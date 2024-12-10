import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import csv
from scipy.interpolate import griddata

au = 0.05292
nm_au = 1/au

x = "results2.csv"
data = np.loadtxt("results/"+x, delimiter = ",")

# x = np.round(data[:, 0]*au, 2)
x = np.round(data[:, 0], 2)
# y = np.round(data[:, 1]*au, 2)
y = np.round(data[:, 1], 2)

z = data[:, 2]
n = int(np.sqrt(len(z)))
# print(n)

df = pd.DataFrame({'x': x, 'y': y, 'z': z})
df_aggregated = df.groupby(['x', 'y'], as_index=False).mean()  # Średnia wartości z dla powtarzających się (x, y)

# Wydobycie unikalnych wartości x, y oraz wartości z
x_unique = np.unique(df_aggregated['x'])
y_unique = np.unique(df_aggregated['y'])
X, Y = np.meshgrid(x_unique, y_unique)

# Dopasowanie Z do siatki
Z = np.full((len(y_unique), len(x_unique)), np.nan)  # Tablica wypełniona NaN
for _, row in df_aggregated.iterrows():
    xi = np.where(x_unique == row['x'])[0][0]
    yi = np.where(y_unique == row['y'])[0][0]
    Z[yi, xi] = row['z']
# plt.pcolormesh(X, Y, Z, cmap='gnuplot')
# plt.scatter(x, y, c = z, cmap = 'gnuplot')

plt.pcolor(X, Y, Z, cmap = 'gnuplot')
plt.colorbar(label="$\\Psi$")

plt.xlabel("x [nm]")
plt.ylabel("y [nm]")
plt.title("funkcja falowa $\\Psi$, dla N = " + str(int(n/40)))
print(str(int(n/40)))
plt.show()
plt.savefig("results/N_" + str(int(n/40)) + ".png", dpi = 400)