import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import csv
import sys

N = int(sys.argv[1])
L = float(sys.argv[2])

au = 0.05292
nm_au = 1/au


for stan in range(6):
    fig, ax = plt.subplots()
    if(L == int(L)):
        data = np.loadtxt("results/results6_L_" + str(L) + ".000000_N_" + str(N) + "_nrstanu_" + str(stan) + ".csv", delimiter = ",")
    else:
        data = np.loadtxt("results/results6_L_" + str(L) + "00000_N_" + str(N) + "_nrstanu_" + str(stan) + ".csv", delimiter = ",")
    x = np.round(data[:, 0], 2)
    y = np.round(data[:, 1], 2)
    z = data[:, 2]
    n = int(np.sqrt(len(z)))
    print(n)


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

    pcolor = ax.pcolor(X, Y, Z, cmap='gnuplot')
    fig.colorbar(pcolor, label="$\\Psi$")

    ax.set_xlabel("x [nm]")
    ax.set_ylabel("y [nm]")
    ax.set_title("funkcja falowa $\\Psi$, dla N = " + str(int(n/40)) + " stan " + str(stan))
    print(str(int(n/40)))
    #plt.show()
    fig.savefig("results/N_" + str(int(n/40)) + "_stan_" + str(stan) + ".png", dpi = 400)
    fig.savefig("results/N_" + str(int(n/40)) + "_stan_" + str(stan) + ".pdf", dpi = 400)