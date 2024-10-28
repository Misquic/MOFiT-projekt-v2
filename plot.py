import numpy as np
import matplotlib.pyplot as plt

def rysuj(func, x, bez_3D = False):

    X, Y = np.meshgrid(x, x)

    fig_width = 8
    plt.figure(figsize=(fig_width, fig_width))

    plt.contourf(X, Y, func, levels=50, cmap='viridis')
    plt.title('ψ')
    plt.xlabel('x [nm]')
    plt.ylabel('y [nm]')
    plt.colorbar()
    plt.show()

    if bez_3D == False:
        fig = plt.figure(figsize=(5, 5))
        ax = fig.add_subplot(111, projection='3d')
        ax.plot_surface(X, Y, func, cmap='viridis')
        ax.set_xlabel('x')
        ax.set_ylabel('y')
        plt.show()

with open('results2.csv', newline='') as file:
    text = file.read()

text = text.split(";")
for txt_idx, txt in enumerate(text):
    text[txt_idx] = txt.split(",")

dx = float(text[0][0])
N = float(text[1][0])

for i in range(len(text[2:])):
    for k in range(len(text[2:][i])):
        if text[2:][i][k] != '':
            text[2:][i][k] = float(text[2:][i][k])

elements = text[2:-1]
elements = np.asarray(elements)

N_sq = int(np.sqrt(len(elements)/4))
list_of_regions = []
for i in range(2*N_sq):
    for j in range(2*N_sq):
        array = np.zeros((2*N_sq,2*N_sq))
        array[3-i,j] = 1
        local = elements[i+j,:-1].reshape(-1,int(N))
        local = local.astype(float)
        list_of_regions.append(np.kron(array, local))
global_array = np.sum(np.array(list_of_regions),axis=0)

x = np.arange(-dx*N*N_sq, dx*N*N_sq, dx)

rysuj(global_array, x)