#include "PSOSixHump.h"
#include "PSOGriewank.h"
#include <cstdlib>

using namespace std;

int main(){

    ParticleSwarmSixHump psh;
    ParticleSwarmGriewank psg;
    int op;

   do{

        cout<<"1 - SIX-HUMP CAMEL FUNCTIOn"<<endl;
        cout<<"2 - GRIEWANK FUNCTION"<<endl;
        cout<<"3 - SAIR"<<endl;

        cin>>op;
        switch(op){

        case 1:
        system("clear");
		cout << " = = = = = = PSO - Six Hump: = = = = = = = \n" << endl;
        psh.alocarMatriz();
        psh.inicializarParticulas();
        psh.PSO();
        psh.deletarArray();
        break;

        case 2:
        system("clear");
		cout << " = = = = = = PSO - Griewank: = = = = = = = \n" << endl;
		psg.alocarMatriz();
        psg.inicializarParticulas();
        psg.PSO();
        psg.deletarArray();
        break;
        }
    }while(op != 3);

    return 0;
}
