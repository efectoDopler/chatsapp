#include <iostream>

using namespace std;

#include "DatosUsuario.h"
#include <fstream>
#include <string>

void inicializarUsuario(tPtrDatosUsuario &DatosUsuario){
	inicializarMensajes(DatosUsuario->listaMensajes);
}

void cargaUsuario(tPtrDatosUsuario &DatosUsuario, ifstream &archivo, string usuario){
	DatosUsuario->usuario = usuario;
	archivo >> DatosUsuario->listaMensajes.cont;
	cargarEnLista(DatosUsuario->listaMensajes,archivo,usuario);
}

void guardaUsuario(tPtrDatosUsuario DatosUsuario, ofstream &archivo){
	archivo << DatosUsuario->usuario << endl;
	archivo << DatosUsuario->listaMensajes.cont << endl;
	guardarLista(DatosUsuario->listaMensajes,archivo);
}

bool estadoUsuario(tPtrDatosUsuario DatosUsuario){
	bool ok = estadoListaUsuario(DatosUsuario->listaMensajes);
	return ok;
}