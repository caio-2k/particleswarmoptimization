#include "PSOGriewank.h"
#include <math.h>
#include <ctime>
#include <float.h>
#include <locale.h>
#define nParticles 100
#define Dimension 4
#define c1 2
#define c2 2
#define T_MAX 80
#define Rand() ((double)rand()/RAND_MAX)


double ** posicoes_gri = new double * [nParticles]; // Armazena as posições
double ** velocidade_gri = new double * [nParticles]; // Armazena as velocidades
double ** pBestPos_gri = new double * [nParticles]; // Armazena temporariamente as melhores partículas para cada partícula
double * gBestPos_gri = new double[Dimension]; // Armazena temporariamente o melhor valor de partícula
double * fitnesess_gri = new double[nParticles]; // Armazena temporariamente os valores da função custo(SixHump)
double * pBest_gri = new double[nParticles]; // Melhor adequação temporária para cada particula;
double gBest_gri = 0;

void ParticleSwarmGriewank::alocarMatriz(){

for (int i = 0; i < nParticles; i++) {
    posicoes_gri[i] = new double[Dimension]; // Dimensão da posição de inicialização
    velocidade_gri[i] = new double[Dimension]; // Dimensão da posição de velocidade
    pBestPos_gri[i] = new double[Dimension];   // Dimensão da posição da posição pBest
  }
}

double ParticleSwarmGriewank::GeradorAleatorio(int min, int max){

    return (max - min) * ((double) rand() / (double) RAND_MAX);

}

void ParticleSwarmGriewank::inicializarParticulas(){

    for (int i = 0; i < nParticles; i++) {
            pBest_gri[i] = DBL_MAX;
        for (int j = 0; j < Dimension; j++) {
            posicoes_gri[i][j] = GeradorAleatorio(-600, 600);
            velocidade_gri[i][j] = 0.0;
        }
    }
    gBest_gri = DBL_MAX;
}

double ParticleSwarmGriewank::Griewank(double *x){

 double soma = 0, xi;
  double prod = 1;
    for (int i = 1; i <= nParticles; i++) {
        for (int j = 0; j < Dimension; j++) {
            xi = x[j];
            soma = soma + pow(xi, 2) / 4000;
            prod = prod * cos(xi / sqrt(i));
        }
    }

    double y = soma - prod + 1;
    return y;
}

void ParticleSwarmGriewank::update(){

    for (int i = 0; i < nParticles; i++) {
        for (int j = 0; j < Dimension; j++) {
            fitnesess_gri[i] = Griewank(posicoes_gri[i]);
    }
  }
}

void ParticleSwarmGriewank::printgBest(){

    setlocale(LC_ALL, "Portuguese");
    cout << "-------------------------\n";
    cout << "Global Best = " << gBest_gri << endl;
    cout<<"Posições = ";
    for(int i=0; i<Dimension; i++){
        cout<<"("<<gBestPos_gri[i]<<") ";
    }
    cout << "\n-------------------------\n";

}

void ParticleSwarmGriewank::PSO(){

    int t = 0;

  do {
    int w = 0.9 - (t * ((0.9 - 0.4) / T_MAX)); // Fator inércia

    update(); // Atualiza os valores //


    // Encontra o melhor valor em cada partícula e armazena o valor dessa partícula
    for (int i = 0; i < nParticles; i++) {

      if (fitnesess_gri[i] < pBest_gri[i]) {
        pBest_gri[i] = fitnesess_gri[i];
        for (int j = 0; j < Dimension; j++) {
          pBestPos_gri[i][j] = posicoes_gri[i][j]; // Posição do pBest
        }
        //Encontra o melhor valor de cada interação e armazena temporariamente
        if (pBest_gri[i] < gBest_gri) {
          gBest_gri = pBest_gri[i];
          for (int j = 0; j < Dimension; j++) {
            gBestPos_gri[j] = pBestPos_gri[i][j]; // Posição do gBest
          }
        }
      }

      for (int j = 0; j < Dimension; j++) {

        double r1 = Rand();
        double r2 = Rand();

        velocidade_gri[i][j] = w * velocidade_gri[i][j] + c1 * r1 * (pBestPos_gri[i][j] - posicoes_gri[i][j]) + c2 * r2 * (gBestPos_gri[j] - posicoes_gri[i][j]);

        posicoes_gri[i][j] += velocidade_gri[i][j];

      }

    }

    t++;
    cout << t << " - Best Particle cost = " << gBest_gri << endl;
  } while (t != T_MAX);
    printgBest();

}

void ParticleSwarmGriewank::deletarArray(){

    for (int i = 0; i < nParticles; i++) {

    delete[] posicoes_gri[i];
    delete[] velocidade_gri[i];
    delete[] pBestPos_gri[i];

  }

  delete[] fitnesess_gri;
  delete[] pBest_gri;
  delete[] posicoes_gri;
  delete[] velocidade_gri;
  delete[] gBestPos_gri;
  delete[] pBestPos_gri;

}
