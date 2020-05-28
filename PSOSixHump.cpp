#include "PSOSixHump.h"
#include <math.h>
#include <ctime>
#include <float.h>
#include <locale.h>
#define nParticles 60
#define Dimension 2
#define c1 2
#define c2 2
#define T_MAX 15
#define Rand() ((double)rand()/RAND_MAX)


double ** posicoes_six = new double * [nParticles]; // Armazena as posições
double ** velocidade_six = new double * [nParticles]; // Armazena as velocidades
double ** pBestPos_six = new double * [nParticles]; // Armazena temporariamente as melhores partículas para cada partícula
double * gBestPos_six = new double[Dimension]; // Armazena temporariamente o melhor valor de partícula
double * fitnesess_six = new double[nParticles]; // Armazena temporariamente os valores da função custo(SixHump)
double * pBest_six = new double[nParticles]; // Melhor adequação temporária para cada particula;
double gBest_six = 0;

void ParticleSwarmSixHump::alocarMatriz(){

for (int i = 0; i < nParticles; i++) {
    posicoes_six[i] = new double[Dimension]; // Dimensão da posição de inicialização
    velocidade_six[i] = new double[Dimension]; // Dimensão da posição de velocidade
    pBestPos_six[i] = new double[Dimension];   // Dimensão da posição da posição pBest
  }
}

double ParticleSwarmSixHump::GeradorAleatorio(int min, int max){

    return (max - min) * ((double) rand() / (double) RAND_MAX);

}

void ParticleSwarmSixHump::inicializarParticulas(){
    gBest_six = DBL_MAX;
    for (int i = 0; i < nParticles; i++) {
            pBest_six[i] = DBL_MAX;
        for (int j = 0; j < Dimension; j++) {
                posicoes_six[i][0] = GeradorAleatorio(-3,3);
                posicoes_six[i][1] = GeradorAleatorio(-2,2);
                velocidade_six[i][j] = 0.0;
        }
    }
}

double ParticleSwarmSixHump::Sixhump(double *x){

double termo1, termo2, termo3, x1, x2, y;
  x1 = x[0];
  x2 = x[1];

  termo1 = (4 - 2.1 * pow(x1, 2) + pow(x1, 4) / 3) * pow(x1, 2);
  termo2 = x1 * x2;
  termo3 = (-4 + 4 * pow(x2, 2)) * pow(x2, 2);

  y = termo1 + termo2 + termo3;

  return y;

}

void ParticleSwarmSixHump::update(){

    for (int i = 0; i < nParticles; i++) {
    for (int j = 0; j < Dimension; j++) {
      fitnesess_six[i] = Sixhump(posicoes_six[i]);
    }
  }

}

void ParticleSwarmSixHump::printgBest(){

    setlocale(LC_ALL, "Portuguese");
    cout << "-------------------------\n";
    cout << "Global Best = " << gBest_six << endl;
    cout<<"Posições = ";
    for(int i=0; i<Dimension; i++){
        cout<<"("<<gBestPos_six[i]<<") ";
    }
    cout << "\n-------------------------\n";

}

void ParticleSwarmSixHump::PSO(){

    int t = 0;

  do {
    int w = 0.9 - (t * ((0.9 - 0.4) / T_MAX)); // Fator inércia

    update(); // Atualiza os valores //


    // Encontra o melhor valor em cada partícula e armazena o valor dessa partícula
    for (int i = 0; i < nParticles; i++) {

      if (fitnesess_six[i] < pBest_six[i]) {
        pBest_six[i] = fitnesess_six[i];
        for (int j = 0; j < Dimension; j++) {
          pBestPos_six[i][j] = posicoes_six[i][j]; // Posição do pBest
        }
        //Encontra o melhor valor de cada interação e armazena temporariamente
        if (pBest_six[i] < gBest_six) {
          gBest_six = pBest_six[i];
          for (int j = 0; j < Dimension; j++) {
            gBestPos_six[j] = pBestPos_six[i][j]; // Posição do gBest
          }
        }
      }

      for (int j = 0; j < Dimension; j++) {

        double r1 = Rand();
        double r2 = Rand();

        velocidade_six[i][j] = w * velocidade_six[i][j] + c1 * r1 * (pBestPos_six[i][j] - posicoes_six[i][j]) + c2 * r2 * (gBestPos_six[j] - posicoes_six[i][j]);

        posicoes_six[i][j] += velocidade_six[i][j];

      }

    }

    t++;
    cout << t << " - Best Particle cost = " << gBest_six << endl;
  } while (t != T_MAX);
    printgBest();

}

void ParticleSwarmSixHump::deletarArray(){

    for (int i = 0; i < nParticles; i++) {

    delete[] posicoes_six[i];
    delete[] velocidade_six[i];
    delete[] pBestPos_six[i];

  }

  delete[] fitnesess_six;
  delete[] pBest_six;
  delete[] posicoes_six;
  delete[] velocidade_six;
  delete[] gBestPos_six;
  delete[] pBestPos_six;

}
