//MODULO DE IMPORTACIONES
#include<stdio.h>
#include <stdlib.h>
#include <string.h>


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


//Función que arregla string mal traspasados , ya que aveces por usar memoria dinámica llegaban algunas cadenas con basura de memoria
//Supuesto: Se le pasan string que ya se saben que sus largos reales son incongruentes
//Entrada : string malito , largo real
//Salida : string arreglado
char * limpiezaDeString(char * stringMalo,int tamanoReal)
{
	//Si el tamaño del string ya es correcto devuelvo un nuevo string
	if(strlen(stringMalo)==tamanoReal)
	{
		//printf("String arreglado : %s \n", stringMalo);
		return (stringMalo);
	}
	//Si el tamaño no se cumple
	else
	{
		//Lo copio en un nuevo string
		char nuevo[tamanoReal] ;
		//strcpy(nuevo,stringMalo);
		//free(stringMalo);
		//strncat(nuevo,stringMalo,tamañoReal);
		char caracter;
		int i = 0 ;
		while (i < tamanoReal)
		{
			caracter = stringMalo[i];
			nuevo[i] = caracter;
			i++;
		}
		free(stringMalo);
		//printf("Nuevo String :  %s \n",nuevo);
		//Llamada recursiva :
		limpiezaDeString(nuevo,tamanoReal);

	}
}


//MODULO DE BUSQUEDA DE PALABRAS 
//Función Recursiva
//Función que genera un substring a partir de un string
//Entrada : String a partir dodne se crea el substring , Substring a generar , indice de string,  indice en el cual estoy asignando el char, largo del string a generar
//Salida  : String
void substringR (char * string , char * subString ,int indice , int i, int largo)
{

	//Caso Base, cuando ya me encuentro en el el largo total de lo que quería calcular
	if (largo==0)
	{
		
	}
	//Casos Recursivos
	else
	{
		subString[i] = string[indice];
		//Llamo la recursión con un mi string y mi cadena manteniendolos, y sigo recorriendo ambos strings, reduciendo el largo total
		substringR (string ,subString ,indice + 1,i+1,largo-1);
	}
}

//Función Iterativa
//Función que genera un substring a partir de un string
//Entrada : String a partir dodne se crea el substring , Substring a generar , indice de string,  indice en el cual estoy asignando el char, largo del string a generar
//Salida  : String
char * substringI (char * string ,int indice, int largo)
{
	char * substringaux = malloc(sizeof(char)*largo);
	int i = 0 ;
	char caracter;
	while (i < largo)
	{
		char caracter =string[indice];
		substringaux[i] = caracter;
		i++;
		indice++;
	}	
	return(substringaux);
}

//Vamos a confiar en diosito y decir que el string va a llegar sin problemas :C
//Al fina si pudo llegar siempre sin problemas :-D, free();
//Función que inserta fixeada
//Entradas: Nueva cadena a insertar , lista enlazadas de subcadnas
void insertar(palabra * P, char * string ,int largoString,Nodo * puntero )
{
	/*
	if (puntero->cadena==P->subcadenas->cabeza->cadena)
	{
		printf("Insertar [%d] : subcadena : %s tamanoReal : %d tamanoLen  : %ld\n",P->subcadenas->largo,string, largoString, strlen(string) );
	}
	*/
	//Ahora pregunto si mi subcadena tiene el mismo largo de mi actual string a agregar
	if (puntero->largo==largoString)
	{
		//printf("Cadena llego como : %s  \n",string );
		//Lo agrego al siguiente elemento de mi nodo
		//printf("Largo cadena : %d \n",largoString );
		//printf("Cadena en puntero : %s \n", puntero->cadena);
		//printf("Largo de Cadena: %d \n",puntero->largo);
		//En caso de que lo sea, reservo memoria de mi nodo
		//Creación manual
		//Nodo * nodo = malloc(sizeof (Nodo));
		//Copiamos el string en el nodo
		//strcpy(nodo->cadena,string);
		//nodo->largo = largoString;
		Nodo * nodo = crearNodo(string);
		//Ahora mi nodo apunta al siguiente de mi puntero actual
		nodo->siguiente = puntero->siguiente;
		int i = 0; int vueltas = 0;
		//printf("L : New Chain in my nodo : %s My string : %s \n", nodo->cadena ,string);
		puntero->siguiente = nodo;
		puntero= puntero->siguiente ; 
		P->subcadenas->largo = P->subcadenas->largo + 1;
		//printf("L :New Chain in my lista: %s\n", puntero->cadena );
		string=malloc(sizeof(char));
		free(string);
	}
	//Si no existe un nodo siguiente
	else if (puntero->siguiente == NULL)
	{
		//printf("Cadena llego como : %s \n",string );
		//Mi puntero siguiente será mi nuevo nodo
		Nodo * nodo = crearNodo(string);
		//printf("N: New Chain in my nodo : %s\n", nodo->cadena );
		puntero->siguiente = nodo;
		//Y ahora mi puntero es el siguiente
		puntero = puntero->siguiente ;
		//printf("N :New Chain in my lista : %s\n", puntero->cadena );
		//Aumento mi largo de lista enlazada
		P->subcadenas->largo = P->subcadenas->largo + 1;
		string=malloc(sizeof(char));
		free(string);
	}	

	//Si existe un sigueinte nodo sigo avanzando
	else if (puntero->siguiente != NULL)
	{
		puntero = puntero->siguiente ;
		insertar(P,string ,largoString,puntero );
	}

}
//Función para generar todas las cadenas cuando la subcadena encontrada es mayo a 3
//Entrada: palabra P , subcadena , largo de la subcadena
//Salida: Void
//Recursión : De cola, ya que no deja estados pendientes
void generarSubcadenasMayores (palabra * P , char * subcadena , int largoSubcadena ,int indice, int casos)
{
	//Creo un substring del tamaño del indice, que se crea a partir de la subcadena, desde el número de casos que me encuentro hasta el largo del indice
	char *  subString;
	//Genero el substring dentro de la subcadena
	subString = substringI (subcadena , casos,indice);
	//Hacemos una limpieza del substring antes de insertarlo
	subString=strcpy(subString ,limpiezaDeString(subString,indice)); 
	//printf("Cadena : %s\n", subcadena);
	//printf("Substring fixed : %s\n", subString);
	//subcadenaAux  = limpiezaDeString(subcadenaAux, largoSubcadena);
	//printf("Subcadena : %s , Subcadena Aux : %s \n",subcadena ,subcadenaAux );
	//printf("indice : %d casos :%d largoR: %d largoLen : %ld subcadena  : %s \n",indice,casos,largoSubcadena,strlen(subcadena),subcadena);
	//Caso Borde, cuando el indice es igual a largo de  la subcadena
	if (indice == largoSubcadena)
	{		
		char * subStringFinal  ;
		subStringFinal =  limpiezaDeString(subcadena,largoSubcadena);
		//Pregunto si mi cadena se encuentra en algun nodo de la lista
		if (estaEnListaEnlazada(P->subcadenas,subStringFinal)==1)
		{
			//printf("Cadena : %s\n",subcadena );
			//printf("No esta\n");
			//Si el complete esta en -1 signfica que esta vacío el primer elemento de la lista
			//Por lo cual la nueva cabeza es nuestro nuevo nodo
			if (P->subcadenas->cabeza->largo == -1)
			{
				//Trasbasijo mi string en una el primer elemento
				//Nueva Cabeza
				strcpy(P->subcadenas->cabeza->cadena ,limpiezaDeString(subString,indice));
				P->subcadenas->cabeza->largo = indice;
				P->subcadenas->largo = 1;
				P->subcadenas->cabeza->siguiente = NULL;
				//printf("subcadena nueva en nodo :  %s\n",string );
				//printf("Subcadena nueva en nodo :  %s\n",String );
				//printf("Nuevo string nodo  : %s\n", nodo->cadena);
				//printf("PUNTERO NULO, NUEVA CABEZA\n");
				//printf("Nuevo string Cabeza  : %s Largo : %d siguiente = %p \n", P->subcadenas->cabeza->cadena , P->subcadenas->cabeza->largo,P->subcadenas->cabeza->siguiente);
			}
			//Si la cabeza no es nula
			else
			{
				//printf("Substring  Final fixed : %s\n", subStringFinal);
				insertar(P,subStringFinal,largoSubcadena,P->subcadenas->cabeza);	
			}
		}
		else
		{
			free(subStringFinal);
		}

	}

	//Casos Recursivos
	//Pregunto si mi cadena se encuentra en algun nodo de la lista y si mi cabeza esta vacía
	else if (estaEnListaEnlazada(P->subcadenas,subString)==1 && (P->subcadenas->cabeza->largo == -1))
	{
		//printf("Substring fixed : %s\n", subString);
		//Trasbasijo mi string en una el primer elemento
		strcpy(P->subcadenas->cabeza->cadena ,limpiezaDeString(subString,indice));
		P->subcadenas->cabeza->largo = indice;
		P->subcadenas->largo = 1;
		P->subcadenas->cabeza->siguiente = NULL;
		//ASigno la nueva cabeza
		//Nueva Cabeza
		//Liberamos la cabeza anterior
		//Y asignamos una nueva cabeza
		//Nodo * nodo = crearNodo(String);
		//printf("subcadena nueva en nodo :  %s\n",string );
		//printf("Subcadena nueva en nodo :  %s\n",String );
		//printf("Nuevo string nodo  : %s\n", nodo->cadena);
		//printf("PUNTERO NULO, NUEVA CABEZA\n");
		//printf("Nuevo string Cabeza  : %s Largo : %d siguiente = %p \n", P->subcadenas->cabeza->cadena , P->subcadenas->cabeza->largo,P->subcadenas->cabeza->siguiente);
		//Si mi cabeza no esta vacía lo inserto de manera natural
		//free(subString);
		if (casos+1 == largoSubcadena-(indice-1))
		{
			//Sigo Recorriendo recursivamente la cadena, reinicio los casos y paso al siguiente indice
			generarSubcadenasMayores (P ,subcadena ,largoSubcadena, indice+1,0);
		}
		else if (casos+1 < largoSubcadena-(indice-1))
		{
			//Sigo Recorriendo recursivamente la cadena, mantengo el indice y paso al sigueinte caso
			generarSubcadenasMayores (P ,subcadena ,largoSubcadena,indice,casos+1);
		}
	}
	//Si no se encuentra pero ya hay un elemento en la cabeza
	else if (estaEnListaEnlazada(P->subcadenas,subString)==1)
	{
		//printf("Substring fixed : %s\n", subString);
		insertar(P,subString,indice,P->subcadenas->cabeza);
		//free(subString);
		if (casos+1 == largoSubcadena-(indice-1))
		{
			//Sigo Recorriendo recursivamente la cadena, reinicio los casos y paso al siguiente indice
			generarSubcadenasMayores (P ,subcadena ,largoSubcadena, indice+1,0);
		}
		else if (casos+1 < largoSubcadena-(indice-1))
		{
			//Sigo Recorriendo recursivamente la cadena, mantengo el indice y paso al sigueinte caso
			generarSubcadenasMayores (P ,subcadena ,largoSubcadena,indice,casos+1);
		}
	}

	//Casos Recursivos
	//Formula de cuantas subcadenas posibles hay dentro de una cadena
	//por ejemplo subcadenas de 3 caracteres en una cadena de 6
	//...---
	//-...--
	//--...-
	//---...
	//6-(3-1) = 4 , 4 posibles subcadenas
	//siendo la formula largoCadena-(tamañosubcadenas-1)
	//Si el próximo caso es igual al largo de la subcadena, significa que es el último caso
}

//función generadora de subcadenas dentro de una lista enlazafa
//Entrada : estructura palabra , 3 <= n
//Salida :Void
void generarSubcadenas(palabra * P,char * subcadena, int largoSubcadena)
{
	//Creamos un nuevo string que se somete a un proceso de limpieza, ya que aveces por usar memoria dinámica llegaban algunas cadenas con basura 
	char * newString ;
	newString = limpiezaDeString(subcadena,largoSubcadena);
	//printf("Subcadena : %s LargoR : %d Largo Len : %ld\n ",newString,largoSubcadena,strlen(subcadena));
	//Preguntamos si la subcadena encontrada es igual a 3
	if (largoSubcadena == 3)
	{
		//En Caso de serlo pregunto si esta subcadena no se encuentra en la lista enlazada
		if (estaEnListaEnlazada(P->subcadenas ,newString)== 1)
		{
			//En caso de no encontrarse, la agrego a mi lista enlazada
			insertarAlInicio(P->subcadenas,newString);
		}
	}
	//De caso contrario, que el largo de la subcadena encontrada sea mayor a 3, genero todas las subcadenas posibles con ese largo, y pregunto si cada una se encuentra dentro
	//De la subcadena
	else if (largoSubcadena > 3)
	{
		//printf("1\n");
		generarSubcadenasMayores(P,newString,largoSubcadena,3,0);
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
				//printf("LargoR : %d LargoLen : %ld \n", largoSub ,strlen(subcadena));
				//printf("Caracter : %c [%d] [%d] \n",caracter,i,j ); 
				//printf("Subcadena : %s\n",subcadena );
				//char * temp = limpiezaDeString(subcadena,largoSub);
				//printf("temp1  :%s\n",temp);
				generarSubcadenas(P,subcadena,largoSub);
			}
			else
			{
				free(subcadena);
			}
			//Recorro la sopa hacia la derecha con la palabra en orden
			//Reinicializamos la subcadena
			largoSub = 1;
			char * subcadena2= (char*)malloc(sizeof(char)*largoSub);
			buscarSubcadenasH(sopa,n,i,j,coincidencias[indice],P,subcadena2,&largoSub);
			if (largoSub >= 3)
			{
				//printf("LargoR : %d LargoLen : %ld \n", largoSub ,strlen(subcadena));
				//printf("Caracter : %c [%d] [%d] \n",caracter,i,j ); 
				//printf("Subcadena : %s\n",subcadena );
				//char * temp2 = limpiezaDeString(subcadena2,largoSub);
				//printf("temp2  :%s\n",temp2);
				generarSubcadenas(P,subcadena2,largoSub);
			}
			else
			{
				free(subcadena2);	
			}
			
			indice ++;
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
void busqueda (char ** sopa ,int n1 ,palabra * P)
{
	//Casos Base
	if (!P->siguiente)
	{
		printf("DONE\n");
	}
	//Casos Recursivos
	else if (P->siguiente)
	{
		printf("--------------------------------------------------------\n");
		printf("Palabra : %s\n", P->palabra);
		char * temp = malloc(sizeof(char)*P->largoPalabra);
		//strcpy(temp,P->palabra); 
		//generarSubcadenas(P,temp,P->largoPalabra);
		//imprimirHayazgos(P);
		busquedaDeSubcadenas(sopa,n1,0,0,P);
		//Solo si el i+1 no es igual al largo
		busqueda(sopa,n1,P->siguiente);
	}
}