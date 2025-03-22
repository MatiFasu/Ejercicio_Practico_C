
struct Ciudad {
	int idCiu;
	char descr[20];
	int millas;
};

struct RCiudad{
	Ciudad c;
	int cantF;
};

struct Vuelo
{
	int idVue;
	int cap;
	int idOri; // idCiu origen
	int idDes; // idCiu origen
};

struct RVuelo {
	Vuelo v;
	int apa;
	int apr;
};

struct Reserva {
	int idCli;
	int idVue;
	int cant;
};

struct Cliente {
	int idCli;
	int millasAcum;
};

// ***************************************

Arr<RCiudad> subirCiudades() {
	Arr<RCiudad> ciudades = arr<RCiudad>();

	FILE* f = fopen("Archivos/CompaniaDeAviacion/CIUDADES.dat","r+b");

	Ciudad c = read<Ciudad>(f);
	while (!feof(f)) {

		RCiudad rc = { c,0 };

		arrAdd<RCiudad>(ciudades, rc);

		c = read<Ciudad>(f);
	}

	fclose(f);

	return ciudades;
}

Arr<RVuelo> subirVuelos() {
	Arr<RVuelo> vuelos = arr<RVuelo>();

	FILE* f = fopen("Archivos/CompaniaDeAviacion/VUELOS.dat", "r+b");

	Vuelo v = read<Vuelo>(f);
	while (!feof(f)) {

		RVuelo rv = { v,0,0 };

		arrAdd<RVuelo>(vuelos, rv);

		v = read<Vuelo>(f);
	}

	fclose(f);

	return vuelos;
}

int cmpRVueloInt(RVuelo rv, int id) {
	return rv.v.idVue - id;
}

RVuelo* buscarVuelo(Arr<RVuelo> vuelos, int idVue) {
	int pos = arrFind<RVuelo, int>(vuelos, idVue, cmpRVueloInt);
	return arrGet<RVuelo>(vuelos, pos);
}

int cmpRCiudadInt(RCiudad rc, int id) {
	return rc.c.idCiu - id;
}

RCiudad* buscarCiudad(Arr<RCiudad> ciudades, int idCiu) {
	int pos = arrFind<RCiudad, int>(ciudades, idCiu, cmpRCiudadInt);
	return arrGet<RCiudad>(ciudades, pos);
}

void actualizarDemandaCiudad(Arr<RCiudad>& ciudades, RCiudad& rc) {
	int pos = arrFind<RCiudad, int>(ciudades, rc.c.idCiu, cmpRCiudadInt);
	arrSet<RCiudad>(ciudades, pos, rc);
}

void actualizarPlazasVuelo(Arr<RVuelo>& vuelos, RVuelo& rv) {
	int pos = arrFind<RVuelo, int>(vuelos, rv.v.idVue, cmpRVueloInt);
	arrSet<RVuelo>(vuelos, pos, rv);
}

int cmpClienteInt(Cliente c, int id) {
	return c.idCli - id;
}

void actualizarMillasCliente(Arr<Cliente>& clientes, int idCli, int millas) {
	int pos = arrFind<Cliente, int>(clientes, idCli, cmpClienteInt);
	if (pos < 0)
	{
		Cliente x = { idCli,0 };
		pos = arrAdd<Cliente>(clientes, x);
	}

	Cliente* z = arrGet<Cliente>(clientes, pos);
	z->millasAcum += millas;
	arrSet<Cliente>(clientes, pos, *z);
}

int cmpClienteCliente(Cliente a, Cliente b) {
	return a.idCli - b.idCli;
}

void mostrarPunto1(Arr<Cliente> clientes) {
	cout << "\n CLIENTES \n" << endl;

	for (int i = 0; i < arrSize<Cliente>(clientes); i++) {

		Cliente* c = arrGet<Cliente>(clientes, i);

		cout << c->idCli << ", " << c->millasAcum << endl;

	}

	cout << endl;
}

void mostrarPunto2(Arr<RCiudad> ciudades) {

	cout << "\n CIUDADES \n" << endl;

	for (int i = 0; i < arrSize<RCiudad>(ciudades); i++) {

		RCiudad* rc = arrGet<RCiudad>(ciudades, i);

		cout << rc->c.idCiu << ", " << rc->c.descr << " -> " << rc->cantF << endl;

	}

	cout << endl;
}
void mostrarPunto3(Arr<RVuelo> vuelos) {

	cout << "\n VUELOS \n" << endl;

	for (int i = 0; i < arrSize<RVuelo>(vuelos); i++) {

		RVuelo* rv = arrGet<RVuelo>(vuelos, i);

		string mensaje = (rv->v.cap == rv->apa) ? "Completo" : "Incompleto";

		cout << rv->v.idVue << ", " << rv->apr << " -> " << mensaje << endl;

	}

	cout << endl;
}

