#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>

/**
*   @autor Brayan Montañez
**/
using namespace std;

template<class T>
class Archivo{

		char nom[40];
		T buffer;//Para implementacion en otra clase
		fstream obj;
		int N;
	public:
		Archivo(){}
		Archivo(char *c){strcpy(nom, c);}

		/**** Archivos .txt ****/
		void abrir( const std::_Ios_Openmode &t );
		bool falla();
		void cerrar();
		void escribir(string datos, bool finLinea = false);
		void leer(char cad[]);
		void leerCampo(char cad[], char delimitador);
		bool esFin();
		int tamano();
		void posicionar(int p);
		void imprimir();
		/**********************/

		//Para implementacion en otra clase
		void convertir(char cad[], T (*f)(char *k)){buffer = f(cad);}
        T getBuffer(){return buffer;}

        //SETTERS
		void setNombre(char *c){strcpy(nom, c);}

};

/*************************/
/**    ARCHIVOS .txt    **/
/*************************/

//Abrir archivo para leer datos
template<class T> void Archivo<T>::abrir(const std::_Ios_Openmode &t){
    this->obj.open(nom, t);
}

template <class T> bool Archivo<T>::falla(){
    return obj.fail();
}

template<class T> void Archivo<T>::cerrar(){
    obj.close();
}

template<class T> void Archivo<T>::escribir(string datos, bool finLinea){
    obj << datos;
    if(finLinea) obj<<endl;
}

template<class T> void Archivo<T>::leer(char cad[]){
    obj.getline(cad, 180,'\n');
}

template<class T> void Archivo<T>::leerCampo(char cad[], char delimitador){
    obj.getline(cad, 180, delimitador);
}

template<class T> bool Archivo<T>::esFin(){
    return obj.eof();
}

template <class T> void Archivo<T>::posicionar( int p ){
    obj.seekg(p*sizeof(T), ios::beg );
}

template <class T> int Archivo<T>::tamano(){
     char linea[150];
     N=0;

     do{
        leer(linea);
        N++;
        if(esFin()) break;
     }while(true);

     return N;
}


template <class T> void Archivo<T>::imprimir(){
     char linea[150];
     int n=0;
     posicionar(0);
     do{
        leer(linea);
        cout<<"["<<++n<<"]"<<linea<<endl;
        if(esFin()) break;
     }while(true);
}
/*************************/
/*************************/
































