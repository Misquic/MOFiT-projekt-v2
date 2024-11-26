#include "funkc.h"
#include "Elements.h"
#include <iostream>
#include <tuple>
#include <cmath>
#include "Eigen/Dense"
#include "Eigen/Eigenvalues"
using namespace Eigen;

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
        if(double(i_kom)/(2*N) > (2*N-1) ){//skrajny prawy
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
        if(double(i_kom)/(2*N) > (2*N-1) ){
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

double g(double eps1, double eps2, int i_wewn){
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

double f1(double x){
    return (1.0 - x)/2.0;
};

double f2(double x){
    return (1.0 + x)/2.0;
};

std::vector<double> i_kom_i_wewn2pos(int i_kom, int i_wewn, const Parameters& pm){
    std::vector<int> indexes = i_kom_i_wewn2index_kom(i_kom, i_wewn, pm);

    std::vector<double> pos(2);
    pos[0] = -pm.L/2 + indexes[1] * pm.a;  //x 
    pos[1] = pm.L/2 - indexes[0] * pm.a;   //y

    return pos;
}

double calcPsi(double x, double y, const Parameters& pm){
    return exp(-pm.m*pm.omega*0.5 * (x*x + y*y));
};

double s_ji(int j, int i, const Parameters& pm){
    double suma = 0;
    for(int l = 1; l <= 3; l++){
        for(int n = 1; n <= 3; n++){

            suma += pm.w[l-1]*pm.w[n-1]*g(pm.p[l-1],pm.p[n-1],j)*g(pm.p[l-1],pm.p[n-1],i);

            };
        };


    return suma * (pm.a*pm.a/4);
    };

double t_ji(int j, int i, const Parameters& pm){
    double suma = 0;
    for(int l = 1; l <= 3; l++){
        for(int n = 1; n <= 3; n++){
            suma += pm.w[l-1]*pm.w[n-1]*(dgdksi1(j, l, n, pm)*dgdksi1(i, l, n, pm) + dgdksi2(j, l, n, pm)*dgdksi2(i, l, n, pm));// + dgdksi(j, l, n, pm)*dgdksi(i, l, n, pm));
            };
        };

    return suma / (2*pm.m); 
};
double dgdksi2(int i, int l, int n, const Parameters& pm){
    return (g(pm.p[l-1],pm.p[n-1] + pm.d_ksi, i) - g(pm.p[l-1],pm.p[n-1] - pm.d_ksi, i))/(2.0*pm.d_ksi);
};
double dgdksi1(int i, int l, int n, const Parameters& pm){
    return (g(pm.p[l-1] + pm.d_ksi,pm.p[n-1], i) - g(pm.p[l-1] - pm.d_ksi,pm.p[n-1], i))/(2.0*pm.d_ksi);
};

double v_ji(int j, int i, int i_kom, const Parameters& pm){
    double local_const = (pm.a*pm.a/4.0)*(pm.m*pm.omega*pm.omega/2.0);
    double suma = 0;

    for(int l = 1; l <= 3; l++){
        for(int n = 1; n <= 3; n++){
            
            suma += pm.w[l-1]*pm.w[n-1] * g(pm.p[l-1],pm.p[n-1],j) * g(pm.p[l-1],pm.p[n-1],i) * (pow(ksi2r(pm.p[l-1], i_kom, pm)[0], 2.0) + pow(ksi2r(pm.p[n-1], i_kom, pm)[1], 2.0));
            //std::cout << i << " "<< j << " "<< l << " "<< n << " " << suma << "\n";
        };
    };
    return suma * local_const;
};

std::vector<double> ksi2r(double ksi_x, double ksi_y, int i_kom, const Parameters&  pm){
    std::vector<double> pos(2);
    Element el(i_kom, pm);
    return el.ksi2r(ksi_x, ksi_y);
};
std::vector<double> ksi2r(double ksi, int i_kom, const Parameters&  pm){
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

// oblicza równanie własne Hc=ESc
std::pair<std::vector<double>, std::vector<std::vector<double>>> HcESc(
    const std::vector<std::vector<double>>& vecH, 
    const std::vector<std::vector<double>>& vecS) 
{
    if (vecH.size() != vecH[0].size() || vecS.size() != vecS[0].size()) {
        throw std::invalid_argument("macierze nie są kwadratowe");
    }
    if (vecH.size() != vecS.size()) {
        throw std::invalid_argument("inne wymiary tablic");
    }

    int n = vecH.size();
    Eigen::MatrixXd H(n, n);
    Eigen::MatrixXd S(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            H(i, j) = vecH[i][j];
            S(i, j) = vecS[i][j];
        }
    }

    if (!H.isApprox(H.transpose()) || !S.isApprox(S.transpose())) {
        throw std::invalid_argument("macierze są niesymetryczne");
    }

    Eigen::GeneralizedSelfAdjointEigenSolver<Eigen::MatrixXd> solver(H, S);
    if (solver.info() != Eigen::Success) {
        throw std::runtime_error("nie rozwiązałem lol :D");
    }

    Eigen::VectorXd eigenvalues = solver.eigenvalues();
    std::vector<double> E(eigenvalues.data(), eigenvalues.data() + eigenvalues.size());

    Eigen::MatrixXd eigenvectors = solver.eigenvectors();
    std::vector<std::vector<double>> v;
    for (int col = 0; col < eigenvectors.cols(); ++col) {
        std::vector<double> column(eigenvectors.rows());
        for (int row = 0; row < eigenvectors.rows(); ++row) {
            column[row] = eigenvectors(row, col);
        }
        v.push_back(column);
    }

    return {E, v};
};

// zwraca n najniższych wartości z wektora input
std::vector<double> fifteen_lowest(const std::vector<double>& input, size_t n) {
    std::vector<double> positiveValues;
    for (double value : input) {
        if (value > 0) {
            positiveValues.push_back(value);
        }
    }
    if (positiveValues.size() < n) {
        throw std::runtime_error("Za mało dodatnich wartości w wektorze!");
    }
    std::sort(positiveValues.begin(), positiveValues.end());
    return std::vector<double>(positiveValues.begin(), positiveValues.begin() + n);
};

// znajduje indeks w wektorze vec, któremu odpowiadająca wartość równa jest value
int find_index(const std::vector<double>& vec, double value) {
    auto it = std::find(vec.begin(), vec.end(), value);
    if (it != vec.end()) {
        return std::distance(vec.begin(), it);
    } else {
        return -1;
    }
};

int oom(double x){ // to get order of magnitude // nie działa dla ujemnych i poniżej 1 
    int oom_val = 0;
    if(x < 0){
        oom_val--;
        x = -x;
    }
    if(x == 0){
        return 1;
    }
    if(x < 1){
        while(x < 1){
            x*=10;
            oom_val--;
            // if(oom_val < -14){
            //     std::cout << "oom break!: " << oom_val << " x: " << x << "\n";
            // return 0;
            //}
        }
        return oom_val;
        // return 2;
    }
    while(x > 1){
        x/=10;
        oom_val++;
        if(oom_val > 12){
            std::cout << "oom break!: " << x << "\n";
            return oom_val;
        }
    }
    return oom_val;
};

int oom(const std::vector<double>& vec){
    int oom_val = 0;
    for(const double& x: vec){
        int oom_x = oom(x);
        if(std::abs(oom_x) > oom_val){
            oom_val = oom_x;
        }
    }
    return oom_val;
}

int oom(const std::vector<std::vector<double>>& vec){
    int oom_val = 0;
    for(const std::vector<double>& x: vec){
        int oom_x = oom(x);
        if(std::abs(oom_x) > oom_val){
            oom_val = oom_x;
        }
    }
    return oom_val;
}

// obliczanie wektora d w następnym kroku czasowym na podstawie poprzedniego kroku czasowego z Eigen
std::vector<std::complex<double>> d_tdt_Eigen(
    const std::vector<std::vector<double>>& vecH, 
    const std::vector<std::vector<double>>& vecS,
    const std::vector<complex<double>>& d,
    double dt){

    if (vecH.size() != vecH[0].size() || vecS.size() != vecS[0].size()) {
        throw std::invalid_argument("macierze nie są kwadratowe");
    }
    if (vecH.size() != vecS.size()) {
        throw std::invalid_argument("inne wymiary tablic");
    }

    std::complex<double> constant(0.0,0.5*dt);
    int n = vecH.size();

    Eigen::MatrixXcd SpH(n, n);
    Eigen::MatrixXcd SmH(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::complex<double> vH(vecH[i][j],0.0);
            std::complex<double> vS(vecS[i][j],0.0);
            SpH(i, j) = vS + constant*vH;
            SmH(i, j) = vS - constant*vH;
            }
    }
    Eigen::VectorXcd d_eigen(d.size());
    for (size_t i = 0; i < d.size(); ++i) {
        d_eigen[i] = std::complex<double>(d[i], 0.0);
    }

    SmH = SmH.inverse();
    Eigen::MatrixXcd SmHd = SmH * d_eigen;
    Eigen::VectorXcd dplusdt = SpH.colPivHouseholderQr().solve(SmHd);

    std::vector<std::complex<double>> Ddt;
    for (int i = 0; i < dplusdt.size(); ++i) {
        Ddt.push_back(dplusdt(i));
        }

    return Ddt;
};

// obliczanie wektora d w następnym kroku czasowym na podstawie poprzedniego kroku czasowego
std::vector<std::complex<double>> d_tdt(
    const std::vector<std::vector<double>>& vecH, 
    const std::vector<std::vector<double>>& vecS,
    const std::vector<complex<double>>& d,
    double dt){

    if (vecH.size() != vecH[0].size() || vecS.size() != vecS[0].size()) {
        throw std::invalid_argument("macierze nie są kwadratowe");
    }
    if (vecH.size() != vecS.size()) {
        throw std::invalid_argument("inne wymiary tablic");
    }

    std::complex<double> constant(0.0,0.5*dt);
    int n = vecH.size();
    std::vector<std::vector<std::complex<double>>> SpH(n, std::vector<std::complex<double>>(n));
    std::vector<std::vector<std::complex<double>>> SmH(n, std::vector<std::complex<double>>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::complex<double> vH(vecH[i][j],0.0);
            std::complex<double> vS(vecS[i][j],0.0);

            SpH[i][j] = vS + constant*vH;
            SmH[j][i] = std::conj(vS - constant*vH); // od razu jest transponowana
            // i sprzezana, chociaz jest rzeczywista, ale dla formalnosci
            }
    }

    std::vector<complex<double>> SpH_d(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            SpH_d[i] += SpH[i][j]*d[j];
        }}

    std::vector<complex<double>> SmHT_SpH_d(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            SmHT_SpH_d[i] += SmH[i][j]*SpH_d[j];
        }}

    return SmHT_SpH_d;
};

// std::vector<double> v_with_E(const std::pair<std::vector<double>, std::vector<std::vector<double>>>& EV, int nty_najnizszy){
//     std::vector<double> lowest_Es = fifteen_lowest(EV.first, 15);
//     double used_E = lowest_Es[nty_najnizszy-1];
//     int idx = find_index(EV.first, used_E);
//     std::vector<double> vec;

// = EV.second
// return vec;
// };