//Laboratorio número 2 EDA 
//Autor : Javier López Campos , 20.243,378-2
//Fecha de Inicio : 08/
//MODULO DE IMPORTACIONES
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include "TDA_lista_enlazada.h"
#include "entradasYSalidas.h"
#include "busqueda.h"


//función que se encarga de ejecutar cada función
//Sin entradas ni salidas
void menu ()
{
    //Variables para medir el tiempo
    //time_t start_t, end_t;
    //double diff_t;
    //time(&start_t);
    
    //Arreglos
    int n1 ;
    char ** sopa = NULL ;
    //printf("ES mayor : %s %s = %d  \n","eje" ,"emp",mayorAlfabetico("eje",3,"emp",3,0));
    //printf("ES mayor : %s %s = %d  \n","abedul" ,"aabedul",mayorAlfabetico("abedul",6,"aabedul",7,0));
   	//printf("ES mayor : %s %s = %d  \n","aabedul","abedul" ,mayorAlfabetico("aabedul",7,"abedul",6,0));
    //printf("%s > %s  : %d\n","aabe" , "aala","aabe" > "aala" ); //= 0
    //printf("A < B  : %d\n",'a' < 'b' ); //= 1
    //printf("A = B  : %d\n",'a' == 'b' ); //= 0
    //Entradas de archivos fijas
    char nombreDeArchivo [50];
    printf("Escriba el nombre de su archivo sopa sin extensión\n");
    printf("Ejemplo : sopa\n");
    scanf ("%s",nombreDeArchivo);
    strcat(nombreDeArchivo , ".in");

    //Si se logro leer correctamente el archivo
    if (leerArchivoSopa(&sopa , nombreDeArchivo, &n1))
    {
    	//Solo en caso de que el largo de la sopa sea menor a 20, muestro por pantalla la sopa
        if (n1<= 20)
        {
            printf("\nSu sopa es :\n");
            imprimirSopa(sopa,n1);
        }
        //Tamaño del arreglo de palabras y el arreglo de palabras
        int n2 ;
        palabra * arregloPalabra= NULL ;
        //Más entradas
        printf("\nAhora escriba el nombre de su archivo de letras a encontrar sin extension\n");
        printf("Ejemplo : palabras\n");
        scanf ("%s",nombreDeArchivo);
        strcat(nombreDeArchivo , ".in"); 
        //char nombreDeArchivo2 [50] 
        if  (leerArchivoPalabra(&arregloPalabra ,  nombreDeArchivo ,&n2 ))
        {  
            imprimirPalabras (arregloPalabra , 0,n2);
            listaP * listaPalabras = (listaP*)malloc(sizeof (listaP));
            listaPalabras->largo = n2;
            palabra * puntero = (palabra*)malloc(sizeof (palabra));
            //palabra * puntero = NULL;
            listaPalabras->cabeza = puntero;
            trabasijarArrregloToLista(arregloPalabra,listaPalabras,listaPalabras->largo,0, puntero);
            busqueda(sopa ,n1 ,puntero);

            char nombreSalida [100] ;
            printf("\nIngrese el nombre de su Archivo de salida sin extension\n");
            scanf("%s",nombreSalida);
            strcat(nombreSalida,".out");
            printf("Archivo de salida : %s \n" , nombreSalida);
            escribirArchivo(listaPalabras,nombreSalida);
        }
        //Liberación de memoria dinamica
        free( arregloPalabra);
        for (int i = 0; i < n1 ; ++i)
        {
            free (sopa[i]);
        }
    }
    else
    {
        printf("F , arrivadercci , \n");
    }

    //Termino del algoritmo

    //time(&end_t);
    //Diferencia
    //diff_t = difftime(end_t, start_t);
    //printf("Tiempo de ejecución :%f\n", diff_t);
}
void main (){menu();}   