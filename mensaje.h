#ifndef mensaje_h
#define mensaje_h

#include <string>
#include <time.h>

using namespace std;


typedef time_t tFecha;

typedef struct{
	string emisor;
	string receptor;
	tFecha fecha;
	string texto;
} tMensaje;

//Muestra la fecha en el formato correcto: COMPLETADA 100%

void mostrarFecha(tFecha fecha);

//Escribe el emisor un mensaje dirigo a un receptor: COMPLETADA 100%

tMensaje crearMensajeNuevo(string emisor,string receptor,string mensaje);	

//Muestra un mensaje enviado en un chat especifico: COMPLETADA 100% 

void mostrarMensaje(tMensaje mensaje);		

void MensajeInicial(tMensaje &mensaje,string emisor,string receptor);

//Carga un mensaje de usuarios.txt de un emisor especifico para el receptor logeado: COMPLETADA 100%

void cargarMensaje(tMensaje &mensaje, ifstream &archivo,string nombre);			

void cargarMensajeVacio(tMensaje &mensaje,string nombre);

// Guarda el mensaje cargado anteriormente y lo guarda en <nombreUsuario>_chats.txt: COMPLETADA 100&

void guardarMensaje(tMensaje mensaje, ofstream &archivo);		

#endif