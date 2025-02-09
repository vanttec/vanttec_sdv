#!/usr/bin/env python3

import torch
import torch.nn as nn

# Define the model architecture (must match training)
class ResidualGRU(nn.Module):
    def __init__(self, input_size, control_size, hidden_size, output_size, num_layers=2):
        super(ResidualGRU, self).__init__()
        self.gru = nn.GRU(input_size + control_size, hidden_size, num_layers, batch_first=True)
        self.fc = nn.Linear(hidden_size, output_size)

    def forward(self, x, u):
        x = torch.cat((x, u), dim=-1)  # Concatenate state & control
        h, _ = self.gru(x)
        return self.fc(h[:, -1, :])  # Output from last timestep

# Model parameters (must match training)
input_size = 9  # State features: ["x", "y", "psi", "vx", "vy", "r", "ax", "ay", "psi_ddot"]
control_size = 2  # Control features: ["D", "delta"]
hidden_size = 64  # GRU hidden layer size
output_size = 3  # Residual outputs: ["ax", "ay", "psi_ddot"]

# Load the trained model
model = ResidualGRU(input_size, control_size, hidden_size, output_size)
model.load_state_dict(torch.load("/docker-ros/ws/src/tests/GRU/gru_residual_dynamics.pth", map_location="cpu"))
model.eval()

# Wrap the model to enforce correct input shape
class WrappedModel(nn.Module):
    def __init__(self, model):
        super(WrappedModel, self).__init__()
        self.model = model

    def forward(self, x, u):
        # Ensure input shape: (batch=1, seq_len=10, features)
        x = x.view(1, 10, input_size)  # 10 time steps of state data
        u = u.view(1, 10, control_size)  # 10 time steps of control data
        return self.model(x, u)

# Convert model to TorchScript
wrapped_model = WrappedModel(model)

# Generate example input tensors with correct shape
example_x = torch.randn(1, 10, input_size)  # 10 time steps, 9 state features
example_u = torch.randn(1, 10, control_size)  # 10 time steps, 2 control features

# Trace the model for TorchScript
traced_model = torch.jit.trace(wrapped_model, (example_x, example_u))

# Save the model in TorchScript format
traced_model.save("/docker-ros/ws/src/tests/GRU/gru_residual_dynamics.pt")

print("✅ Model successfully converted to TorchScript format!")
