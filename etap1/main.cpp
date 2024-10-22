#include <iostream>
#include <fstream>
#include <vector>
#include "funkc.h"
#include "Elements.h"
#include "Const.h"


int main(){
    int   N   = Const::N;    // liczba kwadratow
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
            nodes_names[i][j] = index_node2node_name(i, j);
        }
    }
    //std::cout << nodes_names << "\n";

    for(int i = 0; i < elements_names.size(); i++){ //wypelnianie elements_names, index_kom2i_kom -> dziala!
        for(int j = 0; j < elements_names[0].size(); j++){
            elements_names[i][j] = index_kom2i_kom(i, j);
        }
    }
    //std::cout << elements_names <<"\n";

     for(int i = 0; i < nodes_pos.size(); i++){ //wypelnianie nodes_names -> dziala!
        for(int j = 0; j < nodes_pos[0].size(); j++){
            nodes_pos[i][j][0] = -Lnm/2 + j * anm;  //x 
            nodes_pos[i][j][1] = Lnm/2 - i * anm;   //y
        }
    }

    Elements elements(N, Lnm);

    std::vector<Element> els = elements.getElements();

    std::cout << elements;


    //std::cout << nodes_pos;
    
    // for(int i_kom = 1; i_kom <= 4*N*N; i_kom++){ //sprawdzanie czy i_kom_i_wewn2index_kom dziala -> dziala!
    //     for(int i_wewn = 1; i_wewn < 5; i_wewn++){
    //         std::cout <<"i_kom: " << i_kom << " i_wewn: " << i_wewn << " i: " << i_kom_i_wewn2index_kom(i_kom, i_wewn)[0] << " j: "<<  i_kom_i_wewn2index_kom(i_kom, i_wewn)[1] << "\n"; 
    //     }
    //     std::cout << "\n";
    // }


    float ksi_x = -1.0;
    float ksi_y = -1.0;

    float x_nlg1=0.0, y_nlg1=0.0; // wezel 1
    float x_nlg2=0.0; // wezel2
    float y_nlg3=0.0; // wezel3
    float psi = 0.0;

    float x=0, y=0;
    //x_nlg(i_kom,i_wewn) => pozycja wezla nlg(i_kom, i_wewn)

    std::string file_name = "./results/results2.csv";
    std::ofstream file;
    file.open(file_name);
    if(!file.is_open()){
        std::cerr << "nie udalo sie otworzyc pliku " + file_name;
        return 0;
    }
    info(file);

    for(Element& el: elements.getElements()){
        std::cout << el.getName();
        ksi_x = -1.0;
        while(ksi_x < 1.0){
            ksi_y = -1.0;
            while(ksi_y < 1.0){
                x_nlg1 = el.getNode(1).getPos()[0];
                y_nlg1 = el.getNode(1).getPos()[1];
                x_nlg2 = el.getNode(2).getPos()[0];
                y_nlg3 = el.getNode(3).getPos()[1];

                x = x_nlg1*(1-ksi_x) + x_nlg2*(1+ksi_x);
                y = y_nlg1*(1-ksi_y) + y_nlg3*(1+ksi_y);

                psi = calcPsi(x,y);

                file << psi << ",";

                ksi_y+=Const::d_ksi;
                std::cout << ksi_x << " " << ksi_y << "\n";
            }
            file.flush();
            ksi_x+=Const::d_ksi;
        }
        file << ";";
    }

    




    // std::vector<int2> elements_l(4, int2(2*N, std::vector<int>(2*N)));
    // std::vector<std::vector<int>> elements_4(2*N, std::vector<int>(2*N));

    // for(int i_wewn = 1; i_wewn < 5; i_wewn++){
    //     for(int i = 0; i < elements_4.size(); i++){
    //         for(int j = 0; j < elements_4[0].size(); j++){
    //             elements_l[i_wewn-1][i][j] = nlg_fun(index_kom2i_kom(i,j), i_wewn);
    //         }
    //     }
        
    //     std::cout << "narozniki " << i_wewn << "\n" << elements_l[i_wewn-1] << "\n";
    // }
        
    // for(int i_kom = 1; i_kom <= 4*N*N; i_kom++){
    //     for(int i_wewn = 1; i_wewn <= 4; i_wewn++){
    //         nlg[i_wewn-1][i_wewn-1] = nlg_fun(i_kom, i_wewn);
    //     }
    // }    

    // std::cout << transpose(nlg);





    


}