#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sstream>

using namespace std;

#ifndef RECOGIDA_H_
#define RECOGIDA_H_

class precogida { //la idea es hacerla abstracta
   //String nombre;
   int id; //numero identificador
   float distancia; //distancia
   bool visitado;
   int demanda;
public:
   precogida ();
   precogida (int x, float d);
   int getid (); //indice original de cada fila en la matriz de distancias
   float getdistancia ();
   precogida (const precogida &p);
   void setid (int iid);
   void setdistancia (float o);
   void setvisitado ();
   bool check_visitado ();
   bool operator < (precogida p) const;
   int getdemanda();
   void setdemanda(int dmd);
};

class tvehiculo {
   int id; //identificador del vehiculo
   int ut; // unidades de carga total
   int ua; //unidades de carga actual
   float coste; //coste de la ruta
   list <int> visitados;
   bool usado;
public:
   tvehiculo();
   ~tvehiculo();
   tvehiculo(int i, int uut);
   void insertar (int i);
   void impr_recorrido ();
   int getid ();
   int getcarga_actual ();
   int getcarga_max ();
   void sumar_carga (int cg);
   void sumar_coste (float cost);
   float get_coste ();
   string get_recorrido();
   bool enuso(); //sirve para detectar si un veh�culo se ha utilizado o no
};

class mdistancia {
   int N; //numero de putnos de recogida
   vector <vector <precogida> > md;
   int nvehiculos; //numero de vehiculos que realizaran las rutas
   int ucarga; //unidades de carga maxima de dichos vehiculos
public:
   mdistancia ();
   ~mdistancia();
   mdistancia (int n);
   mdistancia (string nombre);
   mdistancia (int n, vector <vector <precogida> > &vec, int nvec, int carga);
   int getsize ();
   precogida get (int i, int j);
   void ordenar_matriz ();
   void imprimir ();
   void set_visitados (int i);
   int getnvehiculos();
   int getcarga();
   void mostrar_demandas();
};

class ruta {
private:
   mdistancia mraw; //matriz de distancias sin modificar
   mdistancia mord; //matriz de distancias ordenada
   list <int> visitados; //clientes visitados
public:
   //ruta();
   ruta(mdistancia &mat); //constructor con una matriz ya inicializada desde fuera
   ruta(string nombre);
   vector<precogida> ordenar_fila (int i);
   precogida candidatos (int i);
   bool buscar (tvehiculo &v, int media);
   void insertar_visitado (int i);
   bool comprobar_visitado (int i);
   bool fin_visitas ();
   float getdistanciaij (int i, int j);
   list <int> get_visitados();
};

class resolver {
private:
   vector <tvehiculo> vehiculos; //contiene una lista con los vehiculos que van a realizar las recogidas
   ruta * rt; //se encarga de buscar las rutas para los camiones
   float coste_total;
   int cmed; //carga media de los contenedores
public:
   resolver(mdistancia mat);
   void ejecutar ();
   float get_coste_total ();
   string get_ruta();
   string get_ruta_total();
   unsigned int get_vehiculosusados();
};

class optimo {
private:
   resolver * inicial;
   resolver * menor;
   mdistancia matr;
public:
  optimo (mdistancia &mat);
  void repetir (int i,char delimitador, string salida);
};

#endif
