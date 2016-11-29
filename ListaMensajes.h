#ifndef ListaMensajes_h
#define ListaMensajes_h

#include "mensaje.h"

using namespace std;

const int MaxMensajes = 2;

typedef tMensaje *tPtrMensaje;

typedef struct {
	tPtrMensaje arrayMensajes;
	int capacidad;
	int cont;
} tListaMensajes;


void inicializarMensajes(tListaMensajes &listaMensajes);

void redimensionarListaMensajes(tListaMensajes &listaMensajes, int numero);

bool estadoListaUsuario (tListaMensajes listaMensajes);

void añadirMensaje(tMensaje mensaje, tListaMensajes &listaMensajes);

void consultarUltimoElem(tListaMensajes listaMensajes);

void cargarEnLista(tListaMensajes &listaMensajes, ifstream &archivo,string nombre);

void borrarLista(tListaMensajes &listaMensajes);

void guardarLista(tListaMensajes listaMensajes, ofstream &archivo);

 bool comprobarListasMensajesFecha(tListaMensajes listaMensajes1, tListaMensajes listaMensajes2);

#endif