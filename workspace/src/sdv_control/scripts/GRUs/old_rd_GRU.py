#!/usr/bin/env python3

import torch
import torch.nn as nn
import torch.optim as optim
import gpytorch
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from tqdm import tqdm

# Check for GPU availability
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"Using device: {device}")

# === 1. Load dataset ===
print("Loading dataset...")
df_real = pd.read_csv("/docker-ros/ws/src/tests/GRU/real_dynamics_dataset.csv")
df_sim = pd.read_csv("/docker-ros/ws/src/tests/GRU/dynamic_model_dataset.csv")

print("Preprocessing dataset...")
df_real = df_real.drop(columns=["az", "vz"], errors='ignore')
df_sim = df_sim.drop(columns=["az", "vz"], errors='ignore')

# Merge based on experiment_id
df_sim.rename(columns={col: f"sim_{col}" for col in df_sim.columns if col != 'experiment_id'}, inplace=True)
df = pd.merge(df_real, df_sim, on="experiment_id")

# Define residuals as direct outputs of the GRU without explicit subtraction
residual_targets = ["ax", "ay", "psi_ddot"]
for target in residual_targets:
    if target not in df.columns:
        df[target] = 0  # Default to zero if missing

# === 2. Define Inputs and Outputs ===
print("Defining inputs and outputs...")
state_features = ["x", "y", "psi", "vx", "vy", "r", "ax", "ay"]
control_features = ["D", "delta"]

# Normalize inputs
print("Normalizing inputs...")
scaler_x = StandardScaler()
scaler_u = StandardScaler()
scaler_y = StandardScaler()

X_state = scaler_x.fit_transform(df[state_features])
X_control = scaler_u.fit_transform(df[control_features])
Y_residual = scaler_y.fit_transform(df[residual_targets])

# === 3. Convert to Time-Series Data ===
print("Converting dataset to time-series format...")
seq_length = 10

X_seq, U_seq, Y_seq = [], [], []
for i in range(len(df) - seq_length):
    X_seq.append(X_state[i : i + seq_length])
    U_seq.append(X_control[i : i + seq_length])
    Y_seq.append(Y_residual[i + seq_length])

X_seq, U_seq, Y_seq = np.array(X_seq), np.array(U_seq), np.array(Y_seq)
X_train, X_test, U_train, U_test, Y_train, Y_test = train_test_split(
    X_seq, U_seq, Y_seq, test_size=0.2, random_state=42
)

print("Training samples:", len(X_train), "Testing samples:", len(X_test))

# Convert to PyTorch tensors
print("Converting data to PyTorch tensors...")
X_train, U_train, Y_train = (
    torch.tensor(X_train, dtype=torch.float32).to(device),
    torch.tensor(U_train, dtype=torch.float32).to(device),
    torch.tensor(Y_train, dtype=torch.float32).to(device),
)
X_test, U_test, Y_test = (
    torch.tensor(X_test, dtype=torch.float32).to(device),
    torch.tensor(U_test, dtype=torch.float32).to(device),
    torch.tensor(Y_test, dtype=torch.float32).to(device),
)

# === 4. Define GRU Model ===
print("Initializing GRU model...")
class ResidualGRU(nn.Module):
    def __init__(self, input_size, control_size, hidden_size, output_size, num_layers=2):
        super(ResidualGRU, self).__init__()
        self.gru = nn.GRU(input_size + control_size, hidden_size, num_layers, batch_first=True)
        self.fc = nn.Linear(hidden_size, output_size)

    def forward(self, x, u):
        x = torch.cat((x, u), dim=-1)
        h, _ = self.gru(x)
        return self.fc(h[:, -1, :])

input_size = len(state_features)
control_size = len(control_features)
hidden_size = 64
output_size = len(residual_targets)

model = ResidualGRU(input_size, control_size, hidden_size, output_size).to(device)
criterion = nn.MSELoss()
optimizer = torch.optim.Adam(model.parameters(), lr=0.001)
batch_size = 32
train_dataset = torch.utils.data.TensorDataset(X_train, U_train, Y_train)
train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=batch_size, shuffle=True, drop_last=True)

with gpytorch.settings.memory_efficient(True):
    model.train()
    epochs = 50
    train_losses = []
    
    for epoch in range(epochs):
        epoch_loss = 0
        with tqdm(train_loader, desc=f"Epoch {epoch+1}/{epochs}") as pbar:
            optimizer.zero_grad()
            
            for i, (batch_x, batch_u, batch_y) in enumerate(pbar):
                batch_x, batch_u, batch_y = batch_x.to(device), batch_u.to(device), batch_y.to(device)
                output = model(batch_x, batch_u)
                loss = criterion(output, batch_y)
                loss.backward()
                optimizer.step()
                optimizer.zero_grad()
                epoch_loss += loss.item()
                pbar.set_postfix(loss=loss.item())
        
        train_losses.append(epoch_loss / len(train_loader))
        print(f"Epoch {epoch+1}, Average Loss: {train_losses[-1]:.4f}")

print("Saving training loss plot...")
plt.figure()
plt.plot(train_losses, label="Training Loss")
plt.xlabel("Epoch")
plt.ylabel("Loss")
plt.legend()
plt.title("Training Loss Over Epochs")
plt.savefig("/docker-ros/ws/src/tests/GRU/training_loss.png")
plt.show()

# === 6. Evaluate on Test Data ===
print("Evaluating model on test data...")
model.eval()
with torch.no_grad():
    Y_pred = model(X_test, U_test)
    test_loss = criterion(Y_pred, Y_test)
    print(f"Test Loss: {test_loss.item():.4f}")

# Plot Predictions vs True Values
print("Saving residual predictions plot...")
plt.figure()
plt.scatter(Y_test.cpu().numpy(), Y_pred.cpu().numpy(), alpha=0.5)
plt.xlabel("True Residuals")
plt.ylabel("Predicted Residuals")
plt.title("Predicted vs. True Residuals")
plt.savefig("/docker-ros/ws/src/tests/GRU/residual_predictions.png")
plt.show()

# === 7. Save Model ===
print("Saving model...")
torch.save(model.state_dict(), "/docker-ros/ws/src/tests/GRU/gru_residual_dynamics.pth")
print("Model saved successfully.")

