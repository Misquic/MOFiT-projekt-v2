#ifndef FUNKC_H
#define FUNKC_H
#include <iostream>
#include <iomanip>
#include <vector>
#include "Eigen/Dense"
#include <typeinfo>     // do sprawdzania typów i porównywania typów
#include <type_traits>  // do std::enable if
#include <fstream>  // do std::enable if
// #include "Const.h"
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
std::vector<double> i_kom_i_wewn2pos(int i_kom, int i_wewn, const Parameters &pm);        //do konwersji i_kom i_wewn KOMORKI na pozyzje WEZLA


double g(double eps1, double eps2, int i);
double f1(double x);
double f2(double x);

double calcPsi(double x, double y, const Parameters&  pm);

double s_ji(int j, int i, const Parameters&  pm);
double t_ji(int j, int i, const Parameters&  pm);
double dgdksi1(int i, int l, int n, const Parameters&  pm);
double dgdksi2(int i, int l, int n, const Parameters&  pm);
double v_ji(int j, int i, int i_kom, const Parameters& pm);
std::vector<double> ksi2r(double ksi_x, double ksi_y, int i_kom, const Parameters&  pm);  //dla konkretnego elementu i ksi wylicz pozycję globalną
std::vector<double> ksi2r(double ksi, int i_kom, const Parameters&  pm);                 // gdy ksi_x = ksi_y, dla wygody //wrapper gdy podamy tylko jedno ksi

std::vector<int> generate_global_boundary_nodes(const Parameters&  pm);
std::pair<std::vector<double>, std::vector<std::vector<double>>> HcESc(const std::vector<std::vector<double>>& vecH, const std::vector<std::vector<double>>& vecS);
std::vector<double> fifteen_lowest(const std::vector<double>& input, size_t n);
int find_index(const std::vector<double>& vec, double value);
std::vector<double> v_with_E(const std::pair<std::vector<double>, std::vector<std::vector<double>>>& EV, int nty_najnizszy);

std::vector<std::complex<double>> d_tdt_Eigen(
const std::vector<std::vector<double>>& vecH, 
    const std::vector<std::vector<double>>& vecS,
    const std::vector<float>& d,
    double dt);

std::vector<std::complex<double>> d_tdt(
    const std::vector<std::vector<double>>& vecH, 
    const std::vector<std::vector<double>>& vecS,
    const std::vector<complex<double>>& d,
    double dt);

////////////////////////////////////////////////SZABLONY////////////////////////////////////////////////////////////// (muszą definicjie muszą być w pliku naglowkowym)


template <class data_type>
bool in(data_type el, std::vector<data_type> vec){
    for(int i = 0; i < vec.size(); i++){
        if(el == vec[i]) return true;
    }
    return false;
}

int oom(double x);// to get order of magnitude
int oom(const std::vector<double>& vec);
int oom(const std::vector<std::vector<double>>& vec);

template <class data_type>
std::ostream& operator<<(std::ostream& out, const std::vector<data_type>& tab){ //wypisywanie wektorów jednowymiarowych

    for(int i=0; i<tab.size(); i++){
        if(typeid(tab[0]) == typeid(double)){
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

// 2D
template <class data_type>
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<data_type>>& tab){ //wypisywanie wektorów dwuwymiarowych

    int max_oom = oom(tab);
    std::cout << "max_oom: " << max_oom << "\n";
    
    if(std::abs(max_oom) < oom(tab.size())){
        max_oom = oom(tab.size());
    }
    else if(max_oom < 0){ //NIE DZIAŁA Z MNIEJSZYMI OD ZERA
        max_oom = 12;
    }
   

    if(typeid(tab[0][0]) == typeid(double)){
        out << std::setw(oom(tab.size()) + 1);
        out << "x" << "  ";
        for(int i = 0; i < tab.size(); i++){
            out << std::setw(max_oom + 1);
            out << i+1 << ": ";
        }
        out << "\n";
    }

    for(int i=0; i<tab.size(); i++){
        if(typeid(tab[0][0]) == typeid(double)){
            out << std::setw(oom(tab.size()) + 1);
            out << i+1 << ": ";
        }
        for(int j=0; j<tab[0].size(); j++){
            if(typeid(tab[0][0]) == typeid(double)){
                out << std::setw(max_oom + 2);
                int round_order = std::pow(10,max_oom+1 - oom(tab[i][j])); // 1 odpowiada za zaokrąglanie do dziesiętnych miejsc największych liczb
                out << round(tab[i][j]*round_order)/round_order;
            }
            else{
                out << tab[i][j];
            }
            if(i!=tab.size()-1 || j!=tab[0].size()-1){
                out << " ";
            } 
        }
        out << "\n";
    }
    return out;
};
template <class data_type, class data_type2>
const std::vector<std::vector<data_type>> operator*(const std::vector<std::vector<data_type>>& tab, data_type2 val){ //mnozenie 2D przez wartość
    std::vector<std::vector<data_type>>ret = tab;
    for(int i=0; i<tab.size(); i++){
        for(int j=0; j<tab[0].size(); j++){
            ret[i][j]*=val;
        }
    }
    return ret;
};
template <class data_type, class data_type2>
const std::vector<std::vector<data_type>> operator*(data_type2 val, const std::vector<std::vector<data_type>>& tab){ //mnozenie 2D przez wartość
    return tab*val;
};

template <class data_type>
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<std::vector<data_type>>>& tab){ //wypisywanie wektorów trzywymiarowych

    for(int i=0; i<tab.size(); i++){
        for(int j=0; j<tab[0].size(); j++){
            out << "{";
            for(int k=0; k<tab[0][0].size(); k++){
                if(typeid(tab[0][0][0]) == typeid(double)){
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