#include <iostream>
#include <fstream>
#include <vector>
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
    float Lnm = 100;         // dlugosc boku calego ukladu nm
    Parameters pm(N, Lnm);
    Elements elements(pm); //PODSTAWOWA SIATKA NA KTOREJ PRACUJEMY
    
    //macierz przekrywania
    std::vector<std::vector<float>> s = std::vector<std::vector<float>>(4, std::vector<float>(4));
    //macierz hamiltona
    std::vector<std::vector<float>> t = std::vector<std::vector<float>>(4, std::vector<float>(4));
    //macierz en pot 
    std::vector<std::vector<float>> v = std::vector<std::vector<float>>(4, std::vector<float>(4));
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
    std::vector<float> pos(2);
    for(Element& el: elements.getElements()){
        std::cout <<"\r             \r" << el.getName();
        float ksi_x = -1.0;
        while(ksi_x < 1.0){
            float ksi_y = -1.0;
            while(ksi_y < 1.0){
                float x = 0;
                float y = 0;
                float psi = 0;
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
    // (x,y) ksi2r(numer wezla, ksix, ksiy)

    std::cout << "\n";
    elements.elements[3].S_filter();

}