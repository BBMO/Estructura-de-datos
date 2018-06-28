#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "myconio.h"
#define Max 23 //La palabra mas larga "ELECTROENCEFALOGRAFISTA"

/**
*   AUTOR: Brayan Bladimir Montañez Ortiz;
*   CI.: V.-27270063
**/


using namespace std;

int longitud(char V[]){

	int tam =0; int i=0;

	while(V[i] != 0){
		tam++; i++;
	}

	return tam;
}

int numeroElementosArray(char V[][Max]){

	int tam=0; int i=0;

	while(V[i][0] > 0){
		tam++; i++;
	}

	return tam;
}

int DeterminarMaxIndex(char V[][Max]){

	int max = 0; int i,j;

	for(i = 0 ; i < numeroElementosArray(V) ; i++){
		if(longitud(V[i]) > max){
			max = longitud(V[i]);
		}
	}

	return max;
}

/** TEST **/
void ImprimirVector(int V[], int N){
	int i;
	for(i = 0 ; i < N ; i++){
		cout << V[i] << " ";
	}
}

int numeroMax (int v[], int n) {

	int i;
    int numMayor = -1;

      for(i = 0; i < n; i++){
        if(v[i] > numMayor)
          numMayor = v[i];
      }

    return numMayor;

}

void asignandoVectorAuxiliar(char Vaux[][Max], char V[][Max], int Size){
     for (int i = 0; i < Size; i++){
        strcpy(Vaux[i], V[i]);
    }
}


/** VP vector que va a contener el codigo ASCII de la letra seleccionada **/
/** V vector que contiene las palabras **/
void RadixSort(char vecPalabras[][Max], int vecPosiciones[],int Size){

	int Index = DeterminarMaxIndex(vecPalabras);
    char Vaux[Size][Max];
    asignandoVectorAuxiliar(Vaux, vecPalabras, Size);
	int i,j,z=0;

	/**
        Recorro todos los indices de las cadenas de caracteres
	**/
	while(Index > 0){
        cout<<"\n"<<endl;
        textcolor(LIGHT_RED);
        	cout << "\tOrdenacion en base al caracter: " << Index;
        textcolor(WHITE);

        Index -= 1;

        /**
           Vector paralelo del caracter de la cadena requerido
           este vector toma el ASCII del caracter para ser ordenado
           por el radix sort numerico
        **/
        for(j = 0 ; j < Size ; j++){
            vecPosiciones[j] = (int) tolower(vecPalabras[j][Index]);
        }
        cout<<endl;

        /**********************************/
        /****** RADIXSORT NUMERICO  *******/
        /**********************************/
          int salida[Size];
          int divisor = 1;
          int posicionNueva=0;
          int numMayor = numeroMax(vecPosiciones, Size);

          /** Bucle hasta que se haga 0 el numero mas grande del arreglo **/
          while (numMayor / divisor > 0){

            /**
                TEST =>
                ImprimirVector(VP, Size);
                cout<<endl;
                for (i = 0; i < Size; i++){
                    cout<<V[i]<<"\t";
                }
            **/

            int contador[10] = { 0 };

            /**
                Cuenta cuantos digitos en el intervalo [0, 9] hay
                al descomponer el numero en el digito requerido en el recorrido
            **/
            for (i = 0; i < Size; i++)
              contador[(vecPosiciones[i] / divisor) % 10]++;

            /**
                Esta Operacion marca el recorrido que hay en el
                intervalo [0, 9] sumando la posicion actual con la anterior
                en caso de no haber cifra en algun tramo del intervalo
                el numero se repetirá
            **/
            for (i = 1; i < 10; i++)
              contador[i] += contador[i - 1];

            /**
                Asigno valores a un vector auxiliar de salida
                El calculo esta dado en relacion a la cifra del numero (requerida en el recorrido)
                y su valor en el contador
                e.j.:
                Primer recorrido
                513 % 10 = 3;
                entonces toma la posicion 3 de mi arreglo contador
                y al valor contenido le resta 1 y esa es la nueva
                posicion en el arreglo de salida.

                La asignacion del orden de cadenas de caracteres viene dada
                por VP por ser un arreglo paralelo
            **/
            for (i = Size - 1; i >= 0; i--){
              posicionNueva = --contador[(vecPosiciones[i] / divisor) % 10];
              salida[posicionNueva] = vecPosiciones[i];
              strcpy(Vaux[posicionNueva], vecPalabras[i]);
            }

            /** Asignando datos a los arreglos principales **/
            for (i = 0; i < Size; i++){
                vecPosiciones[i] = salida[i];
                strcpy(vecPalabras[i], Vaux[i]);
            }

            /**Me muevo al siguiente digito**/
            divisor *= 10;

            /**
                TEST =>
                cout<<endl;
                system("pause");
            **/
          }
        /**************************************/
        /****** FIN RADIXSORT NUMERICO  *******/
        /**************************************/



        /** IMPRIMIENDO RESULTADO DE LA FASE CARACTER(Indice) **/
        /** TEST => ImprimirVector(VP, Size);**/
        textcolor(LIGHT_WHITE);
          for (i = 0; i < Size; i++){
             cout<<"\t"<<vecPalabras[i];
          }
        textcolor(WHITE);

	}


}

int main(){

	char vecPalabras[][Max] = { "react", "csharp", "heroku", "android", "estructuras", "angular", "laravel"};
	int N = numeroElementosArray(vecPalabras);
	int *VP = new int[N];
	int i,j;

	cout<<"ARREGLO DE PALABRAS DESORDENADO: ";
	for (i = 0; i < N; i++){
         cout<<vecPalabras[i]<<"\t";
    }

    textcolor(LIGHT_BLUE);
    cout<<"\n\n\t----------------------------\n";
    cout<<"\tAplicando RADIXSORT ADAPTADO\n";
    cout<<"\t----------------------------";
    textcolor(WHITE);

    //Aplicando RadixSort
	RadixSort(vecPalabras,VP,N);

	textcolor(LIGHT_BLUE);
	cout<<"\n\n\t----------------------------\n";
	cout<<"\tFIN RADIXSORT ADAPTADO\n";
	cout<<"\t----------------------------";
	textcolor(WHITE);

    getch();
	return 0;
}







