#include <iostream>

using namespace std;

#include "ListaMensajes.h"
#include <fstream>

void inicializarMensajes(tListaMensajes &listaMensajes) {
	listaMensajes.capacidad = MaxMensajes;
	listaMensajes.arrayMensajes = new tMensaje[listaMensajes.capacidad];
	listaMensajes.cont = 0;
}

void redimensionarListaMensajes(tListaMensajes &listaMensajes, int numero){
	tPtrMensaje MensajeAux;

	MensajeAux = new tMensaje[numero];

	for(int i = 0; i < listaMensajes.capacidad; i++){
		MensajeAux[i] = listaMensajes.arrayMensajes[i];
	}
	delete [] listaMensajes.arrayMensajes;

	listaMensajes.arrayMensajes = MensajeAux;
	listaMensajes.capacidad = numero;
}

bool estadoListaUsuario (tListaMensajes listaMensajes){
	bool llena = false;

	if(listaMensajes.cont == 0){
		llena = false;
	}

	else{
		llena = true;
	}
	
	return llena;
}

void añadirMensaje(tMensaje mensaje, tListaMensajes &listaMensajes) {
	int nuevaCapacidad;

	if(listaMensajes.cont >= listaMensajes.capacidad){
				nuevaCapacidad = (listaMensajes.capacidad*3)/2+1;
				redimensionarListaMensajes(listaMensajes,nuevaCapacidad);
			}

	listaMensajes.arrayMensajes[listaMensajes.cont] = mensaje;
	listaMensajes.cont++;
}

void consultarUltimoElem(tListaMensajes listaMensajes) {
	mostrarMensaje(listaMensajes.arrayMensajes[listaMensajes.cont-1]);
}

void cargarEnLista(tListaMensajes &listaMensajes, ifstream &archivo,string nombre) {
	int nuevaCapacidad;

	if(listaMensajes.cont != 0){

		for (int cont = 0; cont < listaMensajes.cont; cont++){

			if(listaMensajes.cont >= listaMensajes.capacidad){
				nuevaCapacidad = (listaMensajes.capacidad*3)/2+1;
				redimensionarListaMensajes(listaMensajes,nuevaCapacidad);
			}

			cargarMensaje(listaMensajes.arrayMensajes[cont],archivo,nombre);
		}
	}
}

void borrarLista(tListaMensajes &listaMensajes){
	listaMensajes.cont = 0;
}

 void guardarLista(tListaMensajes listaMensajes, ofstream &archivo) {

	 for(int cont = 0; cont < listaMensajes.cont; cont++) {
		 guardarMensaje(listaMensajes.arrayMensajes[cont], archivo);
		 archivo << endl;
	 }
 }

 bool comprobarListasMensajesFecha(tListaMensajes listaMensajes1, tListaMensajes listaMensajes2){
	bool menor = false;
	int cont = listaMensajes1.cont-1;
	int cont2 = listaMensajes2.cont-1;

	if(listaMensajes1.arrayMensajes[cont].fecha<listaMensajes2.arrayMensajes[cont2].fecha){
		menor = true;
	}

	else{
		menor = false;
	}

	return menor;
 }