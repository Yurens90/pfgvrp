#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

using namespace std;

class precogida { //la idea es hacerla abstracta
   //String nombre;
   int id; //numero identificador
   float distancia; //distancia
   bool visitado;
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
};

class tvehiculo {
   int id; //identificador del vehiculo
   int ut; // unidades de carga total
   int ua; //unidades de carga actual
   float coste; //coste de la ruta
   list <int> visitados;
public:
   tvehiculo();
   tvehiculo(int i, int uut);
   void insertar (int i);
   void impr_recorrido ();
   int getid ();
   int getcarga_actual ();
   int getcarga_max ();
   void sumar_carga (int cg);
   void sumar_coste (float cost);
   float get_coste ();
};

class mdistancia {
   int N; //numero de putnos de recogida
   vector <vector <precogida> > md;
public:
   mdistancia ();
   mdistancia (int n);
   mdistancia (string nombre);
   int getsize ();
   precogida get (int i, int j);
   void ordenar_matriz ();
   void imprimir ();
   void set_visitados (int i);
};

class ruta {
private:
   mdistancia mraw; //matriz de distancias sin modificar
   mdistancia mord; //matriz de distancias ordenada
   list <int> visitados; //clientes visitados
public:
   ruta();
   vector<precogida> ordenar_fila (int i);
   precogida candidatos (int i);
   void buscar (tvehiculo &v, int media);
   void insertar_visitado (int i);
   bool comprobar_visitado (int i);
   bool fin_visitas ();
   float getdistanciaij (int i, int j);
};

class resolver {
private:
   vector <tvehiculo> vehiculos; //contiene una lista con los vehiculos que van a realizar las recogidas
   ruta rt; //se encarga de buscar las rutas para los camiones
   float coste_total;
   int cmed; //carga media de los contenedores
public:
   resolver();
   void ejecutar ();
   int get_coste_total ();
};

class optimo {
private:
   resolver menor;
public:
  void repetir (int i);
};

class punto_solomon {
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
   punto_solomon ();
   punto_solomon (int aid, int ax, int ay, int ademanda, int artime, int addate, int aservtime);
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

class solomon {
private:
   int ncamiones;
   int nclientes;
   int capacidadcamiones;
   vector <punto_solomon> listado;
   int xmin, xmax;
   int ymin, ymax;
public:
   solomon (); //inicializar a 0 los totales y los max y a 999 los mínimos
   //leer de fichero
   solomon (string nombre);
   //calcular distancia entre dos puntos
   
   //generar matriz de distancias -> pasar de vector de puntos_solomon a mdistancia
   
   //getter y setter de xmin,xmax,nclientes
   
};