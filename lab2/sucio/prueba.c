#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TDA_lista_enlazada.h"
//Función que genera un substring a partir de un string
//Entrada : String a partir dodne se crea el substring , Substring a generar indice inferior, indice en el cual estoy asignando el char, largo del string a generar
//Salida  : String
void substring (char * string , char * subString , int indice , int i, int largo)
{
	//Caso Base, cuando ya me encuentro en el el alrgo total de lo que quería calcular
	if (largo==0)
	{
		subString = subString;
	}
	//Casos Recursivos
	else
	{
		subString[i] = string[indice];
		//Llamo la recursión con un mi string y mi cadena manteniendolos, y sigo recorriendo ambos strings, reduciendo el largo total
		substring (string ,subString ,indice + 1,i+1,largo-1);
	}
}

//Función para generar todas las cadenas cuando la subcadena encontrada es mayo a 3
//Entrada: palabra P , subcadena
//Salida: Void
//Recursión : De cola, ya que no deja estados pendientes
void generarSubcadenasMayores (palabra P , char * subcadena ,int indice, int casos)
{
	//Caso Borde, cuando el indice es igual a largo de  la subcadena
	if (indice == strlen(subcadena))
	{
		//Pregunto si la subcadena se ecnuentra en la lista
		if (estaEnListaEnlazada(P.subcadenas ,subcadena)== 1)
		{
			//En caso de no encontrarse, la agrego a mi lista enlazada
			insertarSegunCorresponda(P,subcadena);
		}
		//si no termina de recorrer
		printf("END\n");
	}
	//Casos Recursivos
	else if (casos+1 == strlen(subcadena)-(indice-1))
	{
		//printf("Casos: %d\n", casos+1);
		//Creo un substring del tamaño del indice, que se crea a partir de la subcadena, desde el número de casos que me encuentro hasta el largo del indice
		char * subString = (char*)malloc(sizeof(char)*indice);
		substring (subcadena , subString ,casos,0,indice);
		//printf("%s\n",subString );
		insertarSegunCorresponda(P,subString);
		//Libero mi subString
		free(subString);
		//Sigo Recorriendo recursivamente la cadena
		generarSubcadenasMayores (P ,subcadena ,indice+1,0);
	}
	else if (casos+1 < strlen(subcadena)-(indice-1))
	{
		//printf("Casos: %d\n",casos+1);
		//Creo un substring del tamaño del indice, que se crea a partir de la subcadena, desde el número de casos que me encuentro hasta el largo del indice
		char * subString = (char*)malloc(sizeof(char)*indice);
		substring(subcadena ,subString ,casos,0,indice);
		//printf("%s\n",subString );
		//Pregunto si la subcadena se ecnuentra en la lista
		//En caso de no encontrarse, la agrego a mi lista enlazada
		insertarSegunCorresponda(P ,subString);
		//Libero mi subString
		free(subString);
		//Sigo Recorriendo recursivamente la cadena
		generarSubcadenasMayores (P ,subcadena ,indice,casos+1);
	}
}

//función generadora de subcadenas dentro de una lista enlazafa
//Entrada : estructura palabra , 3 <= n
//Salida :Void
void generarSubcadenas(palabra P,char * subcadena)
{
	Nodo * puntero = P.subcadenas->cabeza;
	//Preguntamos si la subcadena encontrada es igual a 3
	if (strlen (subcadena)==3)
	{
		//En Caso de serlo pregunto si esta subcadena no se encuentra en la lista enlazada
		if (estaEnListaEnlazada(P.subcadenas ,subcadena)== 1)
		{
			//En caso de no encontrarse, la agrego a mi lista enlazada
			insertarAlInicio(P.subcadenas,subcadena);
		}
	}
	//De caso contrario, que el largo de la subcadena encontrada sea mayor a 3, genero todas las subcadenas posibles con ese largo, y pregunto si cada una se encuentra dentro
	//De la subcadena
	else
	{
		//printf("1\n");
		generarSubcadenasMayores(P,subcadena,3,0);
	}
}

//Funcion que recibe palabras
int main()
{
	char word [30] = "eskeler";
	printf("Palabra :%s\n",word );
	//Declaro una estuctura palabra
	palabra P;
	printf("L : %d\n",P.subcadenas->largo);
	//Inicializamos el largo de la palabra
	strcpy(P.palabra,word);
	printf("palabra en word: %s\n",P.palabra );
	//Declaro una subcadena
	char subcadena[14] = "skeler";
	insertarAlInicio(P.subcadenas,"ler");
	printf("L : %d\n",P.subcadenas->largo);
	imprimirHayazgos(P);
	//printf("%d\n",  estaEnListaEnlazada(P.subcadenas,"keler"));
	generarSubcadenas(P,subcadena);
	imprimirHayazgos(P);
	//--------------------------------------------------------------------------------
	//Arreglar insertar segun corresponda LISTO
	//Probando memorias
	/*
	char * subway = (char*)malloc(sizeof(char)*3);
	substring(subcadena ,subway ,0,0,3);
	printf("Subway : %s\n", subway );
	strcpy (P.palabra ,subway);
	printf("New Palabra: %s\n",P.palabra );
	free(subway);
	printf("New Palabra: %s\n",P.palabra );
	printf("%s\n",subway );
	*/



}