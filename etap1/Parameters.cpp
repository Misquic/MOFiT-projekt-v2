#include "Parameters.h"

double nm2au(double nm){
    return nm*18.89726133921252;
};

double eV2au(double eV){
    return eV*0.03674932587122423;
};

Parameters::Parameters(int N, double Lnm): N{N}, Lnm{Lnm}, L{nm2au(Lnm)}, a{L/(2*N)}, anm{Lnm/(2*N)}{
};
