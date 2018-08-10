#include <iostream>
#include <string.h>
#include <conio.h>

using namespace std;

template <class T>
class Pila{
	int tam;
	T *v, valini;
	int tope;
	public:
		Pila(int n, T ini);
		int  Agregar(T ele);
		int  Eliminar(T &Eli);
		void Imprimir();
		int getTope(){return this->tope;}
};

template <class T>
Pila <T>::Pila(int n, T ini){
	tam=n;
	tope=-1;
	v= new T[tam];
	if(!v)
     	cout<<"Falla de Memoria"<<endl;
	else { 
	    valini=ini;
	    for ( int i=0; i<tam; i++)
	        v[i]=ini;
    }
}

template <class T>
int Pila <T>::Agregar(T ele){
	if(!v)return -1;
	if(tope==tam-1)return 0;
	v[tope+1]=ele;
	tope++;
	return 1;
}

template <class T>
int Pila <T>::Eliminar(T &eli){
	if(!v) return -1;
	if(tope==-1) return 0;
	eli=v[tope];
	v[tope]=valini;
	tope--;
	return 1;
}

template <class T>
void Pila <T>::Imprimir(){
    cout<<"Pila:\n";
	for(int i=0;i<=tope; i++)
		cout<<v[i]<<endl;	
}
