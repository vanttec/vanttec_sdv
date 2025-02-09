#!/usr/bin/env python3

import torch
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler

# Load the trained model
model_path = "/docker-ros/ws/src/tests/GRU/gru_residual_dynamics.pth"
model = torch.load(model_path)
model.eval()

# Load the test dataset
test_data_path = "/docker-ros/ws/src/tests/GRU/real_dynamics_dataset.csv"
df_real = pd.read_csv(test_data_path)
test_sim_path = "/docker-ros/ws/src/tests/GRU/dynamic_model_dataset.csv"
df_sim = pd.read_csv(test_sim_path)

# Ensure correct feature alignment
df_sim.rename(columns={col: f"sim_{col}" for col in df_sim.columns if col != 'experiment_id'}, inplace=True)
df = pd.merge(df_real, df_sim, on="experiment_id")

# Define features and normalization
state_features = ["sim_x", "sim_y", "sim_psi", "sim_vx", "sim_vy", "sim_r", "sim_ax", "sim_ay"]
control_features = ["D", "delta"]
residual_targets = ["ax", "ay", "psi_ddot"]

scaler_x = StandardScaler()
scaler_u = StandardScaler()
scaler_y = StandardScaler()

X_state = scaler_x.fit_transform(df[state_features])
X_control = scaler_u.fit_transform(df[control_features])
Y_residual = scaler_y.fit_transform(df[residual_targets])

# Convert to PyTorch tensors
X_test = torch.tensor(X_state, dtype=torch.float32)
U_test = torch.tensor(X_control, dtype=torch.float32)
Y_test = torch.tensor(Y_residual, dtype=torch.float32)

# Make predictions with the trained GRU model
with torch.no_grad():
    Y_pred = model(X_test, U_test)

# Convert back to numpy for plotting
Y_test_np = Y_test.numpy()
Y_pred_np = Y_pred.numpy()

# Plot true residuals vs predicted residuals
plt.figure(figsize=(10, 5))
plt.scatter(Y_test_np, Y_pred_np, alpha=0.5)
plt.xlabel("True Residuals")
plt.ylabel("Predicted Residuals")
plt.title("Predicted vs. True Residuals")
plt.grid()
plt.savefig("/docker-ros/ws/src/tests/GRU/residual_predictions_evaluation.png")
plt.show()

print("Evaluation complete. Residual predictions have been plotted and saved.")
