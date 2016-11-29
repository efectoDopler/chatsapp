#ifndef Servidor_h
#define Servidor_h

#include "ListaUsuarios.h"
#include "ListaChats.h"

using namespace std;

typedef struct{
	tListaUsuarios usuarios;
}tServidor;

int main();

bool login(int &identificador, tListaUsuarios listaUsuarios,bool &salir);

void menu();

void actualizarServidor(tServidor &servidor,tListaMensajes listaMensajes,int posServidor);

void enviarMensaje(tServidor &servidor, tMensaje mensaje);

void obtenerNuevosMensajes(tServidor &servidor, tListaChats &listaChats, string cliente);

void destruirDatosServidor(tServidor &servidor);

#endif