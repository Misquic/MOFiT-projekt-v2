import matplotlib.pyplot as plt
import numpy as np
import csv

au = 0.05292
nm_au = 1/au
# liczba bloczków, oś x: długość boczku, oś y: 15 wartości energii

x = input("Podaj nazwę pliku: ")
data = np.loadtxt("results/"+x, delimiter = ",")
data = np.asarray(data)
labels = data[:,0]
xs = data[:,1]
ys = np.empty(len(xs),dtype = object)
for idx, x in enumerate(xs):
    ys[idx] = data[idx,2:]

for idx_2,x in enumerate(xs):
    for idx_1, label in enumerate(labels):
        for idx_3,y in enumerate(ys[idx_2]):
            plt.plot(label,y,'o',color = 'k')
    plt.title(f'N = {label}')
    plt.ylabel('E ($eV$)')
    plt.xlabel(f'L {x}')
    plt.show()