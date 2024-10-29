import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm

file = open("results2.csv", "r+")
txt = file.read()

#print(txt)

txt.split(separator=";")
dx = float(txt[0])
N_dx_el = int(txt[1])
elements_txt = txt[2:]
elements = [el_txt.split(",") for el_txt in elements_txt]
ile_kwadratow = len(elements)
ile_kwadratow_na_bok = int(np.sqrt(ile_kwadratow))
for i in range(ile_kwadratow):
    elements[i] = np.split(np.asarray(elements[i]), N_dx_el)
elements = np.asarray(elements)

psi_n_row = []
for n in range(ile_kwadratow_na_bok):
    psi_in_row_n = []
    for i in range(ile_kwadratow_na_bok):
        psi_in_row_n.extend(elements[n*ile_kwadratow_na_bok+i,n,:])
    psi_n_row.append(psi_in_row_n)

print(psi_n_row)

