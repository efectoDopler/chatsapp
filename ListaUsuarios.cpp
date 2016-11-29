#include <iostream>

using namespace std;

#include "ListaUsuarios.h"
#include <fstream>

void inicializarLista(tListaUsuarios &listaUsuarios){
	tDatosUsuario UsuarioAux;

	for(int i = 0; i < MaxUsuarios; i++){
		listaUsuarios.datosUsuario[i]= new tDatosUsuario (UsuarioAux);
		inicializarUsuario(listaUsuarios.datosUsuario[i]);
	}
	listaUsuarios.contador = 0;
}

void cargarLista(tListaUsuarios &listaUsuarios,ifstream &archivo){
	string usuario;

	archivo >> usuario;
	while((!archivo.eof())) {
		inicializarUsuario(listaUsuarios.datosUsuario[listaUsuarios.contador]);
		cargaUsuario(listaUsuarios.datosUsuario[listaUsuarios.contador],archivo,usuario);
		listaUsuarios.contador++;
		archivo >> usuario;
	}
}

void guardarLista(tListaUsuarios listaUsuarios){
	ofstream archivo;
	int contador = 0;

	archivo.open("usuarios.txt");

	do{
			guardaUsuario(listaUsuarios.datosUsuario[contador], archivo);
			contador++;

	}while(contador < listaUsuarios.contador);
	
	archivo.close();
}

int buscarEnLista(string nombre, tListaUsuarios listaUsuarios) {
	bool encontrado = false;
	int pos, cont = 0;
	
	while((!encontrado)&&(cont < MaxUsuarios)) {
		if(nombre == listaUsuarios.datosUsuario[cont]->usuario) {
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

void destruirListaUsuarios(tListaUsuarios &listaUsuarios){

	for(int i = MaxUsuarios-1; i > -1; i--){
		delete listaUsuarios.datosUsuario[i];
	}
		listaUsuarios.contador = 0;
}