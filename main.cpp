#include <iostream>
#include<vector>
#include<cmath>
#include<random>
#include<fstream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
    random_device rd;  // Semilla para num aleatorios
    mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

	int N = 500 ;//Inicializar el num de particulas
	float L = 100;//Longitud de la caja
	float r=1.5;//Radio de la partícula

	vector<float> particulasx; //vector de posiciones en x
	vector<float> particulasy; //vector de posiciones en y

	uniform_real_distribution<> dis(r, L - r); //los centros sólo pueden estar en una sub caja de longitud L-2*r
	particulasx.push_back(dis(gen)); //Particula inicial en x
	particulasy.push_back(dis(gen));//Particula inicial en y
	int i = 1;//iterador
	bool  Traslapent;//Verifica que no haya traslape
	float x;
	float y; //Variables donde se asginan las coordenadas.
	float d=2*r;
	while(i<N){
     Traslapent = true ;
     x=dis(gen);//Generamos una coordenadas aleatoria
     y=dis(gen);
     for(int j=0;j<i;j++){
        if (sqrt( pow(x-particulasx[j],2) + pow(y-particulasy[j],2) ) < d){
                Traslapent=false;//Verificamos si hay traslape
                break;
        }
     }
     if(Traslapent){//Si no hay traslape se guarda la coordenada, si sí hay se repite
        particulasx.push_back(x);
        particulasy.push_back(y);
        i++;
     }
	}

    ofstream archivo;//Leemos el archivo donde se guardan las coordenadas
    archivo.open("Coordenadas.csv");
    archivo<<"x,y,\n";

    for(int i=0;i<N;i++){//Guardamos las coordenadas
      archivo<< particulasx[i] << "," << particulasy[i] << "\n";
    }
    archivo.close();//Cerramos el archivo

    ofstream datos;//Guardamos los parametros en un csv para que luego python los lea
    datos.open("Parametros.csv");
    datos<< "N,L,r,\n" << N << "," << L << "," << r << ",";
    //datos<<N << "," << L << "," << r << ",";
    datos.close();
	return 0;
}
