#!/usr/bin/env python3

import torch
import gpytorch
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from gpytorch.kernels import MaternKernel
from gpytorch.likelihoods import GaussianLikelihood
from gpytorch.models import ApproximateGP
from gpytorch.variational import VariationalStrategy, CholeskyVariationalDistribution
from tqdm import tqdm

import numpy as np
from sklearn.metrics import mean_squared_error

class SparseResidualDynamicsGP(gpytorch.models.ApproximateGP):
    def __init__(self, inducing_points):
        num_inducing = inducing_points.size(0)
        assert num_inducing > 0, "ERROR: Inducing points tensor is empty."

        variational_distribution = CholeskyVariationalDistribution(num_inducing)
        variational_strategy = VariationalStrategy(
            self, inducing_points, variational_distribution, learn_inducing_locations=True
        )

        super().__init__(variational_strategy)

        self.mean_module = gpytorch.means.ConstantMean()
        self.covar_module = MaternKernel(nu=2.5, ard_num_dims=inducing_points.shape[-1])
        self.num_tasks = 1

    def forward(self, x):
        mean_x = self.mean_module(x)
        covar_x = self.covar_module(x)
        return gpytorch.distributions.MultivariateNormal(mean_x, covar_x)

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

# Split Data
train_df, test_df = train_test_split(combined_df, test_size=0.2, random_state=42)

# --- Apply scaling ---
scaler_x = StandardScaler()
scaler_y = StandardScaler()

train_x_np = scaler_x.fit_transform(train_df[features])
train_y_np = scaler_y.fit_transform(train_df[["residual_ax"]]).squeeze()  # Ensure 1D tensor
test_x_np = scaler_x.transform(test_df[features])
test_y_np = scaler_y.transform(test_df[["residual_ax"]]).squeeze()  # Ensure 1D tensor

# --- Mixed Precision ---
dtype = torch.float32

# Convert to PyTorch tensors
train_x = torch.tensor(train_x_np, dtype=dtype).to(device)
train_y = torch.tensor(train_y_np, dtype=dtype).to(device)
test_x = torch.tensor(test_x_np, dtype=dtype).to(device)
test_y = torch.tensor(test_y_np, dtype=dtype).to(device)

batch_size = 16
train_dataset = torch.utils.data.TensorDataset(train_x, train_y)
train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=batch_size, shuffle=True, drop_last=True)

# --- Define likelihood ---
likelihood = GaussianLikelihood().to(device, dtype=dtype)

# --- Initialize model ---
num_inducing_points = min(700, train_x.shape[0])
inducing_points = train_x[:num_inducing_points, :].clone().detach().to(device)
assert inducing_points.shape[0] > 0, "ERROR: Inducing points tensor is empty."

# Set the jitter globally
gpytorch.settings.variational_cholesky_jitter._set_value(
    float_value=1e-6, double_value=1e-8, half_value=1e-3
)

with gpytorch.settings.memory_efficient(True):
    model = SparseResidualDynamicsGP(inducing_points).to(device, dtype=dtype)

    # --- Train model ---
    model.train()
    likelihood.train()

    optimizer = torch.optim.Adam([
        {'params': model.parameters()},
        {'params': likelihood.parameters()}
    ], lr=0.001)

    mll = gpytorch.mlls.VariationalELBO(likelihood, model, num_data=train_x.size(0))

    accumulation_steps = 4
    num_epochs = 10
    for epoch in range(num_epochs):
        epoch_loss = 0
        with tqdm(train_loader, desc=f"Epoch {epoch+1}/{num_epochs}") as pbar:
            optimizer.zero_grad()

            for i, (batch_x, batch_y) in enumerate(pbar):
                batch_x, batch_y = batch_x.to(device), batch_y.to(device)

                with gpytorch.settings.max_cholesky_size(256):
                    output = model(batch_x)
                    loss = -mll(output, batch_y)

                loss = loss / accumulation_steps
                loss.backward()

                if (i + 1) % accumulation_steps == 0:
                    optimizer.step()
                    optimizer.zero_grad()
                    epoch_loss += loss.item() * accumulation_steps
                    pbar.set_postfix({"Batch Loss": loss.item() * accumulation_steps})

            if (i + 1) % accumulation_steps != 0:
                optimizer.step()
                optimizer.zero_grad()
                epoch_loss += loss.item() * accumulation_steps
                pbar.set_postfix({"Batch Loss": loss.item() * accumulation_steps})

        print(f"Epoch {epoch+1}, Average Loss: {epoch_loss / len(train_loader)}")

# Print Kernel Hyperparameters
print("\nFinal Kernel Hyperparameters:")
print(f"Lengthscale: {model.covar_module.lengthscale}")
print(f"Output Scale: {model.covar_module.outputscale if hasattr(model.covar_module, 'outputscale') else 'N/A'}")

# Save Trained Model
model_save_path = "/docker-ros/ws/src/tests/residual_dynamics_gp_single_task.pth"
torch.save(model.state_dict(), model_save_path)
print(f"Model saved to {model_save_path}")

# Set model to evaluation mode
model.eval()
likelihood.eval()

# Make predictions
with torch.no_grad():
    test_preds = model(test_x).mean.cpu().numpy()
    true_values = test_y.cpu().numpy()
    
    # Compute RMSE
    rmse = np.sqrt(mean_squared_error(true_values, test_preds))
    print(f"Test RMSE: {rmse}")
    
    # Save predictions
    test_results = pd.DataFrame({
        "true_residual_ax": true_values,
        "predicted_residual_ax": test_preds
    })
    test_results.to_csv("/docker-ros/ws/src/tests/test_predictions.csv", index=False)
    print("Test predictions saved to /docker-ros/ws/src/tests/test_predictions.csv")
