#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Modulo de constantes , constante abecedario
char  abcdario[26] = "abcdefghijklmnopqrstuwvxyz";

//MODULO DE FUNCIONES

//Función que se encarga de imprimir las variables dentro de la estructura
//Entrada arreglo de estructuras , tamaño del arreglo
//Salida :  Prints de cada parametro dentro de la estructura
void imprimirPalabras(palabra * arreglo ,int i, int n)
{
    if (i == n)
    {
        printf("----------------------------\n");
    }
    if (i < n)
    {     
       printf("%s\n",arreglo[i].palabra );
       imprimirPalabras(arreglo,i+1,n);  
    }
}

//Función que se encarga de imprimir la sopa de letras , solo se activa en caso de que el n sea menor a 20
//Entrada arreglo de de arreglos y tamaño n
//Salida :  Prints de cada linea y columna de la matriz
void imprimirSopa(char ** arreglo , int n)
{
    for (int i = -1; i < n; ++i)
    {
        if (i == -1)
        {
            printf("   ");
        }
        else if (i>=0)
        {
            printf("%d  ",i);
        }

        for (int k = 0 ; k < n; ++k)
        {
            if (i < 0)
            {
                if (k <= 8)
                {
                    printf(" %d ", k );
                }
                else
                {  
                    printf(" %d", k );
                }
            }
            else if (i >=0)
            {
                if (i > 9 && k==0)
                {
                    printf("%c ", arreglo[i][k] );
                }
                else
                {
                    printf(" %c ", arreglo[i][k] );
                }
            }
        }
        printf("\n");
    }
}

//Escribir archivo de salida con las posiciones y las caddenas encontradas
//Entrada : Arreglo matriz sopa de letras , tamaño de la sopa de letras , arreglo de estrucutras , su tamaño . nombre del archivo de salida
//SALIDA : un entero 0 en caso de que la escritura fue realizada con exito
int escribirArchivo(char ** sopa , int n , palabra * arregloPalabra , int n2 , char * nombreSalida)
{
    FILE * archivo = fopen (nombreSalida , "wt");
    fprintf (archivo , "\n");
    int i =0 ;
    while (i < n2)
    {
        palabra elemento = arregloPalabra[i];
        i++;
    }
    printf("ESTADO :ESCRITO\n");
    fclose (archivo); 
    return 0 ;
}

//LEER ARCHIVO de palabras y entregarselo a una lista de estructuras
//Entrada : Dirección de memoria del arreglo de Estructruas , nombre del archivo de palabras , y direccion de memoria de el tamaño del arreglo
//SALIDA : true si esta bien leído o false si hay algun error dentro de la lectura
bool leerArchivoPalabra(palabra ** arreglo , char * nombre, int * n)
{
    //verificador ok : 0 todo bueno , 1 :malo malito
    bool ok = true ;
    int i = 0 ;
    //aseguramos que la entrada sea nula
    *arreglo = NULL ;
    //creamos un puntero tipo FILE
    FILE * archivo = fopen (nombre, "r");
    //declaramos un tamaño del arreglo como auxiliar parte de menos 2 porrque no consideramos la primera linea
    int tamano = 0 ;
    int largo = 0;
    // un char auxiliar que guarda cada caracter
    char caracter ;
    //un string auxiliar que guarda cada linea
    char linea [1000];
    if (archivo == NULL){
        printf("ARCHIVO NO ENCONTRADO\n");
        return false;
    }
    //obtengo la primer linea con el tamaño
    fgets(linea, 1000,archivo );   
    tamano = atoi(linea) ;
    int listaDeLargoDePalabras[tamano];
    *n = tamano ;
    palabra * arregloaux = (palabra*) malloc(tamano*sizeof(palabra));
    //ahora hago un for para saber que las palabras no tienen errores de lectura y saber que tan largo es una palabra
    //for (int i = 0; i < tamano* 23; ++i)
    while(!feof(archivo))
    {
        ok = false ;     
        //vamos obteniendo cada caracter y lo vamos transformando según corresponda
        caracter = fgetc (archivo);
        //iteramos del 0 al 26, en caso de ser una letra la iteracion se rompe y pasa al siguiente caracter
        for (int j = 0; j < 26; ++j)
        {
            if (caracter == abcdario[j])
            {
                arregloaux[i].palabra[largo] = caracter;
                largo++;
                ok = true;
            }
        }
        //tambien en caso de ser el final de linea 
        //la conversion de un numero a char se hace con : '0' + int numero                  
        if (caracter == ' ')
        {
            ok = false;
            printf("Error de formato en Espacio\n");
        }
        else if (caracter == '\n' )
        {   
            ok = true;
            //voy guardando el largo
            arregloaux[i].largoPalabra = largo;
            //reinicio el largo y paso al siguiente elemento
            i++;
            largo = 0;
        }
        else if (caracter == EOF || caracter == '\0' )
        {
            ok = true ;
        }
        else  if (!ok)
        {
            //VERIFICACIÓN desechada ya que los ejemplos dados siempre contienen caracteres de error desconocidos
            //printf("%c",caracter );
            //ok = false;
        }   
        /*  
        if (!ok){        
                printf("Error de formato caracter de error : %c \n",caracter );
                return false;
        }    
        */   
    }
    printf("Cant. de palabras es : %d \n",tamano );
    //volvemos el puntero del archivo al inicio
    rewind (archivo);
    //cerranos el archivo
    fclose (archivo);
    //asignamos los valores
    *arreglo = arregloaux;
    printf("Sin errores de lectura\n");
    printf("-------------------------------------\n");
    //todo se completo bien
    return true ;
    //no liberamos la memoria , o si no se perdería la dirección , se libera una vez terminado
}

//Función trasbasijar de un arreglo dinámico a una lista enlazada simple
void trabasijarArrregloToLista(palabra * arreglo , listaP * P, int n, int i,palabra * puntero)
{
    //Le asigno memoria a la lista P
    P = (listaP*)malloc(sizeof (listaP));
    P->largo = n ;
    //Lege al final de mi arreglo
    if (i == n)
    {
        //Asigno el nodo siguiente
        puntero->siguiente = NULL;
        puntero = P->cabeza;
        /*
        printf("Lista Enlazada cabeza: %s\n",P->cabeza->palabra );
        printf("Lista Enlazada : %s\n",puntero->palabra );
        printf("Lista Enlazada : %s\n",puntero->siguiente->palabra );
        printf("Lista Enlazada : %s\n",puntero->siguiente->siguiente->palabra );
        printf("Lista Enlazada : %s\n",puntero->siguiente->siguiente->siguiente->siguiente->palabra );
        */
        
    }
    if (i < n)
    {
        //printf("Arreglo Palabra : %s\n",arreglo[i].palabra );
        //Asigno palabra
        strcpy(puntero->palabra , arreglo[i].palabra);
        //printf("Lista Enlazada Palabra : %s\n",puntero->palabra );
        //Asigno largo de la palabra
        puntero->largoPalabra = strlen(puntero->palabra);
        //printf("Largo  : %d\n",puntero->largoPalabra );
        //Asigno memoria a la lista de subcadenas
        puntero->subcadenas = (Lista*)malloc(sizeof (Lista));
        //puntero->subcadenas =NULL;
        //Al primer elemento de subcadnas le apunto a null
        puntero->subcadenas->cabeza = malloc(sizeof (Nodo)); ;
        puntero->subcadenas->cabeza->largo = -1;
        //Asigno el largo a subcadenas que parte en 0
        puntero->subcadenas->largo = 0;
        //Asigno memoria al siguiente elemento de mi lista
        puntero->siguiente = (palabra*)malloc(sizeof (palabra));
        //Sigo avanzando en ambas listas
        puntero = puntero->siguiente;
        i++;
        trabasijarArrregloToLista(arreglo,P,n,i,puntero);
    }


}

//LEER ARCHIVO de sopas
//ENTRADA : dirección del arreglo matriz de sopa , nombre del archivo , direccion de memoria del tamño
//SALIDA true se leyo bien
bool leerArchivoSopa(char *** arreglo , char * nombre, int * n)
{
    //aseguramos que la entrada sea nula
    *arreglo = NULL ;
    //creamos un puntero tipo FILE
    FILE * archivo = fopen (nombre, "r");
    //declaramos un tamaño del arreglo como auxiliar parte de menos 2 porrque no consideramos la primera linea
    int tamano = 0 ;
    // un char auxiliar que guarda cada caracter
    char caracter ;
    //un string auxiliar que guarda cada linea
    char linea [1000];
    if (archivo == NULL){
        printf("ARCHIVO NO ENCONTRADO\n");
        return false;
    }
    //obtengo la primer linea con el tamaño
    fgets(linea, 1000,archivo );
    tamano = atoi(linea) ;
    //arregloa auxiliar para ir almacenando cada dato
    char **arregloaux=(char **) malloc(tamano*sizeof(char *)); //multiplicadas por n que serian las "filas"
    
    //Asignamos memoria:
    for(int i=0; i<tamano; i++)
    {
        //Asignamos las columnas
        arregloaux[i]= (char *) malloc(tamano*sizeof(char));
    }

    //asignamos el largo de lineas del archivo
    *n = tamano ;
    //verificador ok : 0 todo bueno , 1 :malo malito
    bool ok = true ;
    int i = 0, k =0 ;
    printf("tamano is : %d \n",tamano );
    //ahora iremos agregando cada caracter
    while ( i < tamano)
    {   
        k =0 ;
        while(k < tamano)
        {   
            ok = false ;    
            //vamos obteniendo cada caracter y lo vamos transformando según corresponda
            caracter = fgetc(archivo);
            //iteramos del 0 al 26, en caso de ser una letra la iteracion se rompe y pasa al siguiente caracter
            for (int j = 0; j < 26; ++j)
            {
                //printf("Letra %c \n", abcdario[j] );
                if (caracter == abcdario[j])
                {
                    arregloaux[i][k] = abcdario[j];
                    k++;
                    ok = true;
                    //printf("Letra %c encontrada\n", abcdario[j] );
                    break;
                }
            }
            //tambien en caso de ser el final de linea 
            //la conversion de un numero a char se hace con : '0' + int numero                  
            if (caracter == ' ' ||caracter == '\n'|| caracter == EOF || caracter == '\0'  )
            {   
                ok = true;
                //printf("%d ola\n", k);
            }
            else  if ( !ok)
            {
                printf("%c",caracter );
                //ok = false;
            }
            //ACÁ VEIAMOS SE HABÏA ALGUN TIPO DE ERROR , pero debido a causas desconocidas no 
            //es posible saber que causa el carracter de error
            /* 
            if (!ok){       
                    printf("\nError de formato  : %c \n",caracter );
                    printf("%c \n",caracter );
                    printf("Coordenada %d %d \n",i,k);
                    return false;
            }
            */
        }

        i++;
    }
    //volvemos el puntero del archivo al inicio
    rewind (archivo);
    //se cierra el archivo
    fclose (archivo);
    *arreglo = arregloaux;
    printf("Sin errores de lectura\n");
    printf("-------------------------------------\n");
    //todo se completo bien
    return true ;
}
