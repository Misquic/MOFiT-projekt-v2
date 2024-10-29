#ifndef FUNKC_H
#define FUNKC_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <typeinfo>     // do sprawdzania typów i porównywania typów
#include <type_traits>  // do std::enable if
#include <fstream>  // do std::enable if
#include "Const.h"
#include "Parameters.h"


/* i_kom       = nazwa komorki
   numer wezla = nazwa wezla
   i_wewn      = lokalny numer wezla w odniesieniu do i_kom
   indexy tablicowe zgodne z row major: i,j 0,1 0,2    
                                        1,0 1,1 1,2
                                        2,0 2,1 2,2
*/
   
/////////////////////////////////////////////////////FUNKCJE////////////////////////////////////////////////////////// typ_zwracany nazwa_funkcji(typ_argumentu argument);




int nlg_fun(int i_kom, int i_wewn, int N); //funkcja bazowa zadania do konwersji i_kom i_wewn KOMORKI na nazwe wezla, bedzie przydatna do obliczen, mozna by nazwac i_kom_iwewn2node_name

int index_kom2i_kom(int i, int j, int N); //do konwersji indeksów tablicy KOMORKI na i_komorki KOMORKI
/* i,j 0,1 0,2    3 6 9
   1,0 1,1 1,2 -> 2 5 8
   2,0 2,1 2,2    1 4 7*/
int index_node2node_name(int i, int j, int N); //do konwersji indexów tablicy WEZLOW na nazwe WEZLA

std::vector<int>   i_kom_i_wewn2index_kom(int i_kom, int i_wewn, const Parameters& pm);  //do konwersji i_kom i_wewn KOMORKI na indexy tablicowe KOMOREK
std::vector<float> i_kom_i_wewn2pos(int i_kom, int i_wewn, const Parameters &pm);        //do konwersji i_kom i_wewn KOMORKI na pozyzje WEZLA


float g(float eps1, float eps2, int i);
float f1(float x);
float f2(float x);

float calcPsi(float x, float y, const Parameters&  pm);

float s_ji(int j, int i, const Parameters&  pm);
float t_ji(int j, int i, const Parameters&  pm);
float dgdksi(int i, int l, int n, const Parameters&  pm);
std::vector<float> ksi2r(float ksi_x, float ksi_y, int i_kom, const Parameters&  pm);  //dla konkretnego elementu i ksi wylicz pozycję globalną
std::vector<float> ksi2r(float ksi, int i_kom, const Parameters&  pm);                 // gdy ksi_x = ksi_y, dla wygody //wrapper gdy podamy tylko jedno ksi


////////////////////////////////////////////////SZABLONY////////////////////////////////////////////////////////////// (muszą definicjie muszą być w pliku naglowkowym)

template <class data_type>
std::ostream& operator<<(std::ostream& out, const std::vector<data_type>& tab){ //wypisywanie wektorów jednowymiarowych

    for(int i=0; i<tab.size(); i++){
        if(typeid(tab[0]) == typeid(float)){
            out << std::setw(3);
        }
        out << tab[i];
        if(i!=tab.size()-1){
                out << " ";
            } 
    }
    out << "\n";
    return out;
};

template <class data_type>
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<data_type>>& tab){ //wypisywanie wektorów dwuwymiarowych

    for(int i=0; i<tab.size(); i++){
        for(int j=0; j<tab[0].size(); j++){
            if(typeid(tab[0][0]) == typeid(float)){
                out << std::setw(3);
            }
            out << tab[i][j];
            if(i!=tab.size()-1 && j!=tab[0].size()-1){
                out << " ";
            } 
        }
        out << "\n";
    }
    return out;
};

template <class data_type>
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<std::vector<data_type>>>& tab){ //wypisywanie wektorów trzywymiarowych

    for(int i=0; i<tab.size(); i++){
        for(int j=0; j<tab[0].size(); j++){
            out << "{";
            for(int k=0; k<tab[0][0].size(); k++){
                if(typeid(tab[0][0][0]) == typeid(float)){
                    out << std::setw(3);
                }  
                out << tab[i][j][k];
                if(i!=tab.size()-1 && j!=tab[0].size()-1 && k<tab[0][0].size()-1){
                    out << " ";
                } 
            }
            out << "} ";
        }
        out << "\n";
    }
    return out;
};

template <class data_type>
std::vector<std::vector<data_type>> transpose( const std::vector<std::vector<data_type>>& tab){ //transpozycja tablic, jesli wymiary sie nie zgadzaja to i tak odbije tablice

    std::vector<std::vector<data_type>> ret(tab[0].size(), std::vector<data_type>(tab.size()));
    // if(tab.size() != tab[0].size()){
    //     throw std::invalid_argument( "można transponować tylko tablice o zgodnych wymiarach NxN");
    // }
    for(int i=0; i<ret.size(); i++){
        for(int j=0; j<ret[0].size(); j++){
            ret[i][j] = tab[j][i];
        }
    }
    return ret;
};



#endif // FUNKC_H