#ifndef _PSOSixHump_H_
#define _PSOSixHump_H_
#include <iostream>

using namespace std;

class ParticleSwarmSixHump{

public:

    void alocarMatriz();
    double GeradorAleatorio(int min, int max);
    void inicializarParticulas();
    double Sixhump(double *x);
    void update();
    void printgBest();
    void PSO();
    void deletarArray();

};

#endif


