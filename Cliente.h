#ifndef Cliente_h
#define Cliente_h

#include "ListaChats.h"
#include "Servidor.h"

using namespace std;

typedef struct{
	string identificador;
	tListaChats listaChats;
}tCliente;

void inicializarCliente(tCliente &cliente);

void cargarCliente(tCliente &cliente, int identificador,tServidor &servidor);

void actualizarBuzonMensajes(tCliente &cliente,tPtrDatosUsuario &Usuario);

void cargarMensajeBuzon(tCliente &cliente,tPtrDatosUsuario Usuario,int posicion,int i);

void cargarMensajeBuzonNuevo(tCliente &cliente,tPtrDatosUsuario Usuario,int i);

void guardarChatCliente(tCliente cliente);

void introducirNuevoChatEnCliente(tCliente &cliente,tServidor &servidor);

void usarChat(tChat &chat, tServidor &servidor);

void destruirDatosCliente(tCliente &cliente);
#endif