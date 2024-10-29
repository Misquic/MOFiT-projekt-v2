#include <iostream>
#include <fstream>
#include <vector>
#include "funkc.h"
#include "Elements.h"
#include "Const.h"


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
    std::vector<std::vector<float>> t = std::vector<std::vector<float>>(4, std::vector<float>(4));
    std::vector<std::vector<float>> v = std::vector<std::vector<float>>(4, std::vector<float>(4));
    // for(int j = 0; j < 4; j++){
    //     for(int i = 0; i < )
    // }
 



    //macierz hamiltona

    

    

    std::vector<Element> els = elements.getElements();
    std::cout << elements;

    std::string file_name = "./results/results2.csv";
    std::ofstream file;
    file.open(file_name);
    if(!file.is_open()){
        std::cerr << "nie udalo sie otworzyc pliku " + file_name;
        return 0;
    }

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



    
}