#ifndef Chat_h
#define Chat_h

#include "ListaMensajes.h"

using namespace std;

typedef struct{
	string receptor;
	string emisor;
	tListaMensajes listaMensajes;
}tChat;

void iniciarChat(tChat &chat);

void cargarChat(ifstream &archivo, tChat &chat,string receptor,string emisor);

void guardarChat(ofstream &archivo, tChat chat);

void usarChat(tChat chat,tListaMensajes &listaMensajes);

void mostrarCabecera(tChat chat, int cont);

void mostrarChat(tChat chat, string &mensaje);

void destruirMensajesChat(tChat &chat);

#endif