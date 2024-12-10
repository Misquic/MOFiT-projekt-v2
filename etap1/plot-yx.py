import matplotlib.pyplot as plt
import numpy as np
import csv

au = 0.05292
nm_au = 1/au
# liczba bloczków, oś x: długość boczku, oś y: 15 wartości energii

# x = input("Podaj nazwę pliku: ")
x = "results5_v2.txt"

data = np.loadtxt("results/"+x, delimiter = ",")
data = np.asarray(data)
labels = data[:,0]
xs = data[:,1]
ys = np.empty(len(xs),dtype = object)
for idx, x in enumerate(xs):
    ys[idx] = data[idx,2:]

colors = np.linspace(0,1,7)
colors = plt.cm.viridis(colors)
# for idx_2,x in enumerate(xs):
#     for idx_1, label in enumerate(labels):
#         for idx_3,y in enumerate(ys[idx_2]):
#             plt.plot(label,y,'o',color = colors[idx_3%6])
#     plt.ylim((0, 0.0002))
#     plt.title(f'N = {label}')
#     plt.ylabel('E ($eV$)')
#     plt.xlabel(f'L {x}')
#    #plt.show()

lowest_en = 1000
i = 0
N = 5
colors = np.linspace(0,1,len(ys[0]))
colors = plt.cm.viridis(colors)
for i in range(len(ys[0])):
    for idx_2,(x, n) in enumerate(zip(xs, labels)):
            # print(x, n, ys[idx_2][i])
            if(n == N):
                plt.plot(x,ys[idx_2][i]/0.03674932587122423, ".", color = colors[i])
                if(ys[idx_2][i] < lowest_en):
                    lowest_en = ys[idx_2][i]
                    lowest_ex_idx = idx_2
                    lowest_en_L = x
print("najnizsza en dla L:" ,lowest_en_L)
plt.xlim((20, 150))
plt.ylim((0, 0.3))
plt.ylabel("E [eV]")
plt.xlabel("L [nm]")
plt.title("N = " + str(N) + " najniższa energia dla L = " + str(lowest_en_L) + " nm")
plt.savefig("results/EvsL_N_5.pdf")
plt.savefig("results/EvsL_N_5.png")
plt.show()
## znaleźć najniższe L dla jakiegoś N, a potem dla tego L zrobić zależność en od L
# print(lowest_en_L)
# print(lowest_en)


# for idx_2,x in enumerate(xs):
#     for idx_1, label in enumerate(labels):
#         for idx_3,y in enumerate(ys[idx_2]):
#             plt.plot(label,y,'o',color = colors[idx_3%6])
#     plt.ylim((0, 0.0002))
#     plt.title(f'N = {label}')
#     plt.ylabel('E ($eV$)')
#     plt.xlabel(f'L {x}')
#     plt.show()