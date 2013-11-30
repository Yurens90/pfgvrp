
#include <iostream>
#include "recogida.h"
#include "solomon.h"
using namespace std;

int main(int argc, char  *argv[]) {
	cout << "argc: " << argc << endl;
	if (argc == 4) { //<entrada>, <salida>, iteraciones
	   cout << "4 argumentos" << endl;
	   solomon sol(argv[1]);
	   sol.calcularmatriz();
	   mdistancia matriz;
	   matriz = sol.convertir();
       int iteraciones = atoi(argv[3]);
   	   optimo opt(matriz);
   	   cout << "iteraciones: " << iteraciones << endl;
   	   opt.repetir(iteraciones,';',argv[2]);
	}
	else if (argc == 2) { //<entrada>, <salida>
	   cout << "4 argumentos" << endl;
	   solomon sol(argv[1]);
	   sol.calcularmatriz();
	   mdistancia matriz;
	   matriz = sol.convertir();
	   //int iteraciones = atoi(argv[3]);
	   optimo opt(matriz);
	   //cout << "iteraciones: " << iteraciones << endl;
	   opt.repetir(10000,';',argv[2]);
	}
	else if (argc == 1) { //<entrada>
	   solomon sol(argv[1]);
	   sol.mostrarlistado();
	   sol.calcularmatriz();
	   mdistancia matriz;
	   matriz = sol.convertir();
	   optimo opt(matriz);
	   opt.repetir(10000,';',"salida.txt");
	}
	else
       cout << "Argumentos insuficientes" << endl;
	cout << "fin" << endl;
	cout << "Puse cualquier tecla para finalizar..." << endl;
	cin.get();

}
