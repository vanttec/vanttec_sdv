#!/usr/bin/env python3

import torch
import torch.nn as nn

# ✅ Define Your Model (Ensure it Matches Training Config)
class GRUResidualModel(nn.Module):
    def __init__(self, input_size, control_size, hidden_size, output_size, num_layers=2):  # ✅ Use Correct num_layers
        super(GRUResidualModel, self).__init__()
        self.gru = nn.GRU(input_size + control_size, hidden_size, num_layers=num_layers, batch_first=True)
        self.fc = nn.Linear(hidden_size, output_size)

    def forward(self, x, u):
        # Concatenate state and control inputs
        input_seq = torch.cat((x, u), dim=-1)  # Shape: (batch, 10, 11)
        _, h_n = self.gru(input_seq)  # Take last hidden state
        out = self.fc(h_n[-1])  # Use last layer's hidden state
        return out

# ✅ Instantiate the Model with Correct Sizes
input_size = 9  # State features
control_size = 2  # Control features
hidden_size = 64  # GRU hidden size
output_size = 3  # Residual outputs (ax, ay, psi_ddot)
num_layers = 2  # ✅ Use same `num_layers` as in `rd_GRU.py`

model = GRUResidualModel(input_size, control_size, hidden_size, output_size, num_layers=num_layers)
model.load_state_dict(torch.load("/docker-ros/ws/src/tests/GRU/test1/gru_residual_dynamics.pth", map_location="cpu"))
model.eval()

# ✅ Wrap the Model (Needed for TorchScript)
class WrappedModel(nn.Module):
    def __init__(self, model):
        super(WrappedModel, self).__init__()
        self.model = model

    def forward(self, x, u):
        return self.model(x, u)

# Convert model to TorchScript
wrapped_model = WrappedModel(model)

# Generate example input tensors with correct shape
example_x = torch.randn(1, 10, input_size)  # (Batch, Time, Features)
example_u = torch.randn(1, 10, control_size)  # (Batch, Time, Control)

# Trace the model for TorchScript
traced_model = torch.jit.trace(wrapped_model, (example_x, example_u))

# Save the model in TorchScript format
traced_model.save("/docker-ros/ws/src/tests/GRU/test1/gru_residual_dynamics.pt")

print("✅ Model successfully converted to TorchScript format!")
