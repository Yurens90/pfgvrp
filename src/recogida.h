#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sstream>
#include <time.h>
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
/*
class visita {
   int id; //identificador del punto
   float coste; //coste que supone ir por dicho punto
};
*/

class tvehiculo {
   int id; //identificador del vehiculo
   int ut; // unidades de carga total
   int ua; //unidades de carga actual
   float coste; //coste de la ruta
   //list <int> visitados;
   vector <int> visitados;
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
   void restar_carga (int cg);
   void set_carga(int cg);
   void set_coste(float cost);
   float get_coste ();
   string get_recorrido();
   bool enuso(); //sirve para detectar si un vehículo se ha utilizado o no
   vector <int> get_visitados();
   int get_visitado(int i);
   void set_visitado(int i, int valor);
   void set_visitados(vector <int> &vt);
   int visitados_size(); //devuelve el numero de puntos visitados;
};

class mdistancia {
   int N; //numero de puntos de recogida
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
   float get_distancia(int i, int j);
   float get_demandaij(int i, int j);
};

class ruta {
private:
   mdistancia mraw; //matriz de distancias sin modificar
   mdistancia mord; //matriz de distancias ordenada
   list <int> visitados; //clientes visitados
public:
   //ruta();
   ruta (const ruta &r);
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
   ruta * rt; //se encarga de buscar las rutas para cada vehiculo
   float coste_total;
   int cmed; //carga media de los contenedores
public:
   resolver();
   resolver(mdistancia mat);
   resolver (const resolver &r);
   ~resolver();
   void ejecutar ();
   float get_coste_total ();
   string get_ruta();
   string get_ruta_total();
   unsigned int get_vehiculosusados();
   vector <tvehiculo> get_vector();
   void set_vector(vector <tvehiculo> &vc);
   float getdistanciaij (int i, int j);

};

class optimo {
private:
   resolver * inicial;
   resolver * menor;
   resolver * inter;
   mdistancia matr;
public:
  optimo (mdistancia &mat);
  void repetir (int i,char delimitador, string salida, unsigned int m);
  bool intercambiar();
};

#endif
