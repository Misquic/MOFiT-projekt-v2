#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <cmath>
#include <vector>

float nm2au(float nm);  //do konwersji nm na jednostki atomowe
float eV2au(float eV);  //do konwersji eV na jednostki atomowe

class Parameters{
public:
    const int N;
    const float Lnm;
    const float L;
    float omega = eV2au(10e-3);
    float d_ksi = 0.1;
    float m = 0.067;
    const float anm; 
    const float a; 
    const std::vector<float> w = {5.0/9.0, 8.0/9.0, 5.0/9.0};
    const std::vector<float> p = {-sqrtf(3.0/5.0), 0, sqrtf(3.0/5.0)};

    Parameters(int N, float Lnm);

};

#endif