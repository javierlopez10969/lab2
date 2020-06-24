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
	struct Nodo * anterior;
	//int complete;	
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
//Compara si el string 1 es mayor que ele string2

//SAlida , 0 true , 1 false
int mayorAlfabetico(char * string1 , int largo1 , char * string2, int largo2, int i )
{
    if (string1[i]>string2[i])
    {
        return 0 ;
    }
    //En cambio si es menor 
    else if (string1[i] < string2[i])
    {
        return 1;
    }
    //Si es igual sigo recorriendo los caracteres
    //Pero antes pregunto si el i no se pasa ningungo de los largos
    else if (i+1<largo2 && i+1< largo2)
    {
        //Si no se pasa ninguno de los largos
        //Llamada recursiva
        mayorAlfabetico(string1,largo1,string2,largo2,i+1);
    }
    //Si se pasa en los largos, retorno 1
    else
    {
        return 1;
    }
}


//CONSTRUCTORES
//Función que crea un nodo
//Entrada : string
//Salida : Nodo
Nodo * crearNodo(char * cadena)
{
	//Reservo espacio para el nodo
	Nodo * nodo = 	malloc(sizeof (Nodo));
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
//Función que se encarga de insertar 
//Entrada  :
void insertarAdelante (palabra * P ,char * string , Nodo * puntero)
{
	//Creo un nuevo nodo
	Nodo * nodo = crearNodo(string);
	//printf("N: New Chain in my nodo : %s\n", nodo->cadena );
	//Nodo apunta al siguiente del puntero actual
	nodo->siguiente = puntero->siguiente;
	//Si el siguiente de puntero no es nulo
	if(puntero->siguiente)
	{
		//Si no es nulo
		//El anterior del siguiente de nodo ahora es nodo
		puntero->siguiente->anterior  = nodo;
	}
	//Puntero siguiente ahora es nodo
	puntero->siguiente = nodo;
	//Y anterior de nodo es puntero
	nodo->anterior = puntero;
	//Me muevo a nodo
	puntero = puntero->siguiente ;
	//printf("N :New Chain in my lista : %s\n", puntero->cadena );
	//Aumento mi largo de lista enlazada
	P->subcadenas->largo = P->subcadenas->largo + 1;
	//Libero memoria
	string=malloc(sizeof(char));
	free(string);
}

void insertarAtras (palabra * P ,char * string , Nodo * puntero)
{
	//Creo mi nodo a partir del string
	Nodo * nodo = crearNodo(string);
	// siguiente de nodo es puntero
	nodo->siguiente=puntero;
	//Pregunto si el anterior de puntero es nulo, signfica que es la cabeza de la lista
	if (!puntero->anterior)
	{
		//si es nulo mi nueva cabeza es mi nodo
		P->subcadenas->cabeza = nodo;
		nodo->anterior = NULL;
	}
	//Si no es nulo
	else
	{
		//El anterior de nodo va aser el anterior de puntero
		nodo->anterior = puntero->anterior;
		//Y el siguiente del anteriorr de nodo va a hacer nodo
		nodo->anterior->siguiente =nodo;
	}
	//Ahora el anterior de puntero es nodo
	puntero->anterior = nodo;
	//Aumento el largo
	P->subcadenas->largo = P->subcadenas->largo + 1;
	//Libero memoria
	//printf("L :New Chain in my lista: %s\n", puntero->cadena );
	string=malloc(sizeof(char));
	free(string);

}

//Vamos a confiar en diosito y decir que el string va a llegar sin problemas :C
//Al fina si pudo llegar siempre sin problemas :-D, free();
//Función que inserta un elemento de manera ordenada por su largo, falta insertarla por orden alfabetico
//Entradas: Nueva cadena a insertar , lista enlazadas de subcadnas
void insertar(palabra * P, char * string ,int largoString,Nodo * puntero)
{
	/*
	if (puntero->cadena==P->subcadenas->cabeza->cadena){
	printf("Cadena llego como : %s  \n",string );
	printf("Largo cadena : %d \n",largoString );
	if ((string[0]<puntero->cadena[0])==1)
	{
		printf("anterior\n");
	}
	else{printf("adelante\n");}
	
	printf("Insertar [%d] : subcadena : %s tamanoReal : %d tamanoLen  : %ld puntero : %s de largo %d"
		,P->subcadenas->largo,string, largoString, strlen(string) ,puntero->cadena,puntero->largo);
	printf(" == %d \n , siguiente : %p\n", mayorAlfabetico(string,largoString, puntero->cadena,puntero->largo,0),puntero->siguiente);*/
	//printf("%s with large : %d V/S %s with large : %d = %d \n ",  string, largoString,puntero->cadena,puntero->largo,
	//mayorAlfabetico(string,largoString, puntero->siguiente->cadena,puntero->siguiente->largo,0));

	//Caso super especial, el primer elemento
	if ((P->subcadenas->cabeza->largo == -1) && (P->subcadenas->cabeza->anterior == NULL)  && (strcmp(P->subcadenas->cabeza->cadena,"UNDERTALE") == 0))
	{
		//Como al primer elemento ya le tengo una memoria asignada, solo asigno
		//Copio el string en en la cadena
		strcpy(P->subcadenas->cabeza->cadena ,string);
		//Asigno el largo de la cadena
		P->subcadenas->cabeza->largo = largoString;
		//Asigno el largo del nodo
		P->subcadenas->largo = 1;
		P->subcadenas->cabeza->siguiente = NULL;
		P->subcadenas->cabeza->anterior  = NULL;
	}
	//Caso Borde : Ultimo elemento de la lista
	//Si no existe un nodo siguiente , lo inserto ultimo o penultimo
	else if (puntero->siguiente == NULL)
	{
		//Pregunto si tienen el mismo largo
		if (largoString == puntero->largo)
		{
			//Si tienen el mismo largo
			//Si es menor alfabeticamente, lo inserto atrás
			if (mayorAlfabetico(string,largoString, puntero->cadena,puntero->largo,0)==1)
			{
				insertarAtras (P,string , puntero);
				puntero = puntero->anterior;
				//printf("New chain : %s\n",puntero->cadena );
			}
			else if (mayorAlfabetico(string,largoString,puntero->cadena,puntero->largo,0)==0)
			{
				insertarAdelante(P,string,puntero);
				puntero = puntero->siguiente;
				//printf("New chain : %s\n",puntero->cadena );
			}
		}
		//Si no tienen el mismo largo
		else if (largoString !=puntero->largo)
		{
			//lo inserto adelante
			insertarAdelante(P,string,puntero);
			puntero = puntero->siguiente;
			//printf("New chain : %s\n",puntero->cadena );
		}

	}
	//Caso mixto : Recursivo y borde
	//Pregunto si tienen el mismo largo
	else if (largoString == puntero->largo)
	{
		//Si es menor alfabeticamente
		if (mayorAlfabetico(string,largoString, puntero->cadena,puntero->largo,0)==1)
		{
			//Lo inserto atrás del puntero actual
			insertarAtras (P,string , puntero);
			puntero = puntero->anterior;
		}
		//Si es mayor alfabeticamente****
		else if (mayorAlfabetico(string,largoString,puntero->cadena,puntero->largo,0)==0)
		{
			//Pregunto si es mayor alfabeticamente que el siguiente elemento, y menor o igual numericamente que el siguiente 
			if ((mayorAlfabetico(string,largoString, puntero->siguiente->cadena,puntero->siguiente->largo,0)==0) && largoString == puntero->siguiente->largo )
			{
				//Si es mayor alfabeticamente y menor numericamente que el siguiente elemento sigo recorriendo la lista 
				puntero = puntero->siguiente ;
				insertar(P,string ,largoString,puntero );
			}
			//Pregunto si es menor que el siguiente elemento
			else
			{
				//Si es menor que el siguiente elemento pero mayor que el elemento actual, lo inserto adelante del puntero actual
				insertarAdelante(P,string,puntero);
				puntero = puntero->siguiente;
				//printf("New chain : %s\n",puntero->cadena );
			}
		}
	}
	//Si no tiene el mismo largo y además el siguiente punteor tampoco es nulo
	else
	{
		//Sigo recorriendo la lista
		puntero = puntero->siguiente ;
		insertar(P,string ,largoString,puntero );
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