#include <iostream>
#include <string>
#include <stdlib.h>
#include "C:\Users\Matias\Desktop\Matias\Facultad\1° Año\Algoritmos y Estructura de datos\Curso K1002\1° Cuatrimestre\Z-AlgoritmosProject_1C_EMPTY_v1.9\src\biblioteca\funciones\strings.hpp"
#include "C:\Users\Matias\Desktop\Matias\Facultad\1° Año\Algoritmos y Estructura de datos\Curso K1002\1° Cuatrimestre\Z-AlgoritmosProject_1C_EMPTY_v1.9\src\biblioteca\funciones\tokens.hpp"
#include "C:\Users\Matias\Desktop\Matias\Facultad\1° Año\Algoritmos y Estructura de datos\Curso K1002\1° Cuatrimestre\Z-AlgoritmosProject_1C_EMPTY_v1.9\src\biblioteca\funciones\files.hpp"
#include "C:\Users\Matias\Desktop\Matias\Facultad\1° Año\Algoritmos y Estructura de datos\Curso K1002\1° Cuatrimestre\Z-AlgoritmosProject_1C_EMPTY_v1.9\src\biblioteca\tads\coll.hpp"
using namespace std;

struct Ciudad
{
   int idCiu;
   string descr;
   int millas;
};

struct RCiudad
{
   Ciudad ciu;
   int cont;
};

struct Vuelo
{
   int idVue;
   int cap;
   int idOri; // idCiu origen
   int idDes; // idCiu origen
};

struct RVuelo
{
   Vuelo vue;
   int apa;
   int apr;
};

struct Reserva
{
   int idCli;
   int idVue;
   int cant;
};

string rciudadToString(RCiudad r)
{
   string idCiu = intToString(r.ciu.idCiu);
   string desc = r.ciu.descr;
   string millas = intToString(r.ciu.millas);
   string cont = intToString(r.cont);
   return idCiu+","+desc+","+millas+","+cont;
}

RCiudad rciudadFromString(string s)
{
   RCiudad x;
   x.ciu.idCiu = stringToInt(getTokenAt(s,',',0));
   x.ciu.descr = getTokenAt(s,',',1);
   x.ciu.millas = stringToInt(getTokenAt(s,',',2));
   x.cont = stringToInt(getTokenAt(s,',',3));
   return x;
}

Coll<RCiudad> subirCiudades()
{
   Coll<RCiudad> c = collCreate<RCiudad>();
   FILE* f = fopen("CIUDADES.dat","r+b");

   Ciudad x = read<Ciudad>(f);
   while( !feof(f) )
   {
      RCiudad elm = {x,0};
      collAdd<RCiudad>(c,elm,rciudadToString);
      x = read<Ciudad>(f);
   }

   fclose(f);
   return c;
}

string rvueloToString(RVuelo q){
	
	string idVue = intToString(q.vue.idVue);
	string cap = intToString(q.vue.cap);
	string idOri = intToString(q.vue.idOri);
	string idDes = intToString(q.vue.idDes);
	string apr = intToString(q.apr);
	string apa = intToString(q.apa);
	return idVue+","+cap+","+idOri+","+idDes+","+apa+","+apr;
}

RVuelo rvueloFromString(string s)
{
   RVuelo x;
   x.vue.idVue = stringToInt(getTokenAt(s,',',0));
   x.vue.cap = stringToInt(getTokenAt(s,',',1));
   x.vue.idOri = stringToInt(getTokenAt(s,',',2));
   x.vue.idDes = stringToInt(getTokenAt(s,',',3));
   x.apa = stringToInt(getTokenAt(s,',',4));
   x.apr = stringToInt(getTokenAt(s,',',5));
   return x;
}

Coll<RVuelo> subirVuelos()
{
    Coll<RVuelo> c = collCreate<RVuelo>();
    FILE* f = fopen("VUELOS.dat","r+b");
    
    Vuelo v = read<Vuelo>(f);
    while( !feof(f) ){
    	RVuelo x = {v,0,0};
    	collAdd<RVuelo>(c,x,rvueloToString);	
    	v = read<Vuelo>(f);
	}
    fclose(f);
    return c;
}

struct RCliente
{
   int idCli;
   int acMillas;
};

int cmpRvueloId(RVuelo r,int id){
	return r.vue.idVue-id;
}

RVuelo buscarVuelo(Coll<RVuelo> c,int id)
{
   int pos = collFind<RVuelo,int>(c,id,cmpRvueloId,rvueloFromString);
   return collGetAt<RVuelo>(c,pos,rvueloFromString);
}

int cmpRciudadId(RCiudad r,int id)
{
   return r.ciu.idCiu-id;
}

RCiudad buscarCiudad(Coll<RCiudad> c,int id)
{
   int pos = collFind<RCiudad,int>(c,id,cmpRciudadId,rciudadFromString);
   return collGetAt<RCiudad>(c,pos,rciudadFromString);
}

void actualizarDemandaCiudad(Coll<RCiudad>& c,RCiudad r)
{
   int pos = collFind<RCiudad,int>(c,r.ciu.idCiu,cmpRciudadId,rciudadFromString);
   collSetAt<RCiudad>(c,r,pos,rciudadToString);
}
//hacer
void actualizarPlazasVuelo(Coll<RVuelo>& c,RVuelo r)
{
	int pos = collFind<RVuelo,int>(c,r.vue.idVue,cmpRvueloId,rvueloFromString);
    collSetAt<RVuelo>(c,r,pos,rvueloToString);
}

int cmpRclienteId(RCliente r,int id)
{
   return r.idCli-id;
}

string rclienteToString(RCliente r)
{
    string idCli = intToString(r.idCli);
	string acMillas = intToString(r.acMillas);
	return idCli+","+acMillas;
}

RCliente rclienteFromString(string s)
{
   RCliente x;
   x.idCli = stringToInt(getTokenAt(s,',',0));
   x.acMillas = stringToInt(getTokenAt(s,',',1));
   return x;
}

void actualizarMillasCliente(Coll<RCliente>& c,int id,int millas)
{
   int pos = collFind<RCliente,int>(c,id,cmpRclienteId,rclienteFromString);
   if( pos<0 )
   {
      RCliente x = {id,0};
      pos = collAdd<RCliente>(c,x,rclienteToString);
   }

   RCliente z = collGetAt<RCliente>(c,pos,rclienteFromString);
   z.acMillas+=millas;
   collSetAt<RCliente>(c,z,pos,rclienteToString);
}

//3. Para cada cliente, el total de millas acumuladas.
void mostrarPto3(Coll<RCliente> c)
{
	while( collHasNext<RCliente>(c) )
   {
      RCliente r = collNext<RCliente>(c,rclienteFromString);
      cout << r.idCli <<", " << r.acMillas <<", " << endl;
   }
}
// 1.Para cada ciudad, la cantidad de grupos (familias) que la eligen como destino.
void mostrarPto1(Coll<RCiudad> c)
{
	while( collHasNext<RCiudad>(c) )
   {
      RCiudad r = collNext<RCiudad>(c,rciudadFromString);
      cout << r.cont <<", " << r.ciu.idCiu <<", " << endl;
   }
}
// 2.Por cada vuelo, la cantidad de plazas rechazadas, indicando también si el
// vuelo saldrá completo o incompleto.
void mostrarPto2(Coll<RVuelo> c)
{
   while( collHasNext<RVuelo>(c) )
   {
      RVuelo r = collNext<RVuelo>(c,rvueloFromString);
      string mensaje = (r.vue.cap==r.apa)?"Completo":"Incompleto";
      cout << r.vue.idVue <<", " << r.apr <<", " << mensaje << endl;
   }
}

int main()
{
   // subo las ciudades a memoria
   Coll<RCiudad> cciu = subirCiudades();

   // subo los vuelos
   Coll<RVuelo> cvue = subirVuelos();

   // coleccion de clientes
   Coll<RCliente> ccli = collCreate<RCliente>();

   // abro las novedades, recorro y proceso
   FILE* f = fopen("RESERVAS.dat","r+b");

   Reserva r = read<Reserva>(f);
   while( !feof(f) )
   {
      // busco el vuelo involucrado
      RVuelo rvue = buscarVuelo(cvue,r.idVue);

      // busco las ciudades conectadas por el vuelo
      RCiudad rciuOri = buscarCiudad(cciu,rvue.vue.idOri);
      RCiudad rciuDes = buscarCiudad(cciu,rvue.vue.idDes);

      // actualizo demanda por ciudad
      rciuDes.cont++;
      actualizarDemandaCiudad(cciu,rciuDes);

      // acepto la reserva??
      int plazasDisponibles = rvue.vue.cap-rvue.apa;
      if( r.cant <= plazasDisponibles )
      {
         // acepto la reserva
         rvue.apa+=r.cant;
         actualizarPlazasVuelo(cvue,rvue);

         // millas x cliente
         int millas = abs(rciuOri.ciu.millas-rciuDes.ciu.millas)*r.cant;
         actualizarMillasCliente(ccli,r.idCli,millas);

      }
      else
      {
         // rechazo
         rvue.apr+=r.cant;
         actualizarPlazasVuelo(cvue,rvue);
      }

      r = read<Reserva>(f);
   }

   mostrarPto1(cciu);
   mostrarPto2(cvue);
   mostrarPto3(ccli);

   fclose(f);

   return 0;
}
