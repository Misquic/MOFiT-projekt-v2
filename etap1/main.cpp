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
    float L   = nm2au(Lnm);  // dlugosc boku calego ukladu
    float anm = Lnm/(2*N);   // dlugosc boku malego elementu nm
    float a   = L/(2*N);     // dlugosc boku malego elementu
    
    std::vector<std::vector<float>>              nodes_names(2*N+1, std::vector<float>(2*N+1));                                    //tablica nazw wezlow
    std::vector<std::vector<std::vector<float>>> nodes_pos(2*N+1, std::vector<std::vector<float>>(2*N+1, std::vector<float>(2)));  //tablica pozycji wezlow
    std::vector<std::vector<float>>              elements_names(2*N, std::vector<float>(2*N));                                     //tablica nazw komorek
    std::vector<std::vector<int>>                nlg(4*N*N, std::vector<int>(4));                                                  //tablica nazw wezlow z indeksowaniem i_kom, i_wewn

    for(int i = 0; i < nodes_names.size(); i++){ //wypelnianie nodes_names, index_node2node_name -> dziala!
        for(int j = 0; j < nodes_names[0].size(); j++){
            nodes_names[i][j] = index_node2node_name(i, j, N);
        }
    }

    for(int i = 0; i < elements_names.size(); i++){ //wypelnianie elements_names, index_kom2i_kom -> dziala!
        for(int j = 0; j < elements_names[0].size(); j++){
            elements_names[i][j] = index_kom2i_kom(i, j, N);
        }
    }

     for(int i = 0; i < nodes_pos.size(); i++){ //wypelnianie nodes_names -> dziala!
        for(int j = 0; j < nodes_pos[0].size(); j++){
            nodes_pos[i][j][0] = -L/2 + j * a;  //x 
            nodes_pos[i][j][1] = L/2 - i * a;   //y
        }
    }

    Elements elements(N, Lnm);

    std::vector<Element> els = elements.getElements();

    std::cout << elements;

    float ksi_x = -1.0;
    float ksi_y = -1.0;

    float x_nlg1=0.0, y_nlg1=0.0; // wezel 1
    float x_nlg2=0.0; // wezel2
    float y_nlg3=0.0; // wezel3
    float psi = 0.0;

    float x=0, y=0;

    std::string file_name = "./results/results2.csv";
    std::ofstream file;
    file.open(file_name);
    if(!file.is_open()){
        std::cerr << "nie udalo sie otworzyc pliku " + file_name;
        return 0;
    }

    for(Element& el: elements.getElements()){
        std::cout <<"\r             \r" << el.getName();
        ksi_x = -1.0;
        while(ksi_x < 1.0){
            ksi_y = -1.0;
            while(ksi_y < 1.0){
                x = 0;
                y = 0;
                psi = 0;
                for(int i_wewn = 1; i_wewn < 5; i_wewn++){
                    x+=el.getNode(i_wewn-1).getPos()[0]*g(ksi_x, ksi_y, i_wewn);
                    y+=el.getNode(i_wewn-1).getPos()[1]*g(ksi_x, ksi_y, i_wewn);
                    psi+=calcPsi(el.getNode(i_wewn-1).getPos()[0], el.getNode(i_wewn-1).getPos()[1])*g(ksi_x, ksi_y, i_wewn);
                }
                file << "\n" << x << "," << y <<","<< psi;
                ksi_y+=Const::d_ksi;
            }
            file.flush();
            ksi_x+=Const::d_ksi;
        }
    }
}