//TDA LISTA ENLAZADA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estructuras
typedef struct Nodo
{
	//Elemento que quiero almacenar
	char cadena [50];
	//Largo de la cadena
	int largo;
	//Siguiente elemento
	struct Nodo * siguiente;	
} Nodo;

typedef struct Lista
{
	//Elemento Nodo cabeza
	Nodo * cabeza; 
	// Largo de la lista
	int largo;
}Lista;

typedef struct {
	//Palabra a la cual le buscamos la 
    char palabra[30];
    //Largo de la palabra
    int largoPalabra;
    //Lista enlazada donde se almacenan las subcadenas
    Lista * subcadenas;
}palabra;

//HEADER
int estaEnListaEnlazada(Lista * lista , char * cadena);


//CONSTRUCTORES
//Función que crea un nodo
//Entrada : string
//Salida : Nodo
Nodo * crearNodo(char * cadena)
{
	//Creo un nodo
	Nodo * nodo =(Nodo*)malloc(sizeof (Nodo));
	//Se copia la cadena en el nodo
	strcpy(nodo->cadena,cadena);
	nodo->largo=strlen(cadena);
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
void insertarAlInicio(Lista * lista ,char * cadena)
{
	//Creamos un nodo a partir de la cadena dada
	Nodo * nodo = crearNodo (cadena);
	//Primero pregunto si la lista esta vacía
	if (lista->cabeza == NULL)
	{
		lista->cabeza = nodo ;
		lista->largo = 1;
	}
	//Si no es nulo
	else{
		nodo->siguiente = lista->cabeza; 
		lista->cabeza = nodo;
		lista->largo = lista->largo + 1;
	}
}

//Función que agrega subcadenas según el orden que le corresponda
void insertarSegunCorresponda(palabra P, char * subcadena)
{
	//Antes pregunto si la subcadena no se encuentra dentro de la subcadena
	if (estaEnListaEnlazada(P.subcadenas ,subcadena) ==1)
	{
		//Creo mi nuevo nodo a agregar
		Nodo * nodo = crearNodo (subcadena);
		//Antes que nada pregunto si mi cabeza es nula
		if (P.subcadenas->cabeza == NULL)
		{
			//Si es nula agrego el nodo al principio
			nodo->siguiente = NULL; 
			P.subcadenas->cabeza = nodo;
			P.subcadenas->largo = 1;
		}
		//Caso de que no sea nula 
		else if (P.subcadenas->cabeza != NULL)
		{
			//Inizializo un puntero con la cabeza de la lista
			Nodo * puntero = P.subcadenas->cabeza;		
			//Inicializo un iterador en 0
			int i  = 0;
			//Mientras el iterador sea menor al largo de la lista enlazada
			while(i < P.subcadenas->largo)
			{
				//Pregunto si el largo de mi cadena es igual al largo del puntero actual
				if (nodo->largo == puntero->largo)
				{
					//Pregunto si mi siguiente no es nulo
					if (puntero->siguiente != NULL)
					{
						//Mi nuevo nodo apunta al siguiente del puntero 
						nodo->siguiente = puntero->siguiente;
						//Y ahora el puntero apunta al nuevo nodo agregado
						puntero->siguiente = nodo;
						//Aumento el largo de la lista
						P.subcadenas->largo = P.subcadenas->largo + 1 ;
						//Rompo la iteración
						break ;
					}
					//En caso de que si sea nulo
					if (puntero->siguiente == NULL)
					{
						puntero->siguiente = nodo;
						P.subcadenas->largo = P.subcadenas->largo + 1 ;
						break;
					}

				}
				//En caso de no serlo sigo recorriendo
				i++;
				//Solo si el puntero siguiente existe
				if (puntero->siguiente)
				{
					//Sigo avanzando en la lsita enlazada
					puntero = puntero->siguiente ;
				}
				//En caso de que no exista
				else
				{
					//Lo agrego al final de mi lista
					puntero->siguiente = nodo;
					P.subcadenas->largo = P.subcadenas->largo + 1 ;

				}
			}
		}
	}

}

//Selectores
//Función que obtenga una cadena en cierta posicion
//Entradas : 
//Recorrido :
char *  obtenerCadena (int n, Lista * lista)
{
	//Si la cadena es nula, retorno nula
	if (lista->cabeza == NULL)
	{
		return NULL;
	}
	//Si no es nula
	else
	{
		Nodo * puntero = lista->cabeza;
		int i = 0 ;
		//Hasta que no llege al final de la lista
		while(i < n && puntero ->siguiente)
		{
			puntero = puntero->siguiente ;
			i++;
		}
		return puntero->cadena;
	}
}
//Otras funciones

//Esta en listaEnlazada
//Entrada: Lista enlazada, cadena
//Salida 0 o 1, false or true
int estaEnListaEnlazada(Lista * lista , char * cadena)
{
	int i = 0;
	Nodo * puntero =  lista->cabeza;
	//Pregunto si las cadenas son coincidentes
	if (strcmp(cadena,puntero->cadena)==0)
	{
		return 0;
	}
	//Mientras exista siguiente y el iterador sea menor al largo
	while(i < lista->largo )
	{	
		//Pregunto si los elementos son iguales
		if (strcmp(cadena,puntero->cadena)==0)
		{
			return 0;
		}
		//Si los elementos no son coincidentes sigo avanzando dentro de la lista
		i++;
		//Solo si el punteor siguiente existe
		if (puntero->siguiente != NULL)
		{
			//Sigo avanzando en la lsita enlazada
			puntero = puntero->siguiente ;
		}
	}
	//Si al final de todo no encontre un elemento coincidente devuelvo 0
	return 1 ;
}

//Función que imprime todos los hayazgos dentro
//Entrada : Nodo * puntero , iterador del largo
void imprimirHayazgosR(Lista * lista ,Nodo * puntero,int i)
{
	//Caso Base
	if(i == lista->largo)
	{
		//Se acaba la recursión
	}
	//Caso recursivo
	else if(i < lista->largo)
	{
		//Imprimo la subcadena
		printf("%s\n",puntero->cadena);
		//Aumento el iterador
		//Solo si el punteor siguiente existe
		if (puntero->siguiente != NULL)
		{
			//Sigo avanzando en la lsita enlazada
			puntero = puntero->siguiente ;
			imprimirHayazgosR(lista,puntero,i+1);
		}
	}

}

//Función que imprime todos las subcadenas encontradas de una palabra
//Entrada : Lista Enlazada
//Salida : Todos sus elementos
//Función Envoltorio
void imprimirHayazgos(palabra P )
{
	Lista * lista = P.subcadenas;
	printf("%s : %d \n",P.palabra,P.subcadenas->largo);
	imprimirHayazgosR(lista,lista->cabeza,0);

}