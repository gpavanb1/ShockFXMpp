import numpy as np
import matplotlib.pyplot as plt
from verification_data import *  # Import exact solution data

# Load numerical data from file
# PASTE THE PROGRAM OUTPUT INTO data.txt
data = np.loadtxt("data.txt")

# Extract columns
x, rho, u, p = data.T  # Transpose to unpack columns

# Create figure
plt.figure(figsize=(8, 6))

# Plot numerical solutions with solid lines
plt.plot(x, rho, "b-", label=r"$\rho/\rho_{0}$")
plt.plot(x, u, "r-", label=r"$u$")
plt.plot(x, p, "g-", label=r"$p/p_{0}$")

# Plot exact solutions with markers
plt.plot(density_x, density_y, "bs",
         label=r"$\rho/\rho_{0}$ Exact", markersize=5)
plt.plot(velocity_x, velocity_y, "rs", label=r"$u$ Exact", markersize=5)
plt.plot(pressure_x, pressure_y, "gs", label=r"$p/p_{0}$ Exact", markersize=5)

# Labels and title
plt.xlabel("x")
plt.ylabel("Values")
plt.title("Euler 1D Conservative Variables")
plt.grid()

# Legend placement (automatic best position)
plt.legend(loc="best")

# Adjust layout for better fit
plt.tight_layout()

# Show plot
plt.show()
