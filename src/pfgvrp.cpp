

#define IN_FILE "datos.txt"
#define OUT_FILE "salida.txt"
#define N_ITERACIONES 1000
#define N_INTERCAMBIOS 1000000

#include <iostream>
#include "recogida.h"
#include "solomon.h"
using namespace std;

int main(int argc, char  *argv[]) {
	srand (time(NULL));
	if (argc == 5) { //nombre_ejecutable, <entrada>, <salida>, iteraciones, intercambios
	   solomon sol(argv[1]);
	   sol.calcularmatriz();
	   mdistancia matriz;
	   matriz = sol.convertir();
       int iteraciones = atoi(argv[3]);
   	   optimo opt(matriz);
   	   opt.repetir(iteraciones,';',argv[2], atoi(argv[4]));
	}
	else if (argc == 4) { //nombre_ejecutable, <entrada>, <salida>, iteraciones
	   solomon sol(argv[1]);
	   sol.calcularmatriz();
	   mdistancia matriz;
	   matriz = sol.convertir();
       int iteraciones = atoi(argv[3]);
   	   optimo opt(matriz);
   	   opt.repetir(iteraciones,';',argv[2], N_INTERCAMBIOS);
   	   float sum1 = 0;
   	   int dem = 0;
   	   while(1){
   		  int p1,p2;
   	      cout << "p1?" << endl;
   	      cin >> p1;
   	      cout << "p2?" << endl;
   	      cin >> p2;
   	      cout << "coste: " << matriz.get_distancia(p1,p2) << ", demanda: " << matriz.get_demandaij(p1,p2) << endl;
   	      sum1+=matriz.get_distancia(p1,p2);
   	      dem+=matriz.get_demandaij(p1,p2);
   	      cout << "suma actual coste: " << sum1 << ", demanda: " << dem << endl;
   	      cin.get();

   	   }
	}
	else if (argc == 3) { //nombre_ejecutable, <entrada> <salida>
	   solomon sol(argv[1]);
	   sol.calcularmatriz();
	   mdistancia matriz;
	   matriz = sol.convertir();
	   optimo opt(matriz);
	   opt.repetir(N_ITERACIONES,';',argv[2],N_INTERCAMBIOS);
	}
	else if (argc == 2) {
	   solomon sol(argv[1]);
	   sol.calcularmatriz();
	   mdistancia matriz;
	   matriz = sol.convertir();
	   optimo opt(matriz);
	   opt.repetir(N_ITERACIONES,';',OUT_FILE,N_INTERCAMBIOS);
	}
	else if (argc == 1) { //nombre_ejecutable  =>  Muestra la ayuda
	   cout << "Argumentos insuficientes!" << endl;
	   cout << "Modo de uso: " << endl;
	   cout << argv[0] << " <entrada.txt> <salida.txt> numero_iteraciones" << endl;
	}
	/*
	else if (argc == 1) { //nombre_ejecutable  =>  Se ejecuta el programa con los valores por defecto
		   cout << "0 argumentos" << endl;
		   solomon sol(IN_FILE);
		   sol.calcularmatriz();
		   mdistancia matriz;
		   matriz = sol.convertir();
		   optimo opt(matriz);
		   opt.repetir(N_ITERACIONES,';',OUT_FILE,N_INTERCAMBIOS);
	}
	*/
	else
       cout << "Argumentos insuficientes" << endl;

}
