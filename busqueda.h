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
		stringMalo = malloc(sizeof(char));
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
	if (i == largo)
	{
		//Devuelvo mi substring
		;
	}
	//Casos Recursivos
	else
	{
		subString[i] = string[indice];
		//Llamo la recursión con un mi string y mi cadena manteniendolos, y sigo recorriendo ambos strings, reduciendo el largo total
		substringR (string ,subString ,indice + 1,i+1,largo);
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


//Función para generar todas las cadenas cuando la subcadena encontrada es mayo a 3
//Entrada: palabra P , subcadena , largo de la subcadena
//Salida: Void
//Recursión : De cola, ya que no deja estados pendientes
void generarSubcadenasR(palabra * P , char * subcadena , int largoSubcadena ,int indice, int casos)
{
	//Creo un substring del tamaño del indice, que se crea a partir de la subcadena, desde el número de casos que me encuentro hasta el largo del indice
	char *  subString;
	//Genero el substring dentro de la subcadena
	
	//Llamada Iterativa
	//subString = substringI (subcadena , casos,indice);

	//Llamada Recursiva
	subString = malloc(sizeof(char)*indice);
	substringR(subcadena,subString,casos,0,indice);
	//printf("Substring not fixed : %s\n", subString);
	//Hacemos una limpieza del substring antes de insertarlo
	subString=strcpy(subString ,limpiezaDeString(subString,indice)); 
	//printf("Substring fixed : %s\n", subString);
	//printf("Cadena : %s\n", subcadena);
	//printf("indice : %d casos :%d largoR: %d largoLen : %ld subcadena  : %s \n",indice,casos,largoSubcadena,strlen(subcadena),subcadena);

	//Caso Borde, cuando el indice es igual a largo de  la subcadena
	if (indice == largoSubcadena)
	{		
		//char * subStringFinal  ;
		//subStringFinal =  limpiezaDeString(subcadena,largoSubcadena);
		//Pregunto si mi cadena se encuentra en algun nodo de la lista
		//if (estaEnListaEnlazada(P->subcadenas,subStringFinal)==1)
		if (estaEnListaEnlazada(P->subcadenas,subcadena)==1)	
		{
			//printf("Cadena : %s\n",subcadena );
			//printf("No esta\n");
			//printf("Substring  Final fixed : %s\n", subStringFinal);
			//insertar(P,subStringFinal,largoSubcadena,P->subcadenas->cabeza);
			insertar(P,subcadena,largoSubcadena,P->subcadenas->cabeza);
		}
		//free(subStringFinal);

	}
	//Casos Recursivos

	else{ 

		//Si no se encuentra pero ya hay un elemento en la cabeza
		if (estaEnListaEnlazada(P->subcadenas,subString)==1)
		{
			//printf("Substring fixed : %s\n", subString);
			insertar(P,subString,indice,P->subcadenas->cabeza);
			//free(subString);
		}
		//Llamada Recursiva
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
		if (casos+1 == largoSubcadena-(indice-1))
		{
			//Sigo Recorriendo recursivamente la cadena, reinicio los casos y paso al siguiente indice
			generarSubcadenasR (P ,subcadena ,largoSubcadena, indice+1,0);
		}
		else if (casos+1 < largoSubcadena-(indice-1))
		{
			//Sigo Recorriendo recursivamente la cadena, mantengo el indice y paso al sigueinte caso
			generarSubcadenasR (P ,subcadena ,largoSubcadena,indice,casos+1);
		}
	}
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
	//newString= malloc(sizeof(char));
	//free(newString);
	generarSubcadenasR(P,newString,largoSubcadena,3,0);
}

//Función que recorre la sopa de arriba hacia abajo buscando una subcadena en común
//Entrada : sopa, largo de la sopa , indice i , indice j , int indice donde se encuentra la letra encontrada , indi Palabra, subcadena
//char dir indica la dirección en la que me estoy moviendo = U  = arriba ,D = abajo , L = Izquierda
//char orden = , el orden que estoy siguiendo, O = orden , R = en reversa
//Salida : Subcadena con las coincidencias
void buscarSubcadenasV(char ** sopa , int n , int i , int j ,int  indiceP , palabra * P , char * subcadena, int * largoSub)
{
	//Primero me muevo de arriba hacia abajo
	//Caso borde
	//No puedo seguir bajando, ya que llege o al tope de la matriz o al tope de mi palabra
	if (i+1 == n || indiceP == P->largoPalabra)
	{
		*largoSub = *largoSub-1;
		//devuelvo subcadena
		//printf("Largo : %d\n", *largoSub );
		//printf("Subcadena : %s de %s\n",subcadena ,P->palabra);
	}
	//Casos Recursivos
	else if (i < n)
	{
		//Aigno al caracter la posicion donde mi encuentro en la sopa
		char caracter = sopa[i][j] ;
		//printf("CaracterS : %c\n",sopa[i][j]);
		//printf("CaracterP : %c\n",P->palabra[indiceP]);
		//pregunto si el caracter actual coincide con el caracter actuald e mi palabra
		if (caracter == P->palabra[indiceP])
		{
			//Si coinciden, la subcadena en su indice se asgina
			subcadena[*largoSub-1]= caracter ;
			//Aumento el largo de la subcadena 
			*largoSub = *largoSub + 1;
			//printf("Largo : %d\n", *largoSub );
			//Hago el llamado recursivo hacia arriba y en orden
			buscarSubcadenasV(sopa,n,i+1,j,indiceP+1 ,P,subcadena,largoSub);
		}
		//En caso de que no coincidan, termino la recursión
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
			//Declaramos una subcadena de tamaño 1
			int largoSub = 1;
			char * subcadena = (char*)malloc(sizeof(char)*largoSub);
			//Busqueda Vertical
			buscarSubcadenasV(sopa,n,i,j,coincidencias[indice],P,subcadena,&largoSub);
			//Pregunto si la subcadena es de un minimo de 3
			if (largoSub >= 3)
			{
				//printf("LargoR : %d LargoLen : %ld \n", largoSub ,strlen(subcadena));
				//printf("Caracter : %c [%d] [%d] \n",caracter,i,j ); 
				//printf("Subcadena : %s\n",subcadena );
				//char * temp = limpiezaDeString(subcadena,largoSub);
				//printf("temp1  :%s\n",temp);
				generarSubcadenas(P,subcadena,largoSub);
				//free(subcadena);
			}
			free(subcadena);
			//Recorro la sopa hacia la derecha con la palabra en orden
			//Reinicializamos la subcadena
			largoSub = 1;
			char * subcadena2= (char*)malloc(sizeof(char)*largoSub);
			//Busqueda Horizontal
			buscarSubcadenasH(sopa,n,i,j,coincidencias[indice],P,subcadena2,&largoSub);
			//Pregunto si la subcadena es de un minimo de 3
			if (largoSub >= 3)
			{
				//printf("LargoR : %d LargoLen : %ld \n", largoSub ,strlen(subcadena));
				//printf("Caracter : %c [%d] [%d] \n",caracter,i,j ); 
				//printf("Subcadena : %s\n",subcadena );
				//char * temp2 = limpiezaDeString(subcadena2,largoSub);
				//printf("temp2  :%s\n",temp2);
				generarSubcadenas(P,subcadena2,largoSub);
				//free(subcadena2);
			}
			free(subcadena2);	
			indice ++;
		}
	}
	//Libero la memoria dinámica
	free(coincidencias);
	//sigo recorriendo la sopa

	//Caso Borde
	//Si ambos siguientes indices son iguales al largo de la sopa, paro de hacer recursión e imprimo los elementos hayados
	if(i+1==n && j+1 == n)
	{
		imprimirHayazgos(P);
	}

	//Casos Recursivos
	//si mi siguiente indice i es igual a n pero mi inidice j sige siendo menor a n
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
	printf("Palabra : %s\n", P->palabra);
	printf("--------------------------------------------------------\n");
	busquedaDeSubcadenas(sopa,n1,0,0,P);

	//Casos Base : Ya no existe un siguiente palabra
	if (!P->siguiente)
	{
		printf("DONE\n");
	}
	//Casos Recursivos : Si existe un siguiente
	else if (P->siguiente)
	{
		//Solo si el i+1 no es igual al largo
		//Solo si hay un sigiente elemento sigo avanzando
		busqueda(sopa,n1,P->siguiente);
		
	}
}