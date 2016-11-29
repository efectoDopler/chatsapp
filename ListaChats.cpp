#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "ListaChats.h"


void inicializarListaChat(tListaChats &listaChats) {
	listaChats.capacidad = MaxChats;
	listaChats.chats = new tChat [listaChats.capacidad];
	listaChats.contador = 0;
	iniciarChat(listaChats.chats[listaChats.contador]);
}

void redimensionarListaChats(tListaChats &listaChats, int numero){
	tPtrChat chatAux;

	chatAux = new tChat[numero];

	for(int i = 0; i < listaChats.capacidad; i++){
		chatAux[i] = listaChats.chats[i];
	}
	delete [] listaChats.chats;

	listaChats.chats = chatAux;
	listaChats.capacidad = numero;
}


void cargarListasChat(ifstream &archivo, tListaChats &listaChats,string emisor) {
	string receptor;
	int nuevaCapacidad;
	int contador = 0;

	archivo >> contador;
	archivo >> receptor;

	if(contador == 0){
		listaChats.chats[0].emisor = emisor;
	}

	for(int i = 0; i < contador; i++) {
		if(listaChats.contador >= listaChats.capacidad){
			nuevaCapacidad = (listaChats.contador/10)*2;

			if(nuevaCapacidad < 10){
				nuevaCapacidad = 10;
			}

			redimensionarListaChats(listaChats,nuevaCapacidad);
		}
		cargarChat(archivo, listaChats.chats[listaChats.contador], receptor, emisor);
		listaChats.contador++;

		archivo >> receptor;
	}
}

void guardarListasChat(ofstream &archivo, tListaChats listaChats) {

	archivo << listaChats.contador << endl;
	for(int  cont = 0; cont < listaChats.contador; cont++) {
		guardarChat(archivo,listaChats.chats[cont]);
	}
}

void mostrarChats(tListaChats listaChats,string nombre){

	cout << "____________________________________________________________________________" << endl;
	cout << "                      CHATSAPP 2.0: Chats de " << nombre << endl;
	cout << "____________________________________________________________________________" << endl;
	
	for(int i = 0; i < listaChats.contador; i++){
		 mostrarCabecera(listaChats.chats[i],i);
	}
}

void insertarEnLista(tListaChats &listaChats,string id){
	string emisor;

	if(listaChats.contador != 0){
		emisor = listaChats.chats[listaChats.contador-1].emisor;
	}

	else{
		emisor = listaChats.chats[listaChats.contador].emisor;
	}

	listaChats.chats[listaChats.contador].receptor = id;
	listaChats.chats[listaChats.contador].emisor = emisor;
	inicializarMensajes(listaChats.chats[listaChats.contador].listaMensajes);
	MensajeInicial(listaChats.chats[listaChats.contador].listaMensajes.arrayMensajes[0],emisor,id);
	listaChats.chats[listaChats.contador].listaMensajes.cont++;
	listaChats.contador++;
}

int buscarChat(tListaChats listaChats, string nombre) {
	bool encontrado = false;
	int pos, cont = 0;
	
	while((!encontrado)&&(cont < MaxChats)) {
		if(nombre == listaChats.chats[cont].receptor) {
			encontrado = true;
			pos = cont;
		}
		cont++;
	}
	if(!encontrado){ 
		pos = -1;
	}
	
	return pos;
}

void ordenarPorFecha(tListaChats &listaChats){
	tChat chatTmp;

	for(int i = 0; i < listaChats.contador-1; i++){
		for(int j = listaChats.contador-1; j > i; j--){

			if(comprobarListasMensajesFecha(listaChats.chats[j].listaMensajes,listaChats.chats[j-1].listaMensajes)){
				chatTmp = listaChats.chats[j];
				listaChats.chats[j] = listaChats.chats[j-1];
				listaChats.chats[j-1] = chatTmp;
			}
		}
	}
}

void ordenarPorNombre(tListaChats &listaChats){
	tChat chatTmp;

	for(int i = 0; i < listaChats.contador-1; i++){
		for(int j = listaChats.contador-1; j > i; j--){

			if(listaChats.chats[j].receptor < listaChats.chats[j-1].receptor){
				chatTmp = listaChats.chats[j];
				listaChats.chats[j] = listaChats.chats[j-1];
				listaChats.chats[j-1] = chatTmp;
			}
		}
	}
}

void borrarChatLista(tListaChats &listaChats,int numChat){

	for(int i = numChat; i < listaChats.contador; i++){
		listaChats.chats[i] = listaChats.chats[i+1];
	}

	listaChats.contador--;
}


void destruirListaChats(tListaChats &listaChats) {

	for(int i = 0; i < listaChats.contador; i++) {
		destruirMensajesChat(listaChats.chats[i]);
	}
	delete []listaChats.chats;
	listaChats.contador = 0;
}