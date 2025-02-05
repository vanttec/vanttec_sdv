import torch
import gpytorch
import pandas as pd

class ResidualDynamicsGP(gpytorch.models.ExactGP):
    def __init__(self, train_x, train_y, likelihood):
        super().__init__(train_x, train_y, likelihood)
        self.mean_module = gpytorch.means.ConstantMean()
        self.covar_module = gpytorch.kernels.ScaleKernel(gpytorch.kernels.RBFKernel())

    def forward(self, x):
        mean_x = self.mean_module(x)
        covar_x = self.covar_module(x)
        return gpytorch.distributions.MultivariateNormal(mean_x, covar_x)

# Load data
# Assuming the data is loaded into a dictionary with keys:
#   'train_x': Input features (vx, u)
#   'train_y': Output targets (residual dynamics r(vx, u))
# Load data from CSV file
data_path = "/docker-ros/ws/src/tests/"  # Replace with the actual path
df = pd.read_csv(data_path)

#... (data preprocessing and feature engineering)

# Convert to PyTorch tensors
train_x = torch.tensor(df[['vx', 'vy', 'vz', 'ax', 'ay', 'az', 'x', 'y', 'psi', 'yaw_rate', 'steering_angle', 'throttle']].values)
train_y = torch.tensor(df[['residual_ax', 'residual_ay', 'residual_az', 'residual_vx', 'residual_vy', 'residual_vz', 'residual_x', 'residual_y', 'residual_psi', 'residual_yaw_rate']].values)

test_x = torch.tensor(test_df[['vx', 'vy', 'vz', 'ax', 'ay', 'az', 'x', 'y', 'psi', 'yaw_rate', 'steering_angle', 'throttle']].values)  # Input features for testing

# Define likelihood
likelihood = gpytorch.likelihoods.GaussianLikelihood()

# Initialize model
model = ResidualDynamicsGP(train_x, train_y, likelihood)

# Train model
model.train()
likelihood.train()
optimizer = torch.optim.Adam(model.parameters(), lr=0.1)
mll = gpytorch.mlls.ExactMarginalLogLikelihood(likelihood, model)
for i in range(100):
    optimizer.zero_grad()
    output = model(train_x)
    loss = -mll(output, train_y)
    loss.backward()
    optimizer.step()

# Save trained model
torch.save(model.state_dict(), 'residual_dynamics_gp.pth')

# Load trained model
model.load_state_dict(torch.load('residual_dynamics_gp.pth'))

# Make predictions
model.eval()
likelihood.eval()
with torch.no_grad():
    predictions = likelihood(model(test_x))