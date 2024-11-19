#include "funkc.h"
#include "Elements.h"
#include <iostream>
#include <tuple>
#include <cmath>


int nlg_fun(int i_kom, int i_wewn, int N){ //zwraca numer wezla globalnie z numeru komorki i numeru wezla lokalnego
    if(i_wewn <= 0 || i_wewn >= 5 ){
        throw std::invalid_argument("i_wewn must be between 1 and 4");
    }    
    switch (i_wewn)
    {
    case 1:
        return i_kom;
        break;
    case 2:
        if(float(i_kom)/(2*N) > (2*N-1) ){//skrajny prawy
            return i_kom + 2*(2*N);
        }
        return i_kom + (2*N);
        break;
    case 3:
        if( i_kom%(2*N) == 0){
            return (4*N*N) + int(i_kom / (2*N)); 
        }
        return i_kom + 1;
        break;
    case 4:
        if(float(i_kom)/(2*N) > (2*N-1) ){
            return i_kom + 2*(2*N) + 1;
        }
        if( i_kom%(2*N) == 0){
            return (4*N*N) + int(i_kom / (2*N)) + 1;
        }
        return i_kom + (2*N)+ 1;
        break;
    
    default:
    return -99;
        break;
    }

};

int index_kom2i_kom(int i, int j, int N){
    return 2*N-i + j*2*N;
};

std::vector<int> i_kom_i_wewn2index_kom(int i_kom, int i_wewn, const Parameters& pm){
    int N = pm.N;
    int i, j;

    switch (i_wewn)    {
    case 1:
        if(i_kom%(2*N) == 0){
            i = i_kom%(2*N)+1;
        }else{
            i = 2*N - i_kom%(2*N)+1;
        }
        j = int((i_kom - 0.1)/(2*N)); //xD chyba będzie działać
        break;
    case 2:
        if(i_kom%(2*N) == 0){
            i = i_kom%(2*N)+1;
        }else{
            i = 2*N - i_kom%(2*N)+1;
        }
        j = int((i_kom - 0.1)/(2*N)) + 1; //xD chyba będzie działać
        break;
    case 3:
        if(i_kom%(2*N) == 0){
            i = i_kom%(2*N);
        }else{
            i = 2*N - i_kom%(2*N);
        }
        j = int((i_kom - 0.1)/(2*N)); //xD chyba będzie działać
        break;
    case 4:
        if(i_kom%(2*N) == 0){
            i = i_kom%(2*N);
        }else{
            i = 2*N - i_kom%(2*N);
        }
        j = int((i_kom - 0.1)/(2*N))+1; //xD chyba będzie działać
        break;
    default:
    throw std::invalid_argument(" błąd w i_kom_iwewn2index_kom, podano zle i_wewn");
        i = -99;
        j = -99;
        break;
    }


    std::vector<int> ret = {i, j};
    return ret;
};


int index_node2node_name(int i, int j, int N){
    if(i!=2*N && j != 2*N){
        return nlg_fun(index_kom2i_kom(i, j, N), 3, N);
    }
    if(i == 2*N && j!= 2*N){
        return nlg_fun(index_kom2i_kom(i-1, j, N), 1, N);
    }
    if( i!=0 && j == 2*N){
        return nlg_fun(index_kom2i_kom(i-1, j-1, N), 2, N);
    }
    //if( i == 0 && j == 2*N){
    return nlg_fun(index_kom2i_kom(i, j-1, N), 4, N);
    
};

float g(float eps1, float eps2, int i_wewn){
    switch(i_wewn){
    case 1:
        return f1(eps1)*f1(eps2);
        break;
    case 2:
        return f2(eps1)*f1(eps2);
        break;
    case 3:
        return f1(eps1)*f2(eps2);
        break;
    case 4:
        return f2(eps1)*f2(eps2);
        break;
    default:
        throw std::out_of_range("g i_wewn out of range");
        break;
    }
};


float f1(float x){
    return (1.0 - x)/2.0;
};

float f2(float x){
    return (1.0 + x)/2.0;
};

std::vector<float> i_kom_i_wewn2pos(int i_kom, int i_wewn, const Parameters& pm){
    std::vector<int> indexes = i_kom_i_wewn2index_kom(i_kom, i_wewn, pm);

    std::vector<float> pos(2);
    pos[0] = -pm.L/2 + indexes[1] * pm.a;  //x 
    pos[1] = pm.L/2 - indexes[0] * pm.a;   //y

    return pos;
}

float calcPsi(float x, float y, const Parameters& pm){
    return exp(-pm.m*pm.omega*0.5 * (x*x + y*y));
};

float s_ji(int j, int i, const Parameters& pm){
    float suma = 0;
    for(int l = 1; l <= 3; l++){
        for(int n = 1; n <= 3; n++){

            suma += pm.w[l-1]*pm.w[n-1]*g(pm.p[l-1],pm.p[n-1],j)*g(pm.p[l-1],pm.p[n-1],i);

            };
        };


    return suma * (pm.a*pm.a/4);
    };

float t_ji(int j, int i, const Parameters& pm){
    float suma = 0;
    for(int l = 1; l <= 3; l++){
        for(int n = 1; n <= 3; n++){
            suma += pm.w[l-1]*pm.w[n-1]*(dgdksi1(j, l, n, pm)*dgdksi1(i, l, n, pm) + dgdksi2(j, l, n, pm)*dgdksi2(i, l, n, pm));// + dgdksi(j, l, n, pm)*dgdksi(i, l, n, pm));
            };
        };

    return suma / (2*pm.m); 
};
float dgdksi2(int i, int l, int n, const Parameters& pm){
    return (g(pm.p[l-1],pm.p[n-1] + pm.d_ksi, i) - g(pm.p[l-1],pm.p[n-1] - pm.d_ksi, i))/(2.0*pm.d_ksi);
};
float dgdksi1(int i, int l, int n, const Parameters& pm){
    return (g(pm.p[l-1] + pm.d_ksi,pm.p[n-1], i) - g(pm.p[l-1] - pm.d_ksi,pm.p[n-1], i))/(2.0*pm.d_ksi);
};

float v_ji(int j, int i, int i_kom, const Parameters& pm){
    float local_const = (pm.a*pm.a/4.0)*(pm.m*pm.omega*pm.omega/2.0);
    float suma = 0;

    for(int l = 1; l <= 3; l++){
        for(int n = 1; n <= 3; n++){
            
            suma += pm.w[l-1]*pm.w[n-1] * g(pm.p[l-1],pm.p[n-1],j) * g(pm.p[l-1],pm.p[n-1],i) * (pow(ksi2r(pm.p[l-1], i_kom, pm)[0], 2.0) + pow(ksi2r(pm.p[n-1], i_kom, pm)[1], 2.0));
            //std::cout << i << " "<< j << " "<< l << " "<< n << " " << suma << "\n";
        };
    };
    return suma * local_const;
};

std::vector<float> ksi2r(float ksi_x, float ksi_y, int i_kom, const Parameters&  pm){
    std::vector<float> pos(2);
    Element el(i_kom, pm);
    return el.ksi2r(ksi_x, ksi_y);
};
std::vector<float> ksi2r(float ksi, int i_kom, const Parameters&  pm){
    return ksi2r(ksi, ksi, i_kom, pm);
};

std::vector<int> generate_global_boundary_nodes(const Parameters&  pm){

    std::vector<int> boundary_nodes(8*pm.N); 

    int k = 0;
    for(int i=0; i<2*pm.N+1; i++){
        for(int j = 0; j<2*pm.N+1; j++){
            if(i==0 || j ==0 || i==2*pm.N || j==2*pm.N){
                boundary_nodes[k] = index_node2node_name(i,j, pm.N);
                k++;
            };
        };
        
    };
    return boundary_nodes;
};


