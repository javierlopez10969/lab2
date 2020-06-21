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


typedef struct palabra{
	//Palabra a la cual le buscamos la 
    char palabra[30];
    //Siguiente elemento de la palabra
    struct palabra * siguiente;
    //Largo de la palabra
    int largoPalabra;
    //Lista enlazada donde se almacenan las subcadenas
    Lista * subcadenas;
}palabra;

typedef struct listaP
{
	//Elemento cabeza de palabras
	palabra * cabeza ;
	//Largo total de la lista
	int largo ;
	
}listaP;

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


//Selectores
//Otras funciones

//Esta en listaEnlazada
//Entrada: Lista enlazada, cadena
//Salida 0 o 1, false or true
int estaEnListaEnlazada(Lista * lista , char * cadena)
{
	int i = 0;
	Nodo * puntero =  lista->cabeza;
	//Mientras exista siguiente y el iterador sea menor al largo
	while(i < lista->largo)
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
	//Si al final de todo no encontre un elemento coincidente devuelvo 1
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
void imprimirHayazgos(palabra * P)
{
	Lista * lista = P->subcadenas;
	printf("%s : %d \n",P->palabra,P->subcadenas->largo);
	imprimirHayazgosR(lista,lista->cabeza,0);

}