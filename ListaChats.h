#ifndef ListaChats_h
#define ListaChats_h

#include "Chat.h"

using namespace std;

const int MaxChats = 10;

typedef tChat *tPtrChat;

typedef struct{
	tPtrChat chats;
	int capacidad;
	int contador;
}tListaChats;

void inicializarListaChat(tListaChats &listaChats);

void redimensionarListaChats(tListaChats &listaChats, int numero);

void cargarListasChat(ifstream &archivo, tListaChats &listaChats,string usuario);

void guardarListasChat(ofstream &archivo, tListaChats listaChats);

void mostrarChats(tListaChats listaChats,string nombre);

void insertarEnLista(tListaChats &listaChats,string id);

int buscarChat(tListaChats listaChats, string nombre);

void ordenarPorFecha(tListaChats &listaChats);

void ordenarPorNombre(tListaChats &listaChats);

void borrarChatLista(tListaChats &listaChats,int numChat);

void destruirListaChats(tListaChats &listaChats);


#endif