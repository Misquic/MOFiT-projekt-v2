#ifndef CONST_H
#define CONST_H
#include <vector>

// plik w ktory ma byc zaloczony w kazdym innym pliku, definiuje stale i przydatne nazwy

namespace Const{
// const int N       = 10;
const float DX    = 2;                  //krok miedzy kolejnymi wezlami w ksi
const float au = 0.05292; //promień Bohra
const float nm_au = 1/au;  //liczba przez ktora nalezy wymnozyc by dokonac konwersji
const float V2meV = 27211.6;
const float meV2ab = 1.0/V2meV;

const float Lnm   = 100;                // dlugosc boku calego ukladu nm
const float L     = nm_au*Lnm;          // dlugosc boku calego ukladu
const float w    = 10*meV2ab;                 // ab, bo hbar = 1 omega
const float d_ksi = 0.1;                // krok ksi
const float m     = 0.067;          // masa w au
}

using float2 = std::vector<std::vector<float>>;
using int2 = std::vector<std::vector<int>>;

#endif // CONST_H

// dx, długośc boku, wartości_komórki(, , , ,) - wartości komórki( , , , ,)