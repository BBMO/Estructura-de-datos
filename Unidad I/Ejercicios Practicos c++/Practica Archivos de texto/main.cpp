#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "Archivo.h"
#include "templatesOrdenamiento.h"

using namespace std;

int mostrarTablas(char *nombre = "nombres.txt"){
    char linea[180];
    int i=0, opcion;
    Archivo<string> tablas(nombre);
    if(strcmp("nombres.txt", nombre)==0)cout<<"\nSeleccione tabla\n"<<endl;
    tablas.abrirModoLectura();
    while(true){
        i++;
        tablas.leer(linea);
        if(strcmp("", linea)!=0) cout<<"["<<i<<"] "<<linea<<endl;
        if(tablas.esFin()) break;
    }
    cout<<"[0] Volver"<<endl;
    tablas.cerrar();
    cout<<"\tEntrada: ";
    cin>>opcion;

    return (opcion+1 > i || opcion==0)? 0 : opcion;
}

char *seleccionarTabla(int tabla, char *nombre = "nombres.txt"){
    char linea[180];
    int i=0;
    Archivo<string> tablas(nombre);

    tablas.abrirModoLectura();
    while(true){
        i++;
        tablas.leer(linea);
        if(i==tabla) break;
    }
    tablas.cerrar();

    return linea;
}

void mostrarContenido(int pos){
    char linea[180];
    Archivo<string> archivo("tabla.txt");
    archivo.setNombre(seleccionarTabla(pos));

    archivo.abrirModoLectura();
    while(true){
        archivo.leer(linea);
        cout<<linea<<endl;
        if(archivo.esFin()) break;
    }
    archivo.cerrar();

    archivo.cerrar();
    cout<<"\n\nEnter para continuar";
    getch();
}

void modificarColumnas(int pos){
    char nuevaColumna[180], linea[300];
    int opcion, id=0;
    Archivo<string> archivo("tabla.txt");
    archivo.setNombre(seleccionarTabla(pos)); //Toma el nombre de la tabla de posicion dada en el menu


            id=0;
            archivo.abrirModoLectura();
            archivo.leer(linea);
            while(strcmp(linea, "")!=0){
                id++;
                archivo.leer(linea);
            }
            char vec[id][300];
            archivo.cerrar();

            id=0;
            archivo.abrirModoLectura();
            archivo.leer(linea);
            while(strcmp(linea, "")!=0){
                strcpy(vec[id], linea);
                id++;
                archivo.leer(linea);
            }
            archivo.cerrar();

            cout<<"\tNombre nueva Columna: ";
            cin>>nuevaColumna;

            for(int i=0; i<id; i++){
                if(i==0) strcat(vec[i], nuevaColumna);
                else strcat(vec[i], "NULL");

                strcat(vec[i], ",");
            }

            //ESCRIBIENDO EN EL ARCHIVO
            archivo.crear();

            for(int i=0; i<id; i++){
                if(i<(id-1))archivo.escribir(vec[i], true);
                else archivo.escribir(vec[i], false);
            }


            archivo.cerrar();

    cout<<"\n\tColumna agregada, presione enter para volver";
    getch();

}

void crearTabla(char* nombre){
    Archivo<string> tablas("nombres.txt");

    //Agrego nuevo nombre de tabla al archivo nombres
    tablas.abrirModoEscritura();
    tablas.escribir(strcat(nombre, ".txt"), true);
    tablas.cerrar();

    Archivo<string> nueva(nombre);
    nueva.crear();
    nueva.escribir("id,");
    nueva.cerrar();

    cout<<"Tabla creada satisfactoriamente, vaya a modificar sus columnas (enter para continuar)"<<endl;
    getch();
}

void agregarFila(int pos){
    char linea[200], lineaAux[200], buffer[33];
    int id=0;
    Archivo<string> archivo("tabla.txt");
    archivo.setNombre(seleccionarTabla(pos)); //Toma el nombre de la tabla de posicion dada en el menu
    archivo.abrirModoLectura();

    //ID autoincrementable
    archivo.leer(linea); //linea extraida
    strcpy(lineaAux, linea);
    while(strcmp(linea, "")!=0){
        id++;
        archivo.leer(linea);
    }
    archivo.cerrar();
    //Doy apertira de escribir en el archivo
    archivo.abrirModoEscritura();
    itoa(id,buffer,10);
    archivo.escribir("\n");
    archivo.escribir(strcat(buffer, ","));

    //Pido datos por columna y envio al archivo
    char *ptr, dato[50];
    ptr = strtok(lineaAux,",");
    ptr = strtok(NULL, ",");
    while(ptr != NULL){
      cin.sync();
      cout<<"\t"<<ptr<<": ";
      cin.getline(dato, 50);
      archivo.escribir(strcat(dato, ","));
      ptr = strtok(NULL, ",");
    }

    archivo.cerrar();
    cout<<"\n\tFila agregada, presione enter para volver";
    getch();
}

void ordenar(int pos){

    char linea[50], lineaaux[50];
    int i=0, opcion;
    Archivo<string> archivo("tabla.txt");
    archivo.setNombre(seleccionarTabla(pos)); //Toma el nombre de la tabla de posicion dada en el menu

    //Creando vector
    archivo.abrirModoLectura();
    archivo.leer(linea); //linea extraida
    while(strcmp(linea, "")!=0){
        i++;
        archivo.leer(linea);
    }
    archivo.cerrar();
    string v[i-1], vaux[i-1];

    archivo.abrirModoLectura();
    archivo.leer(linea);
    archivo.cerrar();

    //Pido datos por columna y envio al archivo
    i=0;
    cout<<"\nSELECCIONE POR QUE COLUMNA DESEA ORDENAR"<<endl;
    char *ptr;
    ptr = strtok(linea,",");
    while(ptr != NULL){
      i++;
      cout<<"["<<i<<"]"<<ptr<<endl;
      ptr = strtok(NULL, ",");
    }
    cout<<"\tEntrada: ";
    cin>>opcion;

    int j=0;
    archivo.abrirModoLectura();
    archivo.leer(linea);
    while(strcmp(linea, "")!=0){
        i=0;
        archivo.leer(linea);
        strcpy(lineaaux, linea);
        ptr = strtok(linea,",");
        while(ptr != NULL){
          i++;
          if(i==opcion){
            v[j]=ptr;
            vaux[j]=lineaaux;
            j++;
          }
          ptr = strtok(NULL, ",");
        }
    }
    archivo.cerrar();

    //ORDENAR
    seleccionDirectaAdaptadoPractica(&v[0], j, &vaux[0]);

    cout<<"\n-------------------------------"<<endl;
    for(int i=0; i<j;i++)
        cout<<vaux[i]<<endl;

    cout<<"\n\n....... presione enter para volver";
    getch();
}

int main(){
    Archivo<string> tablas("nombres.txt");
    if(!tablas.abrirModoLectura())tablas.crear();
    tablas.cerrar();

    int opcion;
    do{

        cout<<"[1] Mostrar Tablas y contenidos"<<endl;
        cout<<"[2] Crear Tabla"<<endl;
        cout<<"[3] Agregar columnas de Tabla"<<endl;
        cout<<"[4] Agregar Fila a Tabla"<<endl;
        cout<<"[5] Mostrar datos ordenados segun columna"<<endl;
        cout<<"[0] salir"<<endl;

        cout<<"Entrada: ";
        cin>>opcion;

        switch(opcion){
            case 1:{
                int tabla = mostrarTablas();
                cout<<"\n\n";
                if(tabla != 0) mostrarContenido(tabla);
                break;
            }
            case 2:{
                char nom[50];
                cout<<"\nNombre de la nueva Tabla sin .txt: ";
                cin>>nom;
                crearTabla(nom);
                break;
            }
            case 3:{
                system("cls");
                cout<<"A CUAL TABLA DESEA AGREGAR COLUMNA"<<endl;
                int tabla = mostrarTablas();
                if(tabla != 0) modificarColumnas(tabla);
                break;
            }
            case 4:{
                system("cls");
                cout<<"A CUAL TABLA DESEA AGREGAR FILA"<<endl;
                int tabla = mostrarTablas();
                if(tabla != 0) agregarFila(tabla);
                break;
            }
            case 5:{
                system("cls");
                cout<<"CUAL TABLA DESEA VER ORDENADA"<<endl;
                int tabla = mostrarTablas();
                if(tabla != 0) ordenar(tabla);
                break;
            }
        }

        system("cls");
    }while(opcion!=0);

    return 0;
}
