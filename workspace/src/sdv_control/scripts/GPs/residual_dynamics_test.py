#!/usr/bin/env python3

import torch
import gpytorch
import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mean_squared_error

# Load trained model
model_path = "/docker-ros/ws/src/tests/residual_dynamics_gp_single_task.pth"
print("CUDA Available:", torch.cuda.is_available())
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"Using device: {device}")

# --- Define model structure (must match trained model) ---
class SparseResidualDynamicsGP(gpytorch.models.ApproximateGP):
    def __init__(self, inducing_points):
        num_inducing = inducing_points.size(0)
        variational_distribution = gpytorch.variational.CholeskyVariationalDistribution(num_inducing)
        variational_strategy = gpytorch.variational.VariationalStrategy(
            self, inducing_points, variational_distribution, learn_inducing_locations=True
        )
        super().__init__(variational_strategy)
        self.mean_module = gpytorch.means.ConstantMean()
        self.covar_module = gpytorch.kernels.MaternKernel(nu=2.5, ard_num_dims=inducing_points.shape[-1])

    def forward(self, x):
        mean_x = self.mean_module(x)
        covar_x = self.covar_module(x)
        return gpytorch.distributions.MultivariateNormal(mean_x, covar_x)

# Load datasets
real_data_path = "/docker-ros/ws/src/tests/real_dynamics_dataset.csv"
simulated_data_path = "/docker-ros/ws/src/tests/dynamic_model_dataset.csv"
real_df = pd.read_csv(real_data_path)
simulated_df = pd.read_csv(simulated_data_path)

# Ensure columns match training
real_df = real_df.drop(columns=["az", "vz"], errors='ignore')
simulated_df = simulated_df.drop(columns=["az", "vz"], errors='ignore')

# Merge data
simulated_df.rename(
    columns={col: f"sim_{col}" for col in ["ax", "ay", "vx", "vy", "x", "y", "psi", "r", "delta", "D"]},
    inplace=True,
)
combined_df = pd.merge(real_df, simulated_df, on="experiment_id", how='inner')

# Compute residuals
for col in ["ax", "ay", "vx", "vy", "x", "y", "psi", "r", "delta", "D"]:
    combined_df[f"residual_{col}"] = combined_df[col] - combined_df[f"sim_{col}"]

# Extract test data after residuals are computed
features = ["ax", "ay", "vx", "vy", "x", "y", "psi", "r", "delta", "D"]
scaler_x = StandardScaler()
scaler_y = StandardScaler()
test_x_np = scaler_x.fit_transform(combined_df[features])
test_y_np = scaler_y.fit_transform(combined_df[["residual_ax"]]).squeeze()

# Convert to torch tensors
test_x = torch.tensor(test_x_np, dtype=torch.float32).to(device)
test_y = torch.tensor(test_y_np, dtype=torch.float32).to(device)

# Load inducing points
num_inducing_points = min(700, test_x.shape[0])  # Ensure consistency with training
inducing_points = test_x[:num_inducing_points, :].clone().detach().to(device)

# Initialize model and load weights
likelihood = gpytorch.likelihoods.GaussianLikelihood().to(device)
model = SparseResidualDynamicsGP(inducing_points).to(device)
model.load_state_dict(torch.load(model_path, map_location=device, weights_only=True))
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
