#include <iostream>
using namespace std;

#include "biblioteca/funciones/arrays.hpp"
#include "biblioteca/funciones/files.hpp"
#include "biblioteca/funciones/lists.hpp"
#include "biblioteca/funciones/strings2.hpp"
#include "biblioteca/funciones/tokens.hpp"

#include "biblioteca/tads/Arr.hpp"
#include "biblioteca/tads/Map.hpp"
#include "biblioteca/tads/List.hpp"
#include "biblioteca/tads/Queue.hpp"
#include "biblioteca/tads/Stack.hpp"

#include <stdlib.h>
#include <cstdlib> 
#include <ctime>
#include <cstring>
#include "main.hpp"



int main()
{
	// Obtengo los datos
	Arr<RCiudad> ciudades = subirCiudades();
	Arr<RVuelo> vuelos = subirVuelos();

	// Creo a los clientes
	Arr<Cliente> clientes = arr<Cliente>();

	// abro el archivo reserva y voy procesando
	FILE* f = fopen("Archivos/CompaniaDeAviacion/RESERVAS.dat","r+b");

	Reserva r = read<Reserva>(f);
	while (!feof(f)) {

		RVuelo* rv = buscarVuelo(vuelos, r.idVue);

		RCiudad* rciuOri = buscarCiudad(ciudades, rv->v.idOri);
		RCiudad* rciuDes = buscarCiudad(ciudades, rv->v.idDes);

		rciuDes->cantF++;
		actualizarDemandaCiudad(ciudades, *rciuDes);

		// acepto la reserva??
		int plazasDisponibles = rv->v.cap - rv->apa;
		if (r.cant <= plazasDisponibles)
		{
			// acepto la reserva
			rv->apa += r.cant;
			actualizarPlazasVuelo(vuelos, *rv);

			// millas x cliente
			int millas = abs(rciuOri->c.millas - rciuDes->c.millas) * r.cant;
			actualizarMillasCliente(clientes, r.idCli, millas);

		}
		else
		{
			// rechazo
			rv->apr += r.cant;
			actualizarPlazasVuelo(vuelos, *rv);
		}


		r = read<Reserva>(f);
	}

	mostrarPunto2(ciudades);
	mostrarPunto3(vuelos);
	mostrarPunto1(clientes);

	fclose(f);

	cout<<endl<<endl;
}