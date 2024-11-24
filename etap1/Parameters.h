#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <cmath>
#include <vector>

double nm2au(double nm);  //do konwersji nm na jednostki atomowe
double eV2au(double eV);  //do konwersji eV na jednostki atomowe

class Parameters{
public:
    const int N;
    const double Lnm;
    const double L;
    double omega = eV2au(10e-3);
    double d_ksi = 0.1;
    double m = 0.067;
    const double anm; 
    const double a; 
    const std::vector<double> w = {5.0/9.0, 8.0/9.0, 5.0/9.0};
    const std::vector<double> p = {-sqrtf(3.0/5.0), 0, sqrtf(3.0/5.0)};

    Parameters(int N, double Lnm);

};

#endif