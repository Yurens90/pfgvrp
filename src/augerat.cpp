/*
 * augerat.cpp
 *
 *  Created on: 07/04/2014
 *      Author: David
 */
#include "augerat.h"
#include <fstream>
#include <vector>
#include <math.h>

punto_augerat :: punto_augerat () {
   id = 0;
   x = 0;
   y = 0;
   demanda = 0;
   rtime = 0;
   ddate = 0;
   servtime = 0;
};

punto_augerat :: punto_augerat (int aid, int ax, int ay, int ademanda, int artime, int addate, int aservtime) {
   id = aid;
   x = ax;
   y = ay;
   demanda = ademanda;
   rtime = artime;
   ddate = addate;
   servtime = aservtime;
};

void punto_augerat :: setid (int i) {
   id = i;
};

void punto_augerat :: setx (int i) {
   x = i;
};

void punto_augerat :: sety (int i) {
   y = i;
};

void punto_augerat :: setdemanda (int i) {
   demanda = i;
};

void punto_augerat :: setrtime (int i) {
   rtime = i;
};

void punto_augerat :: setddate (int i) {
   ddate = i;
};

void punto_augerat :: setservtime (int i) {
   servtime = i;
};

int punto_augerat :: getid () {
   return id;
};

int punto_augerat :: getx () {
   return x;
};

int punto_augerat :: gety () {
   return y;
};

int punto_augerat :: getdemanda () {
   return demanda;
};

int punto_augerat :: getrtime () {
   return rtime;
};

int punto_augerat :: getddate () {
   return ddate;
};

int punto_augerat :: setservtime () {
   return servtime;
};

augerat :: augerat () {
   ncamiones = 0;
   nclientes = 0;
   capacidadcamiones = 0;
};

augerat :: augerat (string nombre) {
   ncamiones = 1000;
   capacidadcamiones = 0;
   ifstream file(nombre.c_str());
   string aux;
   while (aux != "DIMENSION")//saltamos las 4 primeras palabras
      file >> aux;
   file >> aux;
   file >> nclientes;
   for (int i = 0; i < 5;i++)
      file >> aux;
   file >> capacidadcamiones;
   file >> aux;
   //cout << "capacidad:" << capacidadcamiones;
   //cout << aux;
   //file >> aux;
   //cout << "aux;: " << aux << endl;
   //cin.get();
   //empezamos a leer todos los numeros
   //while (!file.eof()) { //saltamos las siguientes 12 palabras
   //cout << "nlientes:" << nclientes << endl;
   for (int i = 0; i < nclientes; i++) {
      int num;
      punto_augerat p;
      file >> num;
      //cout << "id:" << num << endl;
      p.setid(num);
      file >> num;
      //cout << "id:" << num << endl;
      p.setx(num);
      file >> num;
      p.sety(num);
      listado.push_back(p);
   }
   //cout << "hola:" << endl;
   file >> aux;
   //file >> aux;
   //cout << "auxi: " << aux << endl;
   for (int i = 0; i < nclientes; i++) {
      punto_augerat p = listado[i];
      int num;
      file >> num;
      //cout << "numbero: " << num << endl;
      file >> num;
      //cout << "numbero2: " << num << endl;
      p.setdemanda(num);
      listado[i] = p;
   }
   file >> aux;
   //cout << aux;
   //cin.get();
   //}
   file.close();
   vector <float> dummy;
   for (unsigned int i = 0; i < listado.size(); i++)
	   dummy.push_back(-1);
   for (unsigned int i = 0; i < listado.size(); i++)
	   matriz.push_back(dummy);
   nclientes = listado.size();

};

void augerat :: mostrarmatriz () {
	cout << "Nclientes: " << nclientes << endl;
	cout << "matriz size: " << matriz.size() << endl;
	cout << "listado size: " << listado.size() << endl;
	for (unsigned int i = 0; i < matriz.size(); i++) {
		for (unsigned int j = 0; j < matriz.size(); j++)
           cout << matriz[i][j];
        cout << endl;
	}
}

void augerat :: mostrarlistado () {
   cout << "Numero de camiones: " << ncamiones << endl;
   cout << "Capacidad de camiones: " << capacidadcamiones << endl;
   for (unsigned int i = 0; i < listado.size(); i++) {
	   cout << "X: " << listado[i].getx() << ", Y: " << listado[i].gety() << endl;
   }

};

void augerat :: mostrarpunto () {
   cout << "id: " << listado[1].getid() << endl;
   cout << "x: " << listado[1].getx() << endl;
   cout << "y: " << listado[1].gety() << endl;
};

void augerat :: calcularmatriz() {
   for (unsigned int i = 0; i < listado.size(); i++) {
	   for (unsigned int j = 0; j < listado.size(); j++) {
           matriz[i][j] = deuclidea(listado[j].getx(),listado[i].getx(),listado[j].gety(),listado[i].gety());
           //cout << "valor: " << matriz[i][j] << endl;
           //cin.get();
	   }
   }
}

//calcular la distancia euclidea entre dos puntos
float augerat :: deuclidea(int x1, int x2, int y1, int y2) {
   return sqrt(pow((x2-x1),2) + pow((y2-y1),2));
}

mdistancia augerat :: convertir () {
   vector<precogida> aux;
   vector<int> dem;
   for (unsigned int i = 0; i < listado.size();i++)
	   dem.push_back(listado[i].getdemanda());
   vector <vector <precogida> > aux2;
   precogida dummy;
   for (int i = 0; i < nclientes; i++)
	 aux.push_back(dummy);
   for (int i = 0; i < nclientes; i++)
	 aux2.push_back(aux);
   //fin de la inicializacion de la matriz
   for (int i = 0; i < nclientes; i++)
	  for (int j = 0; j < nclientes; j++) {
		aux2[i][j].setdistancia(matriz[i][j]);
		aux2[i][j].setid(j);
		aux2[i][j].setdemanda(listado[j].getdemanda());
		//cout << "getdemanda: " << listado[j].getdemanda() << endl;
		//cin.get();
		//aux2[i][j].setdemanda(matri);
	  };
   /*
   cout << "Antes de pasar a mdistancia" << endl;
   cout << "nclientes: " << nclientes << endl;
   for (int i = 0; i < nclientes; i++) {
	   for (int j = 0; j < nclientes; j++) {
          cout << aux2[i][j].getdemanda() << " ";
	   };
	   cout << endl;
   };

   //cout << "despues de crear mdistancia: " << endl;
   //ret.mostrar_demandas();
   //cin.get();
   //ret.imprimir();
   //cin.get();
    */
   mdistancia ret(nclientes,aux2,ncamiones,capacidadcamiones,dem);
   return ret;
}



