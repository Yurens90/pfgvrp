
#include "recogida.h"

precogida :: precogida () {
   id = -1;
   distancia =-1;
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
   for (list<int> :: iterator it = visitados.begin(); it != visitados.end(); it++)
      cout << "-" << (*it);
   cout << endl << endl;
};

string tvehiculo ::  get_recorrido() {
   stringstream aux;
   for (list<int> :: iterator it = visitados.begin(); it != visitados.end(); it++) {
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


int tvehiculo :: get_ultimo() {
   //cout << "visitados size get ultimo: " << visitados.size() << endl;
   //cout << (*visitados.end()) << endl;
   return (*(visitados.rbegin()));
};

bool tvehiculo :: lleno() {
   if (getcarga_actual() == getcarga_max())
      return true;
   return false;
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

   //insertar_visitado(candidatos[indice].getid());
   return candidatos[indice];
};

bool ruta :: buscar (vector <tvehiculo> &vecs) { //ruta parcial //siguiente es el punto en funcion del cual, se va a buscar el siguiente. Ret es realmente el siguiente punto
   //cout << "fin de visitas? " << fin_visitas() << endl;
         //int cont = 0;
         //int siguiente = 0;
         //float coste = 0.0;
         precogida ret;
         int demanda = 0;
         unsigned int i = 0;
         unsigned int cont = 0;
         while (!fin_visitas() && cont < vecs.size() * 2) {
            //cout << "vecs size: " << vecs.size() << endl;
            while (i < vecs.size() && !fin_visitas()) {
                //cout << "i: " << i << endl;
                //cout << "vehiculo: " << vecs[i].getid() << ", ultimo visitado: " << vecs[i].get_ultimo() << ", siguiente punto: " << ret.getid() << endl;
                //cin.get();
                ret = candidatos(vecs[i].get_ultimo());
                //cout << "candidato: " << ret.getid() << endl;
                //cout << "demanda del punto: " << ret.getdemanda() << endl;
                //cout << "Carga actual del vehículo: " << vecs[i].getcarga_actual() << ", carga maxima del vehiculo: " << vecs[i].getcarga_max() << endl;
                //cin.get();

                demanda = ret.getdemanda();
                //cout << "vehiculo: " << vecs[i].getid() << ", ultimo visitado: " << vecs[i].get_ultimo() << ", punto candidato: " << ret.getid() << ", demanda del punto: " << demanda <<  endl;
            	if (vecs[i].getcarga_actual()+demanda <= vecs[i].getcarga_max()) { //si la carga actual del vehiculo sumada a la que vamos a introducir es menor o igual, lo visita
                   //cout << "entra if" << endl;
            	  insertar_visitado(ret.getid()); //lo marcamos como visitado para descartarlo de la seleccion de puntos factibles
            	  //cout << "distancia: " << ret.getdistancia() << endl;
            	  //cout << "d: " << getdistanciaij(vecs[i].get_ultimo(), ret.getid());
                  vecs[i].sumar_coste(ret.getdistancia());
                  vecs[i].sumar_carga(demanda);
                  vecs[i].insertar(ret.getid());
                  cont = 0;
            	}
            	else {
            		cont++;
            		//cout << "cont: " << cont << endl;
            	}
                i++;

            }
            i = 0;
         }
         for (unsigned int i = 0; i < vecs.size(); i++) {
            if (vecs[i].enuso()) {
         	   vecs[i].sumar_coste(getdistanciaij(vecs[i].get_ultimo(),0));
               vecs[i].insertar(0);
            }
         }
   if (fin_visitas())
      return true;
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
   vehiculos= r.vehiculos;
   rt = r.rt;
   coste_total = r.coste_total;
   cmed = 0;

};

resolver :: ~resolver() {
   vehiculos.clear();
   delete rt;
};

bool resolver :: ejecutar() {
   bool resuelto;
   resuelto = rt->buscar(vehiculos);
   for (unsigned int i = 0; i < vehiculos.size(); i++)
       coste_total+=vehiculos[i].get_coste();
   return resuelto;
};

float resolver :: get_coste_total() {
	//cout << "LLamada Get coste total: " << coste_total << endl;
	//cin.get();
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
void optimo :: repetir (int n, char delimitador, string salida) {
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
	  if (sol->ejecutar()) { // si devuelve true es porque se ha conseguido visitar todos los puntos

		  //cout << "Sol->getcoste... " << sol->get_coste_total() << " VS " << menor->get_coste_total() << endl;
		  //gettimeofday(&fin, NULL);
		  //double tiempo = ((fin.tv_sec+(float)fin.tv_usec/1000000)-(inicio.tv_sec+(float)inicio.tv_usec/1000000));
		  //t2 = clock();
		  gettimeofday(&endTime, NULL);
		  //double tiempo = (double)(t2 - t1) / CLOCKS_PER_SEC;
		  tiempo += timeval_diff(&endTime, &iniTime);
		  if (sol->get_coste_total() < menor_coste) {
			 //cout << "---> Se ha encontrado una mejor" << endl;
			// menor =  sol;
			 gettimeofday(&parcialtime, NULL);
			 mejortiempo = timeval_diff(&parcialtime,&iniTime);
			 mejorit = i;
			 mejortiempo = tiempo;
			 mejor_ruta = sol->get_ruta_total();
			 menor_coste = sol->get_coste_total();
			 nvehiculos = sol->get_vehiculosusados();
		  }
		  ss << i << delimitador << tiempo << delimitador << sol->get_ruta_total() << delimitador << sol->get_coste_total() << delimitador << sol->get_vehiculosusados() << endl;

	  }
	  else
	    ss << "No se encontro solucion" << endl;
	  delete sol;
	  //cout << "Iteracion: " << i << endl;
   };
   gettimeofday(&endTimetot,NULL);
   out << "Iteracion_mejor_solucion" << delimitador << "tiempo" << delimitador << "ruta" << delimitador << "coste" << delimitador << "numero_vehiculos_usados" << endl;
   out << mejorit << delimitador << mejortiempo << delimitador << mejor_ruta << delimitador << menor_coste << delimitador << nvehiculos << endl;
   out << "Numero_iteracion" << delimitador << "tiempo" << delimitador << "ruta" << delimitador << "coste" << delimitador << "numero_vehiculos_usados" << endl;
   out << ss.str();
   out << timeval_diff(&endTimetot,&iniTimetot);
   cout << "Tiempo total: " << timeval_diff(&endTimetot,&iniTimetot) << " segundos" << endl;
   out.close();
   //cout << "Iteracion del mejor: " << mejorit << endl;
   //cout << "El mejor: " << menor->get_coste_total() << endl;
   //cout << "ruta: " << menor->get_ruta() << endl;
};
