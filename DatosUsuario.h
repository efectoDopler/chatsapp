#ifndef DatosUsuario_h
#define DatosUsuario_h

#include "ListaMensajes.h"
#include <string>

using namespace std;

typedef struct {
	string usuario;
	tListaMensajes listaMensajes;
} tDatosUsuario;

typedef tDatosUsuario *tPtrDatosUsuario;

//Completada 100%

void inicializarUsuario(tPtrDatosUsuario &DatosUsuario);

//Creo que esta cargando mal el txt por el modulo ListaMensajes, revisarlo con urda

void cargaUsuario(tPtrDatosUsuario &DatosUsuario, ifstream &archivo, string usuario);

//Completada 100%

void guardaUsuario(tPtrDatosUsuario DatosUsuario, ofstream &archivo);

bool estadoUsuario(tPtrDatosUsuario DatosUsuario);

#endif