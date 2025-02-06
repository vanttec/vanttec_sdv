#!/usr/bin/env python3

import torch
import gpytorch
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from gpytorch.kernels import MultitaskKernel, MaternKernel
from torch.optim.lr_scheduler import ReduceLROnPlateau
from gpytorch.likelihoods import MultitaskGaussianLikelihood
from gpytorch.models import ApproximateGP
from gpytorch.variational import MultitaskVariationalStrategy, VariationalStrategy, CholeskyVariationalDistribution
from tqdm import tqdm

class SparseResidualDynamicsGP(gpytorch.models.ApproximateGP):
    def __init__(self, inducing_points, num_tasks):
        inducing_points = inducing_points.to(torch.float32)  # Ensure correct dtype
        num_inducing = inducing_points.size(0)

        # Ensure inducing points are valid
        assert num_inducing > 0, "ERROR: Inducing points tensor is empty."

        # Fix: Expand inducing points for multitask compatibility
        inducing_points = inducing_points.unsqueeze(0).expand(num_tasks, -1, -1).reshape(-1, inducing_points.shape[-1])

        variational_distribution = CholeskyVariationalDistribution(num_inducing * num_tasks)

        base_variational_strategy = VariationalStrategy(
            self, inducing_points, variational_distribution
        )

        variational_strategy = MultitaskVariationalStrategy(
            base_variational_strategy, num_tasks=num_tasks
        )

        super().__init__(variational_strategy)

        self.mean_module = gpytorch.means.ConstantMean()
        self.covar_module = MultitaskKernel(MaternKernel(nu=2.5), num_tasks=num_tasks, rank=1)
        self.num_tasks = num_tasks  # Store the number of outputs

    def forward(self, x):
        print(f"Forward Pass: Input Shape {x.shape}")  # Debug input shape
        print(f"Inducing Points Shape (Inside Model): {self.variational_strategy.base_variational_strategy.inducing_points.shape}")  

        mean_x = self.mean_module(x)
        mean_x = mean_x.unsqueeze(-1).expand(-1, self.num_tasks)

        covar_x = self.covar_module(x)
        covar_x = covar_x.add_jitter(1e-3)

        print(f"Forward Pass: Covar Shape {covar_x.shape}")  # Debug covariance shape

        return gpytorch.distributions.MultitaskMultivariateNormal(mean_x, covar_x)

print("CUDA Available:", torch.cuda.is_available())
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"Using device: {device}")

# --- Load data ---
real_data_path = "/docker-ros/ws/src/tests/real_dynamics_dataset.csv"
simulated_data_path = "/docker-ros/ws/src/tests/dynamic_model_dataset.csv"

real_df = pd.read_csv(real_data_path)
simulated_df = pd.read_csv(simulated_data_path)

# --- Drop columns ---
real_df = real_df.drop(columns=["az", "vz"])
simulated_df = simulated_df.drop(columns=["az", "vz"])

# --- Merge data ---
simulated_df.rename(
    columns={col: f"sim_{col}" for col in ["ax", "ay", "vx", "vy", "x", "y", "psi", "r", "delta", "D"]},
    inplace=True,
)

combined_df = pd.merge(real_df, simulated_df, on="experiment_id")

# Compute residuals
for col in ["ax", "ay", "vx", "vy", "x", "y", "psi", "r", "delta", "D"]:
    combined_df[f"residual_{col}"] = combined_df[col] - combined_df[f"sim_{col}"]

features = ["ax", "ay", "vx", "vy", "x", "y", "psi", "r", "delta", "D"]
residuals = [f"residual_{col}" for col in features]

# Split Data
train_df, test_df = train_test_split(combined_df, test_size=0.2, random_state=42)

# --- Apply scaling ---
scaler_x = StandardScaler()
scaler_y = StandardScaler()
train_x = scaler_x.fit_transform(train_df[features])
train_y = scaler_y.fit_transform(train_df[residuals])
test_x = scaler_x.transform(test_df[features])
test_y = scaler_y.transform(test_df[residuals])

# Convert to PyTorch tensors
train_x = torch.tensor(train_x, dtype=torch.float32).to(device)
train_y = torch.tensor(train_y, dtype=torch.float32).to(device)
test_x = torch.tensor(test_x, dtype=torch.float32).to(device)
test_y = torch.tensor(test_y, dtype=torch.float32).to(device)

batch_size = 64
train_dataset = torch.utils.data.TensorDataset(train_x, train_y)
train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=batch_size, shuffle=True, drop_last=True)

# --- Define likelihood ---
likelihood = MultitaskGaussianLikelihood(num_tasks=train_y.shape[1]).to(device)

# --- Initialize model ---
num_inducing_points = min(500, train_x.shape[0])  # Ensure it doesn't exceed dataset size
inducing_points = train_x[:num_inducing_points, :].clone().to(device)

print(f"Inducing Points Shape Before Model Init: {inducing_points.shape}")
assert inducing_points.shape[0] > 0, "ERROR: Inducing points tensor is empty!"

model = SparseResidualDynamicsGP(inducing_points, num_tasks=train_y.shape[1]).to(device)

# --- Train model ---
model.train()
likelihood.train()

optimizer = torch.optim.Adam(model.parameters(), lr=0.01)
scheduler = ReduceLROnPlateau(optimizer, mode='min', patience=5, verbose=True)
mll = gpytorch.mlls.ExactMarginalLogLikelihood(likelihood, model)

print(f"Inducing Points Shape: {model.variational_strategy.base_variational_strategy.inducing_points.shape}")  

num_epochs = 10
for epoch in range(num_epochs):
    epoch_loss = 0
    with tqdm(train_loader, desc=f"Epoch {epoch+1}/{num_epochs}") as pbar:
        for batch_x, batch_y in train_loader:
            batch_x, batch_y = batch_x.to(device), batch_y.to(device)

            optimizer.zero_grad()
            output = model(batch_x)  
            loss = -mll(output, batch_y)
            loss.backward()
            optimizer.step()

            epoch_loss += loss.item()
            pbar.set_postfix({"Batch Loss": loss.item()})
    
    scheduler.step(epoch_loss / len(train_loader))
    print(f"Epoch {epoch+1}, Average Loss: {epoch_loss / len(train_loader)}")

# ✅ Print Kernel Hyperparameters
print("\nFinal Kernel Hyperparameters:")
print(f"Lengthscale: {model.covar_module.data_covar_module.lengthscale}")
print(f"Output Scale: {model.covar_module.data_covar_module.outputscale}")

# ✅ Save Trained Model
model_save_path = "/docker-ros/ws/src/tests/residual_dynamics_gp.pth"
torch.save(model.state_dict(), model_save_path)
print(f"Model saved to {model_save_path}")