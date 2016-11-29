#include <iostream>

using namespace std;

#include "Cliente.h"
#include <fstream>

void inicializarCliente(tCliente &cliente){
	inicializarListaChat(cliente.listaChats);
}

void cargarCliente(tCliente &cliente, int identificador,tServidor &servidor){
	ifstream archivo;
	string fichero;

	cliente.identificador = servidor.usuarios.datosUsuario[identificador]->usuario;
	fichero = cliente.identificador+"_chats.txt";
	archivo.open(fichero);
	inicializarListaChat(cliente.listaChats);
	cargarListasChat(archivo, cliente.listaChats,cliente.identificador);
	actualizarBuzonMensajes(cliente,servidor.usuarios.datosUsuario[identificador]);
	ordenarPorNombre(cliente.listaChats);
	archivo.close();
}

void actualizarBuzonMensajes(tCliente &cliente,tPtrDatosUsuario &Usuario){
	int i = 0, posicion;

	if(estadoUsuario(Usuario)){

		do{
			posicion = buscarChat(cliente.listaChats,Usuario->listaMensajes.arrayMensajes[i].emisor);

			if(posicion != -1){
					cargarMensajeBuzon(cliente,Usuario,posicion,i);
			}

			else{
				cargarMensajeBuzonNuevo(cliente,Usuario,i);
			}

			i++;
		}while(i < Usuario->listaMensajes.cont);
		borrarLista(Usuario->listaMensajes);
	}
}

void cargarMensajeBuzon(tCliente &cliente,tPtrDatosUsuario Usuario,int posicion,int i){
		int nuevaCapacidad;

		if(cliente.listaChats.chats[posicion].listaMensajes.cont >= cliente.listaChats.chats[posicion].listaMensajes.capacidad){
			nuevaCapacidad = (cliente.listaChats.chats[posicion].listaMensajes.capacidad*3)/2+1;
			redimensionarListaMensajes(cliente.listaChats.chats[posicion].listaMensajes,nuevaCapacidad);
		}

		cliente.listaChats.chats[posicion].listaMensajes.arrayMensajes[cliente.listaChats.chats[posicion].listaMensajes.cont] = Usuario->listaMensajes.arrayMensajes[i];
		cliente.listaChats.chats[posicion].listaMensajes.cont++;
}

void cargarMensajeBuzonNuevo(tCliente &cliente,tPtrDatosUsuario Usuario,int i){
	
	iniciarChat(cliente.listaChats.chats[cliente.listaChats.contador]);
	cliente.listaChats.chats[cliente.listaChats.contador].emisor = cliente.identificador;
	cliente.listaChats.chats[cliente.listaChats.contador].receptor = Usuario->listaMensajes.arrayMensajes[i].emisor;
	cliente.listaChats.chats[cliente.listaChats.contador].listaMensajes.arrayMensajes[cliente.listaChats.chats[cliente.listaChats.contador].listaMensajes.cont] = Usuario->listaMensajes.arrayMensajes[i];
	cliente.listaChats.chats[cliente.listaChats.contador].listaMensajes.cont++;

	cliente.listaChats.contador++;
}

void guardarChatCliente(tCliente cliente){
	ofstream archivo;
	string fichero;

	fichero = cliente.identificador+"_chats.txt";
	archivo.open(fichero);
	guardarListasChat(archivo,cliente.listaChats);
	archivo.close();
}

void introducirNuevoChatEnCliente(tCliente &cliente,tServidor &servidor){
	string id;
	int posicionServidor, posicionChat;
	int nuevaCapacidad;

	cout << " Introduce la id del usuario con la que crear un nuevo chat: ";
	cin >> id;
	posicionServidor = buscarEnLista(id,servidor.usuarios);

	if( posicionServidor == -1){
		cout << " El Id del usuario introducido no existe en el servidor." << endl;
		system("pause");
	}

	else{
		posicionChat = buscarChat(cliente.listaChats,id);

		if(posicionChat != -1){
			cout << " Ya existe un chat con el usuario " << id <<"." << endl;
			system("pause");
		}

		else{
			if(cliente.listaChats.contador != 0){

				if(cliente.listaChats.contador >= cliente.listaChats.capacidad){
					nuevaCapacidad = (cliente.listaChats.capacidad*3)/2+1;
					redimensionarListaChats(cliente.listaChats,nuevaCapacidad);
				}

				insertarEnLista(cliente.listaChats,id);
				posicionChat = cliente.listaChats.contador-1;
				actualizarServidor(servidor,cliente.listaChats.chats[posicionChat].listaMensajes,posicionServidor);
			}
			else{
				insertarEnLista(cliente.listaChats,id);
				posicionChat = 0;
				actualizarServidor(servidor,cliente.listaChats.chats[posicionChat].listaMensajes,posicionServidor);
			}
		}
	}
}

void usarChat(tChat &chat, tServidor &servidor) {
	bool finalChat = false;
	tMensaje mensajeAux;
	string texto;
	int nuevaCapacidad;

	while(!finalChat) {
		mostrarChat(chat, texto);
		
		if (chat.listaMensajes.cont >= chat.listaMensajes.capacidad){
			nuevaCapacidad = (chat.listaMensajes.capacidad*3)/2+1;
			redimensionarListaMensajes(chat.listaMensajes,nuevaCapacidad);
		}

		if(texto == "$salir$"){ 
			finalChat = true;
		}

		else {
			mensajeAux = crearMensajeNuevo(chat.emisor,chat.receptor,texto);

			//Guardo el mensaje en el buzon del receptor
			enviarMensaje(servidor, mensajeAux);
			//Tambien lo guardo en el chat correspondiente
			añadirMensaje(mensajeAux, chat.listaMensajes);
			system("cls");
		}
	}
}



void destruirDatosCliente(tCliente &cliente) {
	destruirListaChats(cliente.listaChats);
}