//TDA LISTA ENLAZADA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estructuras
typedef struct Nodo
{
	//Elemento que quiero almacenar
	char * cadena ;
	//Siguiente elemento
	struct Nodo * siguiente;
	
} Nodo;
typedef struct Lista
{
	Nodo * cabeza; 
}Lista;

//CONSTRUCTORES
Nodo * crearNodo(char * cadena)
{
	//Creo un nodo
	Nodo * nodo =(Nodo*)malloc(sizeof (Nodo));
	//Copia la cadena en el nodo
	strcpy(nodo->cadena,cadena);
	nodo->siguiente= NULL;
	return nodo;
}

//Funcion que elimina un nodo
void borrarNodo(Nodo * nodo )
{
	free (nodo);
}
//MODIFICADORES
//Función que inserta al inicio de la lista un nuevo elemento
//Dominio : struct lista, cadena
//Recorrido : struct lista
void insertarAlInicio(Lista *lista ,char * cadena)
{
	//Creamos un nodo a partir de la cadena dada
	Nodo * nodo = crearNodo (cadena);
	nodo->siguiente = lista->cabeza; 
	lista->cabeza = nodo;
}

//Función que añade al final de la lista
//Dominio : struct lista, cadena
//Recorrido : struct lista
void insertarAlFinal (Lista * lista , char * cadena)
{
	//Creamos un nodo a partir de la cadena dada
	Nodo * nodo = crearNodo (cadena);
	//Antes de iterar pregunto acaso si la lista no esta vacía
	if (lista->cabeza != NULL)
	{
		Nodo * puntero = lista->cabeza; 
		while (puntero->siguiente)
		{
			puntero = puntero->siguiente;
		}
		puntero->siguiente = nodo; 
	}
	else
	{
		lista->cabeza = nodo ;
	}
}
void insertarDespues (int n , Lista * lista , char * cadena)
{
	Nodo * nodo = crearNodo (cadena) ;
	//Pregunto acaso si mi lista esta vacía
	if (lista->cabeza == NULL)
	{
		lista->cabeza = nodo;
	}
	else
	{
		Nodo * puntero = lista->cabeza;
		int i=0;
		//Si llego a mi n o al final de la lista
		while(i<n && puntero ->siguiente)
		{
			puntero = puntero->siguiente;
			i++;
		}
		//Ahora que he llegado a mi numero deseado
		//Primero hago que mi nodo que quiero insertar apunte al nodo siguiente donde se apuntaba antes
		nodo->siguiente = puntero->siguiente;
		//Y el puntero anterior ahora apunta a mi nuevo nodo insertado
		puntero->siguiente = nodo;
	}
}
//Selectores
//Función que obtenga una cadena en cierta posicion
//Entradas : 
//Recorrido :
char *  obtenerCadena ()
{
	
}
//Otras funciones
int main()
{
	printf("Hola\n");
	return 0;
}
