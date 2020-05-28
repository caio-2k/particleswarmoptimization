#ifndef _PSOGriewank_H_
#define _PSOGriewank_H_
#include <iostream>

using namespace std;

class ParticleSwarmGriewank
{

public:

    void alocarMatriz();
    double GeradorAleatorio(int min, int max);
    void inicializarParticulas();
    double Griewank(double *x);
    void update();
    void printgBest();
    void PSO();
    void deletarArray();

};

#endif


