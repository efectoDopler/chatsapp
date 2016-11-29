#include <iostream>

using namespace std;

#include "Chat.h"
#include <fstream>

void iniciarChat(tChat &chat){
	inicializarMensajes(chat.listaMensajes);
}

void cargarChat(ifstream &archivo, tChat &chat,string receptor, string emisor){
	int nuevaCapacidad;
	chat.receptor = receptor;
	chat.emisor = emisor;
	iniciarChat(chat);
	archivo >> chat.listaMensajes.cont;

	if(chat.listaMensajes.cont >= chat.listaMensajes.capacidad){
		nuevaCapacidad = (chat.listaMensajes.cont*3)/2+1;
		redimensionarListaMensajes(chat.listaMensajes,nuevaCapacidad);
	}

	cargarEnLista(chat.listaMensajes,archivo,chat.emisor);
	/*else{
		cout << " Se ha excedido el maximo de mensajes en este chat.";
	}*/
	
}

void guardarChat(ofstream &archivo, tChat chat) {
	archivo << chat.receptor << endl;
	archivo << chat.listaMensajes.cont << endl;
	guardarLista(chat.listaMensajes,archivo);
}

void mostrarCabecera(tChat chat, int cont) {

	cout << " \t " << cont << " " << chat.receptor << endl;
	cout << " "; consultarUltimoElem(chat.listaMensajes); cout << endl;
	cout << "____________________________________________________________________________" << endl;
}

void mostrarChat(tChat chat, string &mensaje) {

	cout << "____________________________________________________________________________" << endl;
	cout << "                      CHAT CON " << chat.receptor << endl;
	cout << "____________________________________________________________________________" << endl;

	for(int i = 0; i < chat.listaMensajes.cont; i++) {

		if(chat.receptor == chat.emisor) {
			//Esto deberia aparecer en el lado derecho de la pantalla pero como no se hacerlo lo tabulo
			cout << "\t"; mostrarMensaje(chat.listaMensajes.arrayMensajes[i]); cout << endl;
			cout << "____________________________________________________________________________" << endl;
		}

		else {
			mostrarMensaje(chat.listaMensajes.arrayMensajes[i]); cout << endl;
			cout << "____________________________________________________________________________" << endl;
		}
	}

	cout << "____________________________________________________________________________" << endl;
	cout << "Escribe aqui ($salir$ para salir): "; 
	cin.sync();
	getline(cin, mensaje); cout << endl;
}


void destruirMensajesChat(tChat &chat) {
	delete []chat.listaMensajes.arrayMensajes;
	chat.listaMensajes.cont = 0;
}