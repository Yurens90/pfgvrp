

#define IN_FILE "datos.txt"
#define OUT_FILE "salida.txt"
#define N_ITERACIONES 1000
#define N_INTERCAMBIOS 1000000

#include <iostream>
#include "recogida.h"
#include "solomon.h"
using namespace std;

int main(int argc, char  *argv[]) {
	cout << "argc: " << argc << endl;
	if (argc == 4) { //nombre_ejecutable, <entrada>, <salida>, iteraciones
	   cout << "4 argumentos" << endl;
	   solomon sol(argv[1]);
	   sol.calcularmatriz();
	   mdistancia matriz;
	   matriz = sol.convertir();
       int iteraciones = atoi(argv[3]);
   	   optimo opt(matriz);
   	   cout << "iteraciones: " << iteraciones << endl;
   	   opt.repetir(iteraciones,';',argv[2], N_INTERCAMBIOS);
   	   //for (int i = 0; i < 1000000; i++)
	}
	else if (argc == 2) { //nombre_ejecutable, <entrada>
	   cout << "1 argumento" << endl;
	   solomon sol(argv[1]);
	   sol.calcularmatriz();
	   mdistancia matriz;
	   matriz = sol.convertir();
	   //int iteraciones = atoi(argv[3]);
	   optimo opt(matriz);
	   //cout << "iteraciones: " << iteraciones << endl;
	   opt.repetir(N_ITERACIONES,';',argv[2],N_INTERCAMBIOS);
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
	cout << "fin" << endl;
	cout << "Puse cualquier tecla para finalizar..." << endl;
	//cin.get();

}
