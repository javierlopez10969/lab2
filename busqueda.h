//MODULO DE IMPORTACIONES
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

//MODULO DE BUSQUEDA DE PALABRAS 
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
//Entrada: palabra P , subcadena , largo de la subcadena
//Salida: Void
//Recursión : De cola, ya que no deja estados pendientes
void generarSubcadenasMayores (palabra * P , char * subcadena , int largoSubcadena ,int indice, int casos)
{
	//printf("indice : %d largo de subcadena : %d subcadena  : %s Palabra : %s \n",indice,largoSubcadena,subcadena,P->palabra);
	//Caso Borde, cuando el indice es igual a largo de  la subcadena
	if (indice == largoSubcadena)
	{
		//Pregunto si la subcadena se ecnuentra en la lista
		if (estaEnListaEnlazada(P->subcadenas ,subcadena)== 1)
		{
			//En caso de no encontrarse, la agrego a mi lista enlazada
			insertarSegunCorresponda(P,subcadena);
		}
		//si no termina de recorrer
	}
	//Casos Recursivos
	else if (casos+1 == largoSubcadena-(indice-1))
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
		generarSubcadenasMayores (P ,subcadena ,largoSubcadena, indice+1,0);
	}
	else if (casos+1 < largoSubcadena-(indice-1))
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
		generarSubcadenasMayores (P ,subcadena ,largoSubcadena,indice,casos+1);
	}
}

//función generadora de subcadenas dentro de una lista enlazafa
//Entrada : estructura palabra , 3 <= n
//Salida :Void
void generarSubcadenas(palabra * P,char * subcadena, int largoSubcadena)
{
	Nodo * puntero = P->subcadenas->cabeza;
	//Preguntamos si la subcadena encontrada es igual a 3
	if (strlen (subcadena)==3)
	{
		//En Caso de serlo pregunto si esta subcadena no se encuentra en la lista enlazada
		if (estaEnListaEnlazada(P->subcadenas ,subcadena)== 1)
		{
			//En caso de no encontrarse, la agrego a mi lista enlazada
			insertarAlInicio(P->subcadenas,subcadena);
		}
	}
	//De caso contrario, que el largo de la subcadena encontrada sea mayor a 3, genero todas las subcadenas posibles con ese largo, y pregunto si cada una se encuentra dentro
	//De la subcadena
	else if (strlen(subcadena) > 3)
	{
		//printf("1\n");
		generarSubcadenasMayores(P,subcadena,largoSubcadena,3,0);
	}
}
//función que verifica si un caracter se encuentra dentro de una cadena
//Entrada : cadena , caracter , indice que se mueve por la cadena, numero de veces que se encuentra el caracter dentro de la cadena
//SAlida : arreglo con los indices
void caracterInsideString(char * cadena ,char caracter,int i, int * arregloSalida, int * coincidencias)
{
	//Caso base me encuentro al final de la cadena
	if (i == strlen(cadena))
	{
		arregloSalida;
	}
	//Casos recursivos
	//Caso haber encontrado un caracter coincidente
	else if (cadena[i]==caracter)
	{
		*coincidencias=*coincidencias +1;
		//Asigno el indice donde se encuentra
		arregloSalida[*coincidencias-1] = i;
		//Llamada recursiva
		caracterInsideString(cadena,caracter,i+1,arregloSalida,coincidencias);
	}
	//Caso de que el caracter no sea igual a la letra analizando
	else if (cadena[i]!=caracter)
	{
		//Llamada recursiva
		caracterInsideString(cadena,caracter,i+1,arregloSalida,coincidencias);
	}

}
//Función que recorre la sopa de arriba hacia abajo buscando una subcadena en común
//Entrada : sopa, largo de la sopa , indice i , indice j , int indice donde se encuentra la letra encontrada , indi Palabra, subcadena
//char dir indica la dirección en la que me estoy moviendo = U  = arriba ,D = abajo , L = Izquierda
//char orden = , el orden que estoy siguiendo, O = orden , R = en reversa
//Salida : Subcadena con las coincidencias
void buscarSubcadenasV(char ** sopa , int n , int i , int j ,int  indiceP , palabra * P , char * subcadena, int * largoSub)
{
	//Primero me muevo de arriba hacia abajo
	//Caso borde de que no puedo seguir bajando
	if (i+1 == n || indiceP == P->largoPalabra)
	{
		//devuelvo subcadena
		//printf("Largo : %d\n", *largoSub );
		//printf("Subcadena : %s de %s\n",subcadena ,P->palabra);
		*largoSub = *largoSub-1;
	}
	//Si puedo bajar
	// && indiceP+1 < P->largoPalabra
	else if (i < n)
	{
		char caracter = sopa[i][j] ;
		//printf("CaracterS : %c\n",sopa[i][j]);
		//printf("CaracterP : %c\n",P->palabra[indiceP]);

		//pregunto si el siguiente elemento de la lista coincide con el de la palabra
		if (caracter == P->palabra[indiceP])
		{
			subcadena[*largoSub-1]= caracter ;
			//Aumento el largo de la subcadena 
			*largoSub = *largoSub + 1;
			//printf("Largo Eskeresito: %d\n", *largoSub );
			//Si coinciden, la subcadena en su indice se asgina
			//Hago el llamado recursivo hacia arriba y en orden
			buscarSubcadenasV(sopa,n,i+1,j,indiceP+1 ,P,subcadena,largoSub);
		}
		//En caso de que no coincidan
		else if (caracter != P->palabra[indiceP])
		{
			*largoSub = *largoSub-1;
			//devuelvola cadena
		}
	}
}
//Función que recorre la sopa de izquierda a derecha buscando una subcadena en común
//Entrada : sopa, largo de la sopa , indice i , indice j , int indice donde se encuentra la letra encontrada , indi Palabra, subcadena
void buscarSubcadenasH(char ** sopa , int n , int i , int j ,  int  indiceP , palabra * P , char * subcadena, int * largoSub)
{
	//Primero me muevo de arriba hacia abajo
	//Caso borde de que no puedo seguir bajando
	//printf("[%d][%d]\n",i,j);
	if (j+1 == n || indiceP == P->largoPalabra)
	{
		//devuelvo subcadena
		//printf("Largo : %d\n", *largoSub );
		//printf("Subcadena : %s de %s\n",subcadena ,P->palabra);
		*largoSub = *largoSub-1;
	}
	//Si puedo bajar
	// && indiceP+1 < P->largoPalabra
	else if (j < n)
	{
		char caracter = sopa[i][j] ;
		//printf("CaracterS : %c\n",sopa[i][j]);
		//printf("CaracterP : %c\n",P->palabra[indiceP]);
		//pregunto si el siguiente elemento de la lista coincide con el de la palabra
		if (caracter == P->palabra[indiceP])
		{
			subcadena[*largoSub-1]=P->palabra[indiceP];
			//Aumento el largo de la subcadena 
			*largoSub = *largoSub + 1;
			//printf("Largo Eskeresito: %d\n", *largoSub );
			//Si coinciden, la subcadena en su indice se asgina
			//Hago el llamado recursivo hacia arriba y en orden
			buscarSubcadenasH(sopa,n,i,j+1,indiceP+1,P,subcadena,largoSub);
		}
		//En caso de que no coincidan
		else if (caracter != P->palabra[indiceP])
		{
			*largoSub = *largoSub-1;
			//devuelvola cadena
		}
	}

}

//Función que recorre la sopa y va añadiendo las disntintas subcadenas
//ENTRADA : Sopa de letras , LArgo N de la sopa , lista simplemente enlazada con palabras, palabra puntero
//SAlida: Subcadenas de la palabra entregada
void busquedaDeSubcadenas(char ** sopa ,int n ,int i, int j , palabra * P)
{

	//Declaro el caracter a analizar
	char caracter = sopa[i][j];
	int Lcoincidencias = 0;
	//Creo un arreglo dinamico para almacenar los disntintos indices
	int * coincidencias = (int*)malloc(sizeof(int)*Lcoincidencias); ;
	caracterInsideString(P->palabra,caracter, 0,coincidencias,&Lcoincidencias);
	//-----------------------------------------------------------------------------
	//Por implementar
	//LLEVAR UN ARREGLO CON LAS LETRAS QUE YA REVISE PARA NO REVISARLAS DE NUEVO
	//-----------------------------------------------------------------------------
	//Pregunto si mi caracter se encuentra dentro de mi palabra, si hay por lo menos una coincidencia
	if (Lcoincidencias > 0)
	{
		//Si hay por lo mneos una coincidenica
		//printf("Palabra : %s ", P->palabra);
		//printf("Coincidencias : %d \n",Lcoincidencias );
		//Declaramos variables auxiliares
		int indice = 0;
		//Mientra el largo se mayor a 0
		while (indice < Lcoincidencias)
		{
			//printf("Indice coincidente :%d , caracter coincidente : %c \n",coincidencias[indice] ,caracter);
			//Declaramos una subcadena de tamaño 0
			int largoSub = 1;
			char * subcadena = (char*)malloc(sizeof(char)*largoSub);
			//Recorro la sopa hacia abajo con la palabra en orden
			buscarSubcadenasV(sopa,n,i,j,coincidencias[indice],P,subcadena,&largoSub);
			if (largoSub >= 3)
			{
				printf("Largo : %d\n", largoSub );
				printf("Caracter : %c [%d] [%d] \n",caracter,i,j ); 
				printf("Subcadena : %s\n",subcadena );
				generarSubcadenas(P,subcadena,largoSub);
			}
			//Recorro la sopa hacia la derecha con la palabra en orden
			//Reinicializamos la subcadena
			largoSub = 1;
			subcadena = (char*)malloc(sizeof(char)*largoSub);
			buscarSubcadenasH(sopa,n,i,j,coincidencias[indice],P,subcadena,&largoSub);
			if (largoSub >= 3)
			{
				printf("Largo : %d\n", largoSub );
				printf("Caracter : %c [%d] [%d] \n",caracter,i,j ); 
				printf("Subcadena : %s\n",subcadena );
				generarSubcadenas(P,subcadena,largoSub);
			}
			indice ++;
			free(subcadena);
		}

	}
	//Libero la memoria dinámica
	free(coincidencias);
	//sigo recorriendo la sopa
	//Si ambos siguientes indices son iguales al largo de la sopa, paro de hacer recursión e imprimo los elementos hayados
	if(i+1==n && j+1 == n)
	{
		imprimirHayazgos(P);
	}
	//si mi siguiente indice i es igual a n pero mi inidice j sige siendo menot a n
	else if (i+1 < n && j+1 == n)
	{
		//reinicio j y aumento i
		busquedaDeSubcadenas(sopa,n,i+1,0,P);
	}
	else if (i+1 == n && j+1<n)
	{
		busquedaDeSubcadenas(sopa,n,i,j+1,P);
	}
	else if (i+1 < n && j+1<n)
	{
		busquedaDeSubcadenas(sopa,n,i,j+1,P);
	}

}
//función que se encarga de ejecutar la busqueda
//ENTRADA : Sopa de letras , LArgo N de la sopa , lista simplemente enlazada con palabras, palabra puntero
//SALIDAS : Estructura con una 
void busqueda (char ** sopa ,int n1 , listaP * listaDePalabras,palabra * puntero)
{
	//Casos Base
	if (!puntero->siguiente)
	{
		printf("DONE\n");
	}
	//Casos Recursivos
	else if (puntero->siguiente)
	{
		printf("--------------------------------------------------------\n");
		printf("Palabra : %s\n", puntero->palabra);
		busquedaDeSubcadenas(sopa,n1,0,0,puntero);
		//Solo si el i+1 no es igual al largo
		busqueda(sopa,n1,listaDePalabras,puntero->siguiente);
	}

}