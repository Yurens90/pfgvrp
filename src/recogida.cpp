
#include "recogida.h"

precogida :: precogida () {
   id = 0;
   distancia = 0;
   visitado = false;
   demanda = 0;
};

precogida :: precogida (int x, float d) {
   visitado = NULL;
   id = x;
   distancia = d;
   demanda = 0;
};

int precogida :: getid () {
   return id;
};

float precogida :: getdistancia () {
   return distancia;
};

precogida :: precogida (const precogida &p) {
   visitado = NULL;
   id = p.id;
   distancia = p.distancia;
   demanda = p.demanda;
};

void precogida :: setid (int iid) {
   id = iid;
};

void precogida :: setdistancia (float o) {
   distancia = o;
};

void precogida :: setvisitado() {
   visitado = true;
};

bool precogida :: check_visitado() {
   return visitado;
};

bool precogida :: operator < (precogida p) const {
   if (distancia < p.getdistancia())
      return true;
   return false;
};

int precogida :: getdemanda() {
   return demanda;
}

void precogida :: setdemanda(int dmd) {
   demanda = dmd;
}

tvehiculo :: tvehiculo () {
   id = -1;
   ut = 0;
   ua = 0;
   coste = 0.0;
   visitados.push_back(0);
   usado = false;
};

tvehiculo :: ~tvehiculo() {
   //visitados.clear();
};

tvehiculo :: tvehiculo (int i, int uut) {
   //coste = 0;
   id = i;
   ut = uut;
   ua = 0;
   visitados.push_back(0);
   usado = false;
   coste = 0.0;
};

void tvehiculo :: insertar (int i) {
   usado = true;
   visitados.push_back(i);
};

void tvehiculo :: impr_recorrido () {
   cout << "Recorrido del vehiculo "<< id << ": " << endl;
   for (vector<int> :: iterator it = visitados.begin(); it != visitados.end(); it++)
      cout << "-" << (*it);
   cout << endl << endl;
};

string tvehiculo ::  get_recorrido() {
   stringstream aux;
   for (vector<int> :: iterator it = visitados.begin(); it != visitados.end(); it++) {
      aux << (*it) << " ";
   }
   //cout << "desde recorrido: " << aux.str() << endl;
   //cin.get();
   return aux.str();
};

int tvehiculo :: getid() {
   return id;
};

int tvehiculo :: getcarga_actual () {
   return ua;
};

void tvehiculo :: set_carga(int cg) {
   ua = cg;
};

int tvehiculo :: getcarga_max () {
   return ut;
};

void tvehiculo :: sumar_carga (int cg) {
   ua += cg;
};

void tvehiculo :: sumar_coste (float cost) {
   //cout << "suma coste: " << coste << endl;
   //cin.get();
   coste+=cost;
};

float tvehiculo :: get_coste () {
   if (!enuso())
      return 0.0;
   return coste;
};

bool tvehiculo :: enuso() {
   return usado;
};

vector <int> tvehiculo :: get_visitados() {
   return visitados;
};

void tvehiculo ::  restar_carga (int cg) {
   ua = ua - cg;
};

void tvehiculo ::  set_coste(float cost) {
   coste = cost;
};

void tvehiculo :: set_visitados(vector <int> &vt) {
   visitados = vt;
};

mdistancia :: mdistancia () {
   N = 0;
   ucarga = 0;
   nvehiculos = 0;
};

mdistancia :: ~mdistancia() {
   //md.clear();
};

mdistancia :: mdistancia (int n) {
  ucarga = 0;
  nvehiculos = 0;
  N = n;
  vector<precogida> aux;
  precogida dummy;
  for (int i = 0; i < N; i++)
    aux.push_back(dummy);
  for (int i = 0; i < N; i++)
    md.push_back(aux);
};

mdistancia :: mdistancia (string nombre) {
   ucarga = 0;
   nvehiculos = 0;
   N = 0;
   ifstream fich(nombre.c_str());
   fich >> N;
   vector<precogida> aux;
   precogida dummy;
   for (int i = 0; i < N; i++)
     aux.push_back(dummy);
   for (int i = 0; i < N; i++)
     md.push_back(aux);
   //fin de la inicializacion de la matriz
   for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++) {
        float dist;
        fich >> dist;
        md[i][j].setdistancia(dist);
        md[i][j].setid(j);
      };
};

mdistancia :: mdistancia (int n, vector <vector <precogida> > &vec, int nvec, int carga) {
   N = n;
   md = vec;
   nvehiculos = nvec;
   ucarga = carga;
}

int mdistancia :: getsize() {
   return N;
};

precogida mdistancia :: get(int i, int j) {
   return md[i][j];
};

void mdistancia :: ordenar_matriz() {
   for (int i = 0; i < N; i++) {
      std :: sort(md[i].begin(), md[i].end());
   }
};

void mdistancia :: imprimir() {
   for (int i = 0; i < N; i++) {
     for(int j=0;j < N; j++)
       cout << md[i][j].getdistancia() << "	";
   cout << endl;
   }
   cout << "------------------" << endl;
};

void mdistancia :: set_visitados(int i) {
   for (int j = 0; j < N; j++)
      md[i][j].setvisitado();
};

int mdistancia :: getnvehiculos(){
   return nvehiculos;
};

int mdistancia :: getcarga() {
   return ucarga;
};

void mdistancia :: mostrar_demandas() {
   for (int i = 0; i < N; i++) {
	 for(int j=0;j < N; j++)
	   cout << md[i][j].getdemanda() << "-";
   cout << endl;
   }
   cout << "------------------" << endl;
};

float mdistancia :: get_distancia(int i, int j) {
   return md[i][j].getdistancia();
};

float mdistancia :: get_demandaij(int i, int j) {
   return md[i][j].getdemanda();
};

ruta :: ruta (mdistancia &mat) {
   mraw = mat;
   mord = mat;    //nn
   //mord.ordenar_matriz();
   insertar_visitado(0);
}

ruta :: ruta (string nombre) {
   mdistancia aux(nombre.c_str());
   mraw = aux;
   mord = aux;
   insertar_visitado(0);
}

ruta :: ruta (const ruta &r) {
	mraw = r.mraw;
	mord = r.mord;
	visitados = r.visitados;

};

vector<precogida> ruta :: ordenar_fila (int i) {
   vector<precogida> candidatos;
   int j = 0;
   while (j < mord.getsize() && !fin_visitas()) {
      if (!comprobar_visitado(mord.get(i,j).getid()) && mord.get(i,j).getdistancia() != 0)
         candidatos.push_back(mord.get(i,j));
      j++;
   }
   std :: sort(candidatos.begin(), candidatos.end());
   return candidatos;
};

precogida ruta :: candidatos (int i) { // dado un punto buscamos los 3 mas cercanos que no hayan sido visitados ya, para poder seleccionar uno de forma aleatoria
   vector <precogida> candidatos = ordenar_fila(i);
   int indice = 0;
   if (candidatos.size() >= 3)
      indice = rand()% 3;
   else
      indice = rand()% candidatos.size(); // puede ser que en vez de 3 puntos tengamos dos o 1
   //cout << "indice original: " << i << "," << candidatos[indice].getid() << endl;
  // cout << "distancia: " << candidatos[indice].getdistancia() << endl;
   insertar_visitado(candidatos[indice].getid());
   return candidatos[indice];
};

bool ruta :: buscar (tvehiculo &v, int media) { //ruta parcial
   //cout << "fin de visitas? " << fin_visitas() << endl;
   if (!fin_visitas()) {
	   int cont = 0;
	   int siguiente = 0;
	   //float coste = 0.0;
	   precogida ret;
	   //int demanda = 0;
	  // cout << "Carga antes de entrar: " << v.getcarga_actual() << endl;
	   while (cont < mraw.getsize() && v.getcarga_actual()+ mraw.get_demandaij(ret.getid(), siguiente) <= v.getcarga_max() && !fin_visitas()) {
		  ret = candidatos(siguiente);
		  //cout << "----------->siguiente: " << ret.getid() << endl;
		  //demanda = ret.getdemanda();
		  //cout << "Demanda: " << demanda << endl;
		  //cin.get();
		  cont++;
		  v.sumar_coste(ret.getdistancia());
		  //cout << "ret: " << ret.getdistancia() << ", " << "getij: " << mraw.get_distancia(ret.getid(), siguiente) << " i: " << siguiente << ", j: " << ret.getid() << endl;
		  //cin.get();
		  v.sumar_carga(mraw.get_demandaij(ret.getid(), siguiente));
		  siguiente = ret.getid();
		  v.insertar(siguiente);
		  //v.sumar_carga(demanda);
	   }
	   //cout << "vehiculo lleno" << endl;
	   v.sumar_coste(getdistanciaij(ret.getid(),0)); //añadimos el coste de ir desde el ultimo punto hasta el origen
	   //cout << "getij: " << mraw.get_distancia(ret.getid(), 0) << ", vs: " << getdistanciaij(ret.getid(),0) << " i: 0, j: "  << ret.getid() <<  endl;
	   //cout << "carga hasta el momento: " << v.get_coste() << endl;
	   //cin.get();
	   v.insertar(0); //añadimos al recorrido del vehiculo la vuelta al origen
	   //v.impr_recorrido();
	   //cin.get();
	   //cout << "distancia del ultimo punto al origen: " << getdistanciaij(ret.getid(),0) << endl
	   //cout << "ultimo punto visitado: " << ret.getid() << endl;
	   //cout << "cuenta: " << cont << endl;
	   //cout << "coste total del vehiculo: " << v.get_coste() << endl;
	   return true;
   }
   //cout << "Ya todos los puntos estan visitados" << endl;
   return false;
};

void ruta :: insertar_visitado (int i) {
   visitados.push_back(i);
};

bool ruta :: comprobar_visitado (int i) {
  for (list<int> :: iterator it = visitados.begin(); it != visitados.end(); it++)
     if (i == (*it))
        return true;
   return false;
};

bool ruta :: fin_visitas () {
   if ((int)visitados.size() == (int)mraw.getsize())
      return true;
   return false;
};

float ruta :: getdistanciaij (int i, int j) {
   precogida ret = mraw.get(i,j); //recuperamos el punto ij de la matriz sin alterar
   return ret.getdistancia(); //devolvemos la distancia de un punto a otro
};

list <int> ruta :: get_visitados() {
   return visitados;
};

resolver :: resolver (mdistancia mat) { //corregir
  coste_total = 0.0;
  rt = new ruta(mat);
  //cout << "numero de vehiculos: " << mat.getnvehiculos()  << endl;
  //cout << "carga de los vehiculos: " << mat.getcarga() << endl;
  for (int i = 0; i < mat.getnvehiculos(); i++) {
     tvehiculo vec(i,mat.getcarga());
     vehiculos.push_back(vec);
  }
  //coste_total = 9999;
  cmed = 30; //carga media de los contenedores, hay que cambiarlo para que cada uno tenga su carga
  //cmed = mat.getnvehiculos();
};

resolver :: resolver (const resolver &r) {
   cmed = 0;
   vehiculos= r.vehiculos;
   rt = r.rt;
   (*rt) = (*r.rt);
   coste_total = r.coste_total;

};

resolver :: ~resolver() {
   vehiculos.clear();
   delete rt;
};

void resolver :: ejecutar() {
   bool existe = true ;
   unsigned int i = 0;
   while ((i < vehiculos.size()) && (existe)){
      existe = rt->buscar(vehiculos[i],cmed);
      coste_total+=vehiculos[i].get_coste();
     // cout << "Iteracion : " << i << endl;
      i++;
   }
   //if (i == vehiculos.size())
      //cout << "Ha sido necesario usar todos los vehiculos" << endl;
   //if (!existe)
      //cout << "Se han visitado todos los puntos sin usar el total de vehiculos" << endl;
};

float resolver :: get_coste_total() {
	//cout << "LLamada Get coste total: " << coste_total << endl;
	//cin.get();
   coste_total = 0.0;
   for (unsigned int i = 0; i < get_vehiculosusados(); i++)
      coste_total+=vehiculos[i].get_coste();
   return coste_total;
};

string resolver :: get_ruta() {
   list <int> ret = rt->get_visitados();
   stringstream ss;
   for (list<int> :: iterator it = ret.begin(); it != ret.end(); it++) {
      ss << (*it) << " ";
   }
   return ss.str();
};

string resolver :: get_ruta_total() {
   //vector <tvehiculo> vehiculos;
   stringstream ss;
   for (unsigned int i = 0; i < vehiculos.size();i++) {
	  if (vehiculos[i].enuso())
         ss << vehiculos[i].get_recorrido();
   }
   return ss.str();
};

unsigned int resolver :: get_vehiculosusados() {
   unsigned int cont = 0;
   for (unsigned int i = 0; i < vehiculos.size(); i++) {
      if (vehiculos[i].enuso())
    	  cont++;
   }
   return cont;
};

float resolver ::  getdistanciaij (int i, int j) {
   return (rt->getdistanciaij(i,j));
};


vector <tvehiculo> resolver :: get_vector () {
   return vehiculos;
};

void resolver :: set_vector(vector <tvehiculo> &vc) {
   vehiculos = vc;
};

optimo :: optimo (mdistancia &mat) {
   inicial = new resolver(mat);
   menor = new resolver(mat);
   matr = mat;
}

double timeval_diff(struct timeval *a, struct timeval *b){
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}

//implementar salida
void optimo :: repetir (int n, char delimitador, string salida, int m) {
   menor->ejecutar();
   //struct timeval inicio, fin;
   unsigned int mejorit = 0;
   double mejortiempo = 0.0;
   stringstream ss;
   //clock_t t1;
   //clock_t t2;
   ofstream out(salida.c_str());
   string mejor_ruta;
   float menor_coste = menor->get_coste_total();
   unsigned int nvehiculos = 0;
   //ofstream out("salida.txt");
   struct timeval iniTime, endTime, parcialtime;
   struct timeval iniTimetot, endTimetot;

   cout << "Espere..." << endl;
   double tiempo = 0.0;
   gettimeofday(&iniTimetot,NULL);
   for (int i = 0;i < n; i++) {
	   if (i == n * 0.5)
	      cout << "iteracion: " << i << endl;
	  // t1 = clock();
	   gettimeofday(&iniTime, NULL);
	  //gettimeofday(&inicio, NULL);
	  //cout << endl << endl << endl;
	  resolver *sol = new resolver(matr);
	  sol->ejecutar();
	  //cout << "Sol->getcoste... " << sol->get_coste_total() << " VS " << menor->get_coste_total() << endl;
	  //gettimeofday(&fin, NULL);
	  //double tiempo = ((fin.tv_sec+(float)fin.tv_usec/1000000)-(inicio.tv_sec+(float)inicio.tv_usec/1000000));
	  //t2 = clock();
	  gettimeofday(&endTime, NULL);
	  //double tiempo = (double)(t2 - t1) / CLOCKS_PER_SEC;
	  tiempo += timeval_diff(&endTime, &iniTime);
	  if (sol->get_coste_total() < menor_coste) {
		 //cout << "---> Se ha encontrado una mejor" << endl;
		 (*menor) =  (*sol);
		 gettimeofday(&parcialtime, NULL);
		 mejortiempo = timeval_diff(&parcialtime,&iniTime);
		 mejorit = i;
		 mejortiempo = tiempo;
         mejor_ruta = sol->get_ruta_total();
         menor_coste = sol->get_coste_total();
         nvehiculos = sol->get_vehiculosusados();
	  }
	  ss << i << delimitador << tiempo << delimitador << sol->get_ruta_total() << delimitador << sol->get_coste_total() << delimitador << sol->get_vehiculosusados() << endl;
	  delete sol;
	  //cout << "Iteracion: " << i << endl;
   };
   int i = 0;
   while (!intercambiar() && i < m) {
      i++;
      if (i == m*0.5)
         cout << i << endl;
   }
   cout << "Iteracion en la que se intercambio: " << i << endl;
   if (i < m) {
      out << "Solucion mejorada con intercambio interno:" << endl;
      out << "Iteracion_mejor_solucion_mejorada" << delimitador << "tiempo" << delimitador << "ruta" << delimitador << "coste" << delimitador << "numero_vehiculos_usados" << endl;
      out << mejorit << delimitador << mejortiempo << delimitador << menor->get_ruta_total() << delimitador << menor->get_coste_total() << delimitador << nvehiculos << endl;
   }
   out << "Iteracion_mejor_solucion_sin_mejorar" << delimitador << "tiempo" << delimitador << "ruta" << delimitador << "coste" << delimitador << "numero_vehiculos_usados" << endl;
   out << mejorit << delimitador << mejortiempo << delimitador << mejor_ruta << delimitador << menor_coste << delimitador << nvehiculos << endl;
   out << "Numero_iteracion" << delimitador << "tiempo" << delimitador << "ruta" << delimitador << "coste" << delimitador << "numero_vehiculos_usados" << endl;
   out << ss.str();
   out << "Tiempo total: " << timeval_diff(&endTimetot,&iniTimetot);
   cout << "Tiempo total: " << timeval_diff(&endTimetot,&iniTimetot) << " segundos" << endl;

   out.close();
};

/*
   vector <tvehiculo> vecs = menor->get_vector();
   //vector< <vector <int> > > pvisitados;
   vector <vector <int> > pvisitados;
   for (unsigned int i = 0; i < vecs.size();i++) {
      if (vecs[i].enuso()) {
         pvisitados.push_back(vecs[i].get_visitados());
      }
   }
   for (unsigned int i = 0; i < pvisitados.size(); i++) {
      for (unsigned int j = 1; j < pvisitados[i].size()-1; j++) {
         for (unsigned int z = 0; z < pvisitados.size(); z++) {
        	 for (unsigned int k = 1; k < pvisitados[z].size()-1; k++) {
			    cout << pvisitados[i][j] << " vs " << pvisitados[z][k] << ", " ;
			    //cin.get();

        	 }
		     cout << endl;
		     //cin.get();
         }
      }
   }

 */
bool optimo :: intercambiar() {
   vector <tvehiculo> vecs = menor->get_vector();
   srand(time(NULL));
   //vector <vector <int> > pvisitados;
   if (menor->get_vehiculosusados() > 1) {
	   unsigned int i = rand()% menor->get_vehiculosusados();
	   while (i == 0) {
		  //cout << "1" << endl;
		  i = rand()% menor->get_vehiculosusados();
	   }
	   unsigned int j = rand()% menor->get_vehiculosusados();
	   while (j == i && vecs.size() > 1) {
		  j = rand()% menor->get_vehiculosusados();
		  //cout << "2" << endl;
	   }
	   vector <int> p1 = vecs[i].get_visitados();
	   vector <int> p2 = vecs[j].get_visitados();
	   unsigned int k = rand()% p1.size();
	   //cout << "p1 size : " << p1.size() << ", i: " << i << endl;
	   //cin.get();
	   while (k == 0) {
		   //cout << "3" << endl;
		  k = rand()% p1.size();
	   }
	   unsigned int z = rand()% p2.size();
	   while (z == 0)
		  z = rand()% p2.size();

	   int aux = p1[k];
	   p1[k] = p2[z];
	   p2[z] = aux;

	   float cost_total1 = 0.0;
	   int demand1 = 0.0;
	   for (unsigned int ii = 1; ii < p1.size(); ii++) {
		  cost_total1 += matr.get_distancia(p1[ii-1], p1[ii]);
		  demand1 += matr.get_demandaij(p1[ii-1], p1[ii]);
	   }
	   float cost_total2 = 0.0;
	   int demand2 = 0.0;
	   for (unsigned int ii = 1; ii < p2.size(); ii++) {
		  cost_total2 += matr.get_distancia(p2[ii-1], p2[ii]);
		  demand2 += matr.get_demandaij(p2[ii-1], p2[ii]);
	   }
	   if (((cost_total1 <= vecs[i].get_coste()) || (cost_total2 <= vecs[j].get_coste())) && demand1 <= vecs[i].getcarga_max() && demand2 <= vecs[j].getcarga_max()) {
		  cout << "mejor solucion encontrada!" << endl;
		  cout << "Antiguo coste1: " << vecs[i].get_coste() << ", nuevo: " << cost_total1 << endl;
		  cout << "Antigua carga1: " << vecs[i].getcarga_actual() << ", nuevo: " << demand1 << ", maxima: " << vecs[i].getcarga_max() << endl;
		  cout << "Antiguo coste2: " << vecs[j].get_coste() << ", nuevo: " << cost_total2 << endl;
		  cout << "Antigua carga2: " << vecs[j].getcarga_actual() << ", nuevo: " << demand2 << ", maxima: " << vecs[i].getcarga_max() << endl;
		  vecs[i].set_visitados(p1);
		  vecs[i].set_carga(demand1);
		  vecs[i].set_coste(cost_total1);
		  vecs[j].set_visitados(p2);
		  vecs[i].set_carga(demand2);
		  vecs[i].set_coste(cost_total2);
		  menor->set_vector(vecs);
		  cout << "coste total: " << menor->get_coste_total() << ", ruta: " << menor->get_ruta_total() << endl;
		  return true;
	   }
   }
   return false;

};
