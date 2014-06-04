

#define IN_FILE "datos.txt"
#define OUT_FILE "salida.txt"
#define N_ITERACIONES 1000000
#define N_INTERCAMBIOS 1000000

#include <iostream>
#include "recogida.h"
#include "solomon.h"
using namespace std;

int main(int argc, char  *argv[]) {
	srand (time(NULL));
	mdistancia matriz(argv[1]);
	matriz.imprimir();
	optimo opt(matriz);
	opt.repetir(N_ITERACIONES,';',argv[2],N_INTERCAMBIOS);
/*
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
	else
       cout << "Argumentos insuficientes" << endl;
*/
}
