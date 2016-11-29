#include <iostream>

using namespace std;

#include "mensaje.h"
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include <ctime>


void mostrarFecha(tFecha fecha){
	tm* ltm = localtime(&fecha);

	cout << 1900 + ltm->tm_year << "/" << 1 + ltm->tm_mon << "/" << ltm->tm_mday;
	cout << "," << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec;
}

tMensaje crearMensajeNuevo(string emisor,string receptor,string mensaje){
	tMensaje mensajeNuevo;

	mensajeNuevo.texto = mensaje;
	mensajeNuevo.emisor = emisor;
	mensajeNuevo.receptor = receptor;
	mensajeNuevo.fecha = time(0);
	
	return mensajeNuevo;
}	

void mostrarMensaje(tMensaje mensaje){
	cout << mensaje.emisor << "  ("; mostrarFecha(mensaje.fecha);
	cout << "):" << mensaje.texto;
}

void MensajeInicial(tMensaje &mensaje,string emisor,string receptor){
	mensaje.emisor = emisor;
	mensaje.receptor = receptor;
	mensaje.fecha = time(0);
	mensaje.texto = emisor + " ha iniciado un nuevo chat con " + receptor;
}

void cargarMensaje(tMensaje &mensaje, ifstream &archivo,string nombre){
	archivo >> mensaje.emisor;
	archivo >> mensaje.fecha;
	mensaje.receptor = nombre;
	getline(archivo, mensaje.texto);
}

void cargarMensajeVacio(tMensaje &mensaje,string nombre){
	mensaje.receptor = nombre;
}

void guardarMensaje(tMensaje mensaje, ofstream &archivo){
	archivo << mensaje.emisor << " ";
	archivo << mensaje.fecha << " ";
	archivo << mensaje.texto;
}
