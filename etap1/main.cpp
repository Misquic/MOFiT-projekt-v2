#include <iostream>
#include <fstream>
#include <vector>
#include "Eigen/Dense"
#include "funkc.h"
#include "Elements.h"
// #include "Const.h"


int main(int argc, char* argv[]){
    int N;
    if(argc>1){
        N = atof(argv[1]);
    }
    else{
        N   = 2;    // liczba kwadratow
    }
    std::cout << "N: " << N << std::endl;
    double Lnm = 100;         // dlugosc boku calego ukladu nm
    Parameters pm(N, Lnm);
    Elements elements(pm); //PODSTAWOWA SIATKA NA KTOREJ PRACUJEMY
    elements.countV();
    std::cout << "tu\n";

    //macierz przekrywania
    std::vector<std::vector<double>> s = std::vector<std::vector<double>>(4, std::vector<double>(4));
    //macierz hamiltona
    std::vector<std::vector<double>> t = std::vector<std::vector<double>>(4, std::vector<double>(4));
    //macierz en pot 
    std::vector<std::vector<double>> v = std::vector<std::vector<double>>(4, std::vector<double>(4));
    for(int j = 1; j <= 4; j++){
        for(int i = 1; i <= 4; i++){
            s[j-1][i-1] = s_ji(j,i,pm);
            t[j-1][i-1] = t_ji(j,i,pm);
            v[j-1][i-1] = v_ji(j,i, 11, pm);
        }
    }
    std::cout << "s: \n" << s*(4.0/pm.a/pm.a*9.0);
    std::cout << "t: \n" << t*(6.0*2.0*pm.m);
    std::cout << "v: \n" << v*(1/v[0][0])*4;//*(8.0/pm.a/pm.a/pm.m/pm.omega/pm.omega)*; 

    std::vector<Element> els = elements.getElements();
    //std::cout << elements;

    std::string file_name = "./results/results2.csv";
    std::ofstream file;
    file.open(file_name);
    if(!file.is_open()){
        std::cerr << "nie udalo sie otworzyc pliku " + file_name;
        return 0;
    }

    //liczenie psi zad 2
    std::vector<double> pos(2);
    for(Element& el: elements.getElements()){
        std::cout <<"\r             \r" << el.getName();
        double ksi_x = -1.0;
        while(ksi_x < 1.0){
            double ksi_y = -1.0;
            while(ksi_y < 1.0){
                double x = 0;
                double y = 0;
                double psi = 0;
                pos = el.ksi2r(ksi_x, ksi_y);
                for(int i_wewn = 1; i_wewn < 5; i_wewn++){
                    psi+=calcPsi(el.getNode(i_wewn).getPos()[0], el.getNode(i_wewn).getPos()[1], pm)*g(ksi_x, ksi_y, i_wewn);
                }
                file << "\n" << pos[0] << "," << pos[1] <<","<< psi;
                ksi_y+=pm.d_ksi;
            }
            file.flush();
            ksi_x+=pm.d_ksi;
        }
    }
    std::cout << "\n";
    // (x,y) ksi2r(numer wezla, ksix, ksiy)

    //Towrzenie globalnych macierzy S i H

    std::vector<std::vector<double>> S = std::vector<std::vector<double>>((2*pm.N+1)*(2*pm.N+1), std::vector<double>((2*pm.N+1)*(2*pm.N+1)));
    std::vector<std::vector<double>> H = std::vector<std::vector<double>>((2*pm.N+1)*(2*pm.N+1), std::vector<double>((2*pm.N+1)*(2*pm.N+1)));

    for(Element& el: elements.getElements()){
        for(int i1 = 1; i1 <=4; i1++){
            for(int i2 = 1; i2 <=4 ;i2++){
                S[nlg_fun(el.name, i1, pm.N)-1][ nlg_fun(el.name, i2, pm.N)-1] += s[i1-1][i2-1]; //tablica += tablica -> dlatego indeksy -1
                
                H[nlg_fun(el.name, i1, pm.N)-1][ nlg_fun(el.name, i2, pm.N)-1] += t[i1-1][i2-1] + v_ji(i1,i2,el.name, pm); //tablica += tablica + funkcja -> w funkcji indexy wg zadania
            }
        }
    }

    std::cout << "Macierze S i H przed narzuceniem warunków brzegowych:\n";
    std::cout << "S:\n" << S;
    std::cout << "H:\n" << H;
    //warunki brzegowe
    std::vector<int> boundary_nodes = generate_global_boundary_nodes(pm);
    std::cout << boundary_nodes << "\n";
    for(int& node_name: boundary_nodes){
        for(int n = 0; n < S.size(); n++){
            S[node_name -1][n] = 0.0;
            S[n][node_name-1] = 0.0;
            S[node_name-1][node_name-1] = 1;

            H[node_name-1][n] = 0.0;
            H[n][node_name-1] = 0.0;
            H[node_name-1][node_name-1] = -1410.0;
            //std::cout << "tu\n";
        }
    }   
    std::cout << "Macierze S i H po narzuceniu warunków brzegowych:\n";
    std::cout << "S:\n" << S;
    std::cout << "H:\n" << H;
    
    std::cout << "HcESc \n";
    auto ret = HcESc(H, S);
    std::cout<< ret.first << "\n";
    std::cout<< ret.second << "\n";

}

// vcpkg install eigen3
// conan install eigen/3.3.9@

// using namespace std;
// using namespace Eigen;


