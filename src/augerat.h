/*
 * augerat.h
 *
 *  Created on: 07/04/2014
 *      Author: David
 */
#include <iostream>
#include <vector>
#include "recogida.h"

#ifndef AUGERAT_H_
#define AUGERAT_H_
using namespace std;

class punto_augerat {
private:
   int id;
   int x;
   int y;
   int demanda;
   int rtime;
   int ddate;
   int servtime;
public:
   //constructor normal y con los parámetros
   punto_augerat ();
   punto_augerat (int aid, int ax, int ay, int ademanda, int artime, int addate, int aservtime);
   //getter y setter para todos
   void setid (int i);
   void setx (int i);
   void sety (int i);
   void setdemanda (int i);
   void setrtime (int i);
   void setddate (int i);
   void setservtime (int i);
   int getid ();
   int getx ();
   int gety ();
   int getdemanda ();
   int getrtime ();
   int getddate ();
   int setservtime ();

};

class augerat {
private:
   int ncamiones;
   int nclientes;
   int capacidadcamiones;
   vector <punto_augerat> listado;
  // int xmin, xmax;
   //int ymin, ymax;
   vector <vector <float> > matriz;
public:
   augerat (); //inicializar a 0 los totales y los max y a 999 los mínimos
   //leer de fichero
   augerat (string nombre);
   //calcular distancia entre dos puntos

   //generar matriz de distancias -> pasar de vector de puntos_augerat a mdistancia

   //getter y setter de xmin,xmax,nclientes

   //mostrar todos los puntos
   void mostrarlistado();
   //mostrar un punto
   void mostrarpunto();
   //mostrar matriz de distancias de augerat
   void mostrarmatriz();
   //calcular la matriz de distancias
   void calcularmatriz();
   //calcular la distancia euclidea entre dos puntos
   float deuclidea(int x1, int x2, int y1, int y2);
   //convertir a mdistancia
   mdistancia convertir();


};



#endif /* AUGERAT_H_ */
