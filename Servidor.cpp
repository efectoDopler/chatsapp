// Jose J. Escudero Gómez (1º C)
#include <iostream>
#include <fstream>

using namespace std;

#include "Servidor.h"
#include "Cliente.h"


int main(){
	tServidor servidor;
	tCliente cliente;
	ifstream archivo;
	int identificador;
	char opcion,opcion2;
	int numChat;
	bool salir = false;

	archivo.open("usuarios.txt");

	if(archivo.is_open()){
		inicializarLista(servidor.usuarios);
		cargarLista(servidor.usuarios,archivo);
		archivo.close();

		do{

			if(login(identificador,servidor.usuarios,salir)){
				cargarCliente(cliente,identificador,servidor);
				obtenerNuevosMensajes(servidor, cliente.listaChats, cliente.identificador);

				do{
					system("cls");
					mostrarChats(cliente.listaChats,cliente.identificador);
					menu();
					cin >> opcion;

					switch(opcion){
				
						case 'n':
							introducirNuevoChatEnCliente(cliente,servidor);break;
						 

						case 'c':{
							cin >> numChat;
							if(numChat <= cliente.listaChats.contador){ 
								system("cls");
								usarChat(cliente.listaChats.chats[numChat], servidor);
								ordenarPorFecha(cliente.listaChats);
							}

							else {
								cout << "Numero de chat inexistente" << endl;
							}

							break; }

						case 'e':{
							cin >> numChat;
							if(numChat < cliente.listaChats.contador){
								borrarChatLista(cliente.listaChats,numChat);
							}

							else{
								cout << "No existe ese chat" << endl;
								system("pause");
							}

							break;
						}
					
						case 'o': {
							cin >> opcion2;

							switch(opcion2){

								case 'f':ordenarPorFecha(cliente.listaChats); break;
						
								case 'n':ordenarPorNombre(cliente.listaChats);break;

								default:{ 
									cout << " Opcion no contemplada." << endl;
									system("pause");
									break;
								}
								break;
							}
						}
			
						case 's':{
							guardarChatCliente(cliente);
							guardarLista(servidor.usuarios);
							break;
						}

						default: cout << " Opcion invalida!" << endl; break;
					}

					cin.sync();
				}while(opcion != 's');

				destruirDatosCliente(cliente);
			}

	}while(!salir);

		destruirDatosServidor(servidor);
	}

	else{
		cout << " Se ha producido un fallo a la hora de cargar el txt" << endl;
	}

	return 0;
}

bool login(int &identificador, tListaUsuarios listaUsuarios,bool &salir){
	string usuario;
	bool encontrado = false;

	cout << " Introduce el nombre del usuario (pon salir para salir): ";
	cin >> usuario;

	identificador = buscarEnLista(usuario,listaUsuarios);

	if(identificador == -1 && usuario != "salir"){
		cout << " Usuario inexistente." << endl;
		encontrado = false;
	}

	else{
		encontrado = true;
	}

	if(usuario == "salir"){
		encontrado = false;
		salir = true;
	}

	return encontrado;
}

void menu(){

	cout << "____________________________________________________________________________" << endl;
	cout << " Entrar al chat N: c N (intro)                   Crear nuevo chat: n (intro)" << endl;
	cout << " Eliminar el chat N: e N (intro)       Ordenar chats por nombre: o n (intro)" << endl;
	cout << " Ordenar chats por fecha: o f (intro)						 salir: s (intro)" << endl;
	cout << "____________________________________________________________________________" << endl;
	cout << " * Opcion: ";
}

void actualizarServidor(tServidor &servidor,tListaMensajes listaMensajes,int posServidor){
	int contador = servidor.usuarios.datosUsuario[posServidor]->listaMensajes.cont;
	int contador2 = listaMensajes.cont-1;
	int nuevaCapacidad;

	servidor.usuarios.datosUsuario[posServidor]->listaMensajes.arrayMensajes[contador] = listaMensajes.arrayMensajes[contador2];
	servidor.usuarios.datosUsuario[posServidor]->listaMensajes.cont++;

	if(servidor.usuarios.datosUsuario[posServidor]->listaMensajes.cont >= servidor.usuarios.datosUsuario[posServidor]->listaMensajes.capacidad){
		nuevaCapacidad = (servidor.usuarios.datosUsuario[posServidor]->listaMensajes.capacidad*3)/2+1;
		redimensionarListaMensajes(servidor.usuarios.datosUsuario[posServidor]->listaMensajes,nuevaCapacidad);
	}

}

void enviarMensaje(tServidor &servidor, tMensaje mensaje) {
	
	int posicion = buscarEnLista(mensaje.receptor, servidor.usuarios);

	if(posicion == -1) cout << "Usuario no inexistente" << endl;

	else {
		añadirMensaje(mensaje, servidor.usuarios.datosUsuario[posicion]->listaMensajes);
	}
}

void obtenerNuevosMensajes(tServidor &servidor, tListaChats &listaChats, string cliente) {

	tMensaje mensajeAux;
	int posicion, posicionChat,nuevaCapacidad;
	posicion = buscarEnLista(cliente, servidor.usuarios);

	for(int cont = 0; cont < servidor.usuarios.datosUsuario[posicion]->listaMensajes.cont; cont++) {
		if(servidor.usuarios.datosUsuario[posicion]->listaMensajes.cont >= servidor.usuarios.datosUsuario[posicion]->listaMensajes.capacidad){
			nuevaCapacidad = (listaChats.chats[posicion].listaMensajes.capacidad*3)/2+1;
			redimensionarListaMensajes(listaChats.chats[posicion].listaMensajes,nuevaCapacidad);
		}
		mensajeAux = servidor.usuarios.datosUsuario[posicion]->listaMensajes.arrayMensajes[cont];
		posicionChat = buscarChat(listaChats, cliente);
		añadirMensaje(mensajeAux, listaChats.chats[posicionChat].listaMensajes);
	}

	borrarLista(servidor.usuarios.datosUsuario[posicion]->listaMensajes);
}

void destruirDatosServidor(tServidor &servidor){
	destruirListaUsuarios(servidor.usuarios);
}