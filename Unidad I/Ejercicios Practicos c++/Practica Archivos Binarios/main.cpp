#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "Persona.h"
#include "ArchivosBinarios.h"
#include "templatesOrdenamiento.h"

/**
*   @autor Brayan Montañez
**/

using namespace std;
ArchivosBinarios<Persona> arch("Datos.dat");

void imprimirListado(){
    arch.abrir(ios::in | ios::binary);
    arch.imprimir();
    arch.cerrar();
}

void ordenar(){
    int cont=0;
    arch.abrir(ios::in | ios::binary);
    Persona personas[arch.tamano()];
    arch.limpiar();
    arch.posicionar(0);

    while ( true ){
      arch.leer(personas[cont]);
      if ( arch.esFin() ) break;
      cont++;
    }
    arch.cerrar();

    //APLICANDO SELECCION DIRECTA (PUEDE USAR CUALQUIER OTRO DE LA PLANTILLA ORDENAMIENTOS)
    seleccionDirecta(&personas[0], cont);

    arch.abrir(ios::out | ios::binary);
    for(int i=0; i<cont; i++)
        arch.escribir(personas[i]);
    arch.cerrar();
}

void agregarPersona(){
    string nom; int ced;
    cin.sync();
    cout<<"Nombre(max 30 caracteres): "; getline(cin, nom);
    cout<<"Cedula: "; cin>>ced;

    Persona nuevaPersona((char *)nom.c_str(), ced);
    arch.abrir(ios::app | ios::binary);
        arch.escribir(nuevaPersona);
    arch.cerrar();

    ordenar();
}

void eliminarPersona(){
    arch.abrir(ios::in | ios::binary);
    int eliminar, tamano=arch.tamano(), cont=0;
    Persona personas[tamano];
    arch.cerrar();
    cin.sync();

    imprimirListado();
    do{
        cout<<"\nSeleccione numero de Persona a eliminar: ";
        cin>>eliminar;
        if(eliminar>tamano || eliminar<1) cout<<"Numero no valido vuelva a intentar"<<endl;
        else break;
    }while(true);

    //Extrayendo todos los datos del archivo a un vector auxiliar
    arch.abrir(ios::in | ios::binary);
    while ( true ){
      arch.leer(personas[cont]);
      if ( arch.esFin() ) break;
      cont++;
    }
    arch.cerrar();

    //Eliminando la posicion seleccionada por el usuario
    arch.abrir(ios::out | ios::binary);
    for(int i=0; i<cont; i++)
        if(i != (eliminar-1)) arch.escribir(personas[i]);
    arch.cerrar();
}

void consultar(){
    int ced, pos=0;
    cin.sync();

    cout<<"\nCedula a buscar: "; cin>>ced;

    Persona buscandoPersona("", ced);
    arch.abrir(ios::in | ios::binary);
    pos = arch.busquedaBinaria(buscandoPersona);
        if(pos != 0){
            cout<<"\nPersona Encontrada en la posicion "<<(pos+1)<<":\n"<<endl;
            cout<<"\t["<<(pos+1)<<"]"<<buscandoPersona<<endl;
        }
        else cout<<"Persona no encontrada"<<endl;
    arch.cerrar();
}


int main(){

    int opcion=0;
    do{
        system("cls");
        cout<<"\tMENU PRINCIPAL\n"<<endl;
        cout<<"[1] Imprimir Listado"<<endl;
        cout<<"[2] Agregar  Persona"<<endl;
        cout<<"[3] Eliminar Persona"<<endl;
        cout<<"[4] Consultar(buscar en lista)"<<endl;
        cout<<"[0] Salir"<<endl;
        cout<<"\tEntrada: "; cin>>opcion;

        switch(opcion){
            case 1:{
                system("cls");
                cout<<"\t LISTADO \n"<<endl;
                imprimirListado();
                cout<<"\nPresione enter para volver"; getch();
                break;
            }
            case 2:{
                system("cls");
                cout<<"\t AGREGAR PERSONA \n"<<endl;
                agregarPersona();
                cout<<"\nPersona agregada satisfactoriamente!"<<endl;
                cout<<"El archivo se ha ordenado por cedula automaticamente"<<endl;
                cout<<"Presione enter para volver";
                getch();
                break;
            }
            case 3:{
                system("cls");
                cout<<"\t ELIMINAR PERSONA \n"<<endl;
                eliminarPersona();
                cout<<"\nPersona eliminada satisfactoriamente!\nPresione enter para volver"; getch();
                break;
            }
            case 4:{
                system("cls");
                cout<<"\t BUSCAR(Consultar) \n"<<endl;
                consultar();
                cout<<"\n\nPresione enter para volver";getch();
                break;
            }
            default:{
                opcion=0;
            }
        }


    }while(opcion != 0);

    return 0;
}
