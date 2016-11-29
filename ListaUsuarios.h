#ifndef ListaUsuarios_h
#define ListaUsuarios_h

#include <iostream>

using namespace std;

#include "DatosUsuario.h"
#include <fstream>

const int MaxUsuarios = 50;

typedef tPtrDatosUsuario tDatosUsuarios[MaxUsuarios];

typedef struct{
	tDatosUsuarios datosUsuario;
	int contador;
}tListaUsuarios;

void inicializarLista(tListaUsuarios &listaUsuarios);

void cargarLista(tListaUsuarios &listaUsuario,ifstream &archivo);

void guardarLista(tListaUsuarios listaUsuarios);

int buscarEnLista(string nombre, tListaUsuarios listaUsuarios);

void destruirListaUsuarios(tListaUsuarios &listaUsuarios);

#endif