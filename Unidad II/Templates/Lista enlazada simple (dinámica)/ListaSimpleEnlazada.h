/**
* @autor Brayan Montañez
**/
/*
*	LISTAS ENLAZADAS DINÁMICAS (simplemente enlazada)
*	ListaSE
*/

using namespace std;
#include "Nodo.h"

template <class T>
class listaSE
{
        Nodo<T> *cab;
    public:
        Nodo <T> *getCab() { return cab; }
        listaSE ( ) { cab=NULL; }
        int  agregar  ( T E );
        int  eliminar ( T &E);
        bool buscar(T &E, Nodo<T> **p=NULL, Nodo<T> **ant=NULL);
        void imprimir ( );
        int modificar(T E);
};

//Agregar
template <class T> int listaSE <T>::agregar(T E){
	Nodo<T> *nue, *p, *ant;

	nue = new Nodo<T>(E);

	if(!nue) return -1;

	if(cab==NULL) cab=nue;
	else {
		ant=NULL;
		p=cab;

		while(p){ //(p!=NULL)

			if(E<p->getInfo()) break;
			else { // Moverse por la estructura
				ant=p;
				p=p->getSig();
			}

		} // Final While

		if(p==cab){ // Caso insercion en cabecera.
			nue->setSig(cab);
			cab=nue;
		}
		else{
			ant->setSig(nue);
			nue->setSig(p);
		}
	}

	return 1;
}

//Eliminar
template <class T> int listaSE<T>::eliminar( T &E){
      Nodo<T> *p= cab, *ant; int r;
      ant = NULL;
      if ( !cab ) return -1;
      if ( buscar(E, &p, &ant) ){ //Encontrado?
      		//Casos de eliminacion
            if (p==cab){
               cab= cab->getSig();
            }
            else{
           	    ant->setSig(p->getSig());
            }
           delete p;
           return 1;
      }
      else
          return 0;//No encontrado

}


//Buscar
template <class T> bool listaSE<T>::buscar(T &E, Nodo<T> **p, Nodo<T> **ant){
	while(*p != NULL){
		if((*p)->getInfo() == E){
			E=(*p)->getInfo();
			return true;
		}
		else {
			*ant=*p;
			*p=(*p)->getSig();
		}
	}

	return false;
}

//Modificar
template <class T> int listaSE<T>::modificar (T E){
	Nodo <T> *p=cab;
	while(p){
		if(p->getInfo()==E){
			p->setInfo(E);
		}
		p = p->getSig();
	}
}


//Imprimir
template <class T> void listaSE<T>::imprimir ( ) {
      Nodo<T> *p=cab;
      while(p){
      	cout<<p->getInfo()<<endl;
         p = p->getSig();
	  }

}
