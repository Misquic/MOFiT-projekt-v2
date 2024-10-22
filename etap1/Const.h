#ifndef CONST_H
#define CONST_H
#include <vector>

// plik w ktory ma byc zaloczony w kazdym innym pliku, definiuje stale i przydatne nazwy

namespace Const{
const int N       = 2;
const float DX    = 2;                  //krok miedzy kolejnymi wezlami w ksi
const float nm_au = 18.89726133921252;  //liczba przez ktora nalezy wymnozyc by dokonac konwersji
const float Lnm   = 100;                // dlugosc boku calego ukladu nm
const float L     = nm_au*Lnm;          // dlugosc boku calego ukladu
const float anm   = Lnm/(2*N);          // dlugosc boku malego elementu nm
const float a     = L/(2*N);            // dlugosc boku malego elementu
const float w    = 10;                 // meV, bo hbar = 1 omega
const float d_ksi = 0.1;                // krok ksi
const float m_0   = 9.10938291e-31;     // masa elektronu w kg.
const float m     = 0.067*m_0;          // masa w au
}

using float2 = std::vector<std::vector<float>>;
using int2 = std::vector<std::vector<int>>;

#endif // CONST_H

// dx, długośc boku, wartości_komórki(, , , ,) - wartości komórki( , , , ,)