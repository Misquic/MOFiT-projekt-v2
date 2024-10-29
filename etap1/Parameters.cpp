#include "Parameters.h"


float nm2au(float nm){
    return nm*18.89726133921252;
};

float eV2au(float eV){
    return eV*0.03674932587122423;
};

Parameters::Parameters(int N, float Lnm): N{N}, Lnm{Lnm}, L{nm2au(Lnm)}, a{L/(2*N)}, anm{Lnm/(2*N)}{
};
