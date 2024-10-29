import matplotlib.pyplot as plt
import numpy as np
import csv

au = 0.05292
nm_au = 1/au

data = np.loadtxt("results/results2.csv", delimiter = ",")

x = np.round(data[:, 0]*au, 2)
y = np.round(data[:, 1]*au, 2)
z = np.round(data[:, 2], 2)
n = int(np.sqrt(len(z)))
print(n)

x_unique = np.linspace(x.min(), x.max(), n)
y_unique = np.linspace(y.min(), y.max(), n)
#print(y_unique)

sorted_data = data[np.lexsort((x, y))]

x = sorted_data[:, 0]
y = sorted_data[:, 1]
z = sorted_data[:, 2]

Z = z.reshape(n, n)

X, Y = np.meshgrid(x_unique, y_unique)

plt.pcolormesh(X, Y, Z, cmap='gnuplot')
plt.colorbar(label="$\\Psi$")

plt.xlabel("x [nm]")
plt.ylabel("y [nm]")
plt.title("funkcja falowa $\\Psi$, dla N = " + str(int(n/40)))
plt.savefig("results/N_" + str(int(n/40)) + ".png", dpi = 400)
