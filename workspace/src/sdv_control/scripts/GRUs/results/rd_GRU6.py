#!/usr/bin/env python3

import torch
import torch.nn as nn
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
df_real.insert(df_real.columns.get_loc("r") + 1, "psi_ddot", 0)
df_sim.insert(df_sim.columns.get_loc("r") + 1, "psi_ddot", 0)

df_real = df_real.drop(columns=["az", "vz"], errors='ignore')
df_sim = df_sim.drop(columns=["az", "vz"], errors='ignore')

# Compute angular acceleration (psi_ddot) using numerical differentiation
dt = 0.01  # Modify if needed
df_real['psi_ddot'] = (df_real['r'].shift(-1) - 2 * df_real['r'] + df_real['r'].shift(1)) / (dt ** 2)
df_real.loc[:, 'psi_ddot'] = df_real['psi_ddot'].fillna(0)  # Updated to prevent FutureWarning

# Merge based on experiment_id
df_sim.rename(columns={col: f"sim_{col}" for col in df_sim.columns if col != 'experiment_id'}, inplace=True)
df = pd.merge(df_real, df_sim, on="experiment_id")

# Define residuals as direct outputs of the GRU
residual_targets = ["ax", "ay", "psi_ddot"]
for col in residual_targets:
    df[f'residual_{col}'] = df[col] - df[f'sim_{col}']

# Apply improved log transformation only to psi_ddot
df['residual_psi_ddot'] = np.sign(df['residual_psi_ddot']) * np.log1p(df['residual_psi_ddot'].abs() + 1e-6)

# Print the mean and std of residuals in the dataset
print(df[[f"residual_{col}" for col in residual_targets]].describe())

# Normalize inputs
print("Normalizing inputs...")
scaler_x = StandardScaler()
scaler_u = StandardScaler()
scaler_y = StandardScaler()
scaler_y_psi = StandardScaler()

X_state = scaler_x.fit_transform(df[["sim_x", "sim_y", "sim_psi", "sim_vx", "sim_vy", "sim_r", "sim_ax", "sim_ay", "sim_psi_ddot"]])
X_control = scaler_u.fit_transform(df[["D", "delta"]])
Y_residual = scaler_y.fit_transform(df[["residual_ax", "residual_ay"]])
df['residual_psi_ddot'] = scaler_y_psi.fit_transform(df[['residual_psi_ddot']])

# Convert to Time-Series Data
print("Converting dataset to time-series format...")
seq_length = 10

X_seq, U_seq, Y_seq = [], [], []
for i in range(len(df) - seq_length):
    X_seq.append(X_state[i : i + seq_length])
    U_seq.append(X_control[i : i + seq_length])
    Y_seq.append(Y_residual[i + seq_length])

X_seq, U_seq, Y_seq = np.array(X_seq), np.array(U_seq), np.array(Y_seq)
X_train, X_test, U_train, U_test, Y_train, Y_test = train_test_split(X_seq, U_seq, Y_seq, test_size=0.2, random_state=42)

print("Training samples:", len(X_train), "Testing samples:", len(X_test))

# Convert to PyTorch tensors
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

# Define GRU Model
print("Initializing GRU model...")
class ResidualGRU(nn.Module):
    def __init__(self, input_size, control_size, hidden_size, output_size, num_layers=2):
        super(ResidualGRU, self).__init__()
        self.gru = nn.GRU(input_size + control_size, hidden_size, num_layers, batch_first=True, dropout=0.2)
        self.fc = nn.Linear(hidden_size, output_size)

    def forward(self, x, u):
        x = torch.cat((x, u), dim=-1)
        h, _ = self.gru(x)
        return self.fc(h[:, -1, :])

input_size = X_state.shape[1]
control_size = X_control.shape[1]
hidden_size = 32  # Reduced from 64
output_size = Y_residual.shape[1]

model = ResidualGRU(input_size, control_size, hidden_size, output_size).to(device)
criterion = nn.SmoothL1Loss()  # Using Huber Loss
optimizer = torch.optim.AdamW(model.parameters(), lr=5e-4, weight_decay=1e-3)
batch_size = 64  # Increased from 32

train_dataset = torch.utils.data.TensorDataset(X_train, U_train, Y_train)
train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=batch_size, shuffle=True, drop_last=True)

# Training Loop with Memory-Efficient Settings
with gpytorch.settings.memory_efficient(True):
    model.train()
    train_losses = []
    best_loss = float('inf')
    patience_counter = 0
    patience = 15
    epochs = 250
    for epoch in range(epochs):
        epoch_loss = 0
        with tqdm(train_loader, desc=f"Epoch {epoch+1}/{epochs}") as pbar:
            optimizer.zero_grad()
            for batch_x, batch_u, batch_y in pbar:
                batch_x, batch_u, batch_y = batch_x.to(device), batch_u.to(device), batch_y.to(device)
                output = model(batch_x, batch_u)
                loss = criterion(output, batch_y)
                loss.backward()
                torch.nn.utils.clip_grad_norm_(model.parameters(), max_norm=1.0)
                optimizer.step()
                optimizer.zero_grad()
                epoch_loss += loss.item()
                pbar.set_postfix(loss=loss.item())

        avg_loss = epoch_loss/len(train_loader)
        train_losses.append(avg_loss)
        print(f"Epoch {epoch+1}, Loss: {avg_loss:.6f}")
   
print("Saving training loss plot...")
plt.figure()
plt.plot(train_losses, label="Training Loss")
plt.xlabel("Epoch")
plt.ylabel("Loss")
plt.legend()
plt.title("Training Loss Over Epochs")
plt.savefig("/docker-ros/ws/src/tests/GRU/test6/training_loss.png")
# plt.show()
# Save all epoch losses and learning rates to a file
print("Saving epoch losses and learning rates to a file...")
with open("/docker-ros/ws/src/tests/GRU/test6/epoch_losses_and_lrs.txt", "w") as f:
    for epoch, (loss, lr) in enumerate(zip(train_losses, [group['lr'] for group in optimizer.param_groups]), 1):
        f.write(f"Epoch {epoch}: Loss: {loss:.10f}, Learning Rate: {lr:.6f}\n")
print("Epoch losses and learning rates saved successfully.")

# === 6. Evaluate on Test Data ===
torch.cuda.empty_cache()  # Frees unused memory on GPU
print("Evaluating model on test data...")
with torch.no_grad():
    sample_x = X_test[:1].to(device)
    sample_u = U_test[:1].to(device)
    sample_pred = model(sample_x, sample_u)
    print("Initial Prediction Output:", sample_pred.cpu().numpy())
model.eval()
test_dataset = torch.utils.data.TensorDataset(X_test, U_test)
test_loader = torch.utils.data.DataLoader(test_dataset, batch_size=batch_size, shuffle=False)

Y_pred_list = []
with torch.no_grad():
    for batch_x, batch_u in test_loader:
        batch_x, batch_u = batch_x.to(device), batch_u.to(device)
        batch_pred = model(batch_x, batch_u)
        Y_pred_list.append(batch_pred.cpu())  # Move predictions to CPU to free GPU memory

Y_pred = torch.cat(Y_pred_list, dim=0)  # Reconstruct full predictions

# Step 2: Denormalize residuals
Y_pred[:, -1] = torch.tensor(
    scaler_y_psi.inverse_transform(Y_pred[:, -1].reshape(-1, 1)).flatten(), dtype=torch.float32, device=device
)

# Step 3: Reverse Log Transformation
Y_pred[:, -1] = np.sign(Y_pred[:, -1]) * (np.expm1(np.abs(Y_pred[:, -1])))

# Step 4: Compute Corrected psi_ddot
sim_psi_ddot = X_test[:, -1, -1].cpu().numpy()  # Extract sim_psi_ddot from the test set
corrected_psi_ddot = sim_psi_ddot + Y_pred[:, -1].numpy()  # Add corrected residual to first-principles model

# Compute test loss
test_loss = criterion(torch.tensor(corrected_psi_ddot, dtype=torch.float32).to(device), Y_test[:, -1])
rmse = torch.sqrt(test_loss)
print(f"Test Loss: {test_loss.item():.4f}, RMSE: {rmse.item():.4f}")

# Save test results to a file
with open("/docker-ros/ws/src/tests/GRU/test6/test_results.txt", "w") as f:
    f.write(f"Test Loss: {test_loss.item():.4f}, ")
    f.write(f"RMSE: {rmse.item():.4f}")

# Plot Predictions vs True Values
print("Saving residual predictions plot...")
plt.figure()
plt.scatter(Y_test.cpu().numpy(), Y_pred.cpu().numpy(), alpha=0.5, label='Residuals', color='blue')
plt.plot([-3, 3], [-3, 3], color='red', linestyle='dashed', linewidth=2, label='Perfect Fit')
plt.xlabel("True Residuals")
plt.ylabel("Predicted Residuals")
plt.title("Predicted vs. True Residuals")
plt.legend()
plt.grid(True)
plt.savefig("/docker-ros/ws/src/tests/GRU/test6/residual_predictions.png")
# plt.show()

# === 7. Save Model ===
print("Saving model...")
torch.save(model.state_dict(), "/docker-ros/ws/src/tests/GRU/test6/gru_residual_dynamics.pth")
print("Model saved successfully.")

# ✅ Wrap Model for TorchScript (Ensure Consistency)
class WrappedModel(nn.Module):
    def __init__(self, model):
        super(WrappedModel, self).__init__()
        self.model = model  

    def forward(self, x, u):
        return self.model(x, u)

# ✅ Convert Model to TorchScript (Scripted Version)
wrapped_model = WrappedModel(model)
scripted_model = torch.jit.script(wrapped_model)

# ✅ Save the TorchScript Model (Directly)
model_script_path = "/docker-ros/ws/src/tests/GRU/test6/gru_residual_dynamics.pt"
scripted_model.save(model_script_path)
print(f"✅ Model successfully saved in TorchScript format at: {model_script_path}")