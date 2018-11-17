#ifndef ArbolBin_H
#define ArbolBin_H
#include "NodoA.h"
#include "Nodo.h"
#include "bicola.h"

/**
** @auth Brayan Montañez
** @repo https://github.com/@BBMO
**/
template <class T> class ArbolBin{
	NodoA<T> *raiz, *p, *discordia, *ant;
	bool esAVL, hayDiscordia; // indica si esta balanceado o no
	public:
		ArbolBin();
		ArbolBin(bool tipo); // true: balanceado

		int agregar(T e,bool band =false);
		int procesarEliminacion(T ele);
		int eliminar(NodoA<T> *p,NodoA<T> *padre,bool prefDer=true,bool reordenando = false);
		int altura(NodoA<T> *p);
        int numNodo(NodoA<T> *p);
        int factorE(NodoA<T>*p);

		bool esHoja(NodoA<T> *p);
		bool buscar(T E, NodoA<T> *pt=NULL, bool band1=false);

		void imprimir(int tipo=0); // tipo de recorrido
		void preorden(NodoA<T> *p, int niv);
		void inorden(NodoA<T> *p, int niv);
		void postorden(NodoA<T> *p, int niv);
		void anchura();
		void setEsAVL(bool b){esAVL = b;}
		void calcularFE(NodoA<T> *p);
		void reestructurar(NodoA<T> *p);

        NodoA<T> *getRaiz(){return raiz;}
        NodoA<T>* buscarEli(T &ele,NodoA<T> *p,NodoA<T>**padre=NULL,bool buscEli=false);
        NodoA<T> *menor(NodoA<T> *p,NodoA<T> **pad);
        NodoA<T> *mayor(NodoA<T> *p,NodoA<T> **pad);
};

template<class T> ArbolBin<T>::ArbolBin(){
	raiz=NULL;
	esAVL=false;
}

template<class T> ArbolBin<T>::ArbolBin(bool tipo){
	raiz=NULL;
	esAVL=tipo;
}

template<class T> int ArbolBin<T>::agregar(T e,bool band){
	NodoA<T> *nue, *p;
	nue = new NodoA<T>(e);
	if(nue==NULL)return 0;
	if(raiz==NULL)raiz=nue;
	else{
		if(buscar(e)==true && band==true) return 0;
		if(e<ant->getInfo()) ant->setHI(nue);
		else ant->setHD(nue);
	}

	if(esAVL)
        do{
            //cout<<endl<<"evaluando"<<endl;
            hayDiscordia=false;
            calcularFE(raiz);
            //cout<<endl<<"viendo discordia"<<endl;
            if(hayDiscordia){
                //cout<<"recien llena"<<endl;
                //imprimir(1);
                //cout<<"-------------------"<<endl;
                //cout<<endl<<"desequilibrado"<<endl;
                reestructurar(discordia);
            }
        }while(hayDiscordia);
	else{
		//cout<<endl<<"en equilibrio"<<endl;
	}
	return 1;
}

template <class T> bool ArbolBin<T>::buscar(T E, NodoA<T> *pt, bool band1){
	bool band=false;

	bicola<T> recorrido;

	if(raiz==NULL) return false;
	if(pt==NULL){
		p=raiz;
		ant=NULL;
	}
	else p=pt;

	while(p && !band){
		if(band1) recorrido.agregar(p->getInfo());
		if(E==p->getInfo()) band=true;
		else if(E<p->getInfo()){
			ant=p;
			p=p->getHI();
		}
		else{
			ant=p;
			p=p->getHD();
		}
	}

	/*if(band && band1){
		cout<<"\n\n Recorrido: ";
		recorrido.imprimir(false); // true: Imprimir Final-Inicio. false: Imprimir Inicio-Final.
	}*/

	return band;
}

template<class T> NodoA<T>* ArbolBin<T>::buscarEli(T &ele,NodoA<T> *p,NodoA<T> **padre,bool buscEli){
	if(!raiz)
		return NULL;
		if(p->getInfo() == ele){
			ele = p->getInfo();
			return p;
		}
		if(buscEli)
		*padre = p;
		if(p->getHI()){
			NodoA<T> *aux = buscarEli(ele,p->getHI(),padre,buscEli);
			if(aux){
				return aux;
			}

		}
		if(p->getHD()){
			NodoA<T> *aux2 =buscarEli(ele,p->getHD(),padre,buscEli);
			if(aux2){
				return aux2;
			}

		}


	return NULL;
}

template <class T> int ArbolBin<T>::procesarEliminacion(T ele){
	NodoA<T> *pad = NULL;
	NodoA<T> *aux = buscarEli(ele,raiz,&pad,true);
	if(aux){
		return eliminar(aux,pad,false,false);
	}
	else{
		cout<<"no encontrado en el arbol"<<endl;
		return 0;
	}
}

//Nota buscar antes de eliminar para  estar seguro que ya existe
template<class T> int ArbolBin<T>::eliminar(NodoA<T> *p,NodoA<T> *padre,bool prefDer,bool reordenando){
    int r;
	if(!raiz)return 0;
	NodoA<T> *aux,*padAux=p;
	if(p->getHI()==p->getHD())//nodo hoja
    {   if(p == raiz){
			raiz = NULL;
			delete p;
			return 1;
		}
		if(padre->getHI()==p)
			padre->setHI(NULL);
		else
			padre->setHD(NULL);
		delete p;
		return 1;
	}
	if(p->getHI() && !p->getHD()){
		aux = mayor(p->getHI(),&padAux);
		p->setInfo(aux->getInfo());
		r = eliminar(aux,padAux);
	}
	else{
		if(p->getHD() && !p->getHI()){
			aux = menor(p->getHD(),&padAux);

			p->setInfo(aux->getInfo());
			r = eliminar(aux,padAux);
		}
		else{
			if(prefDer){

				aux = menor(p->getHD(),&padAux);
				p->setInfo(aux->getInfo());
				r = eliminar(aux,padAux);
			}
			else{

				aux = mayor(p->getHI(),&padAux);
				p->setInfo(aux->getInfo());
				r = eliminar(aux,padAux);
			}

		}
	}

	if(esAVL && !reordenando){
		do{
			hayDiscordia=false;
			calcularFE(raiz);
			if(hayDiscordia){
				reestructurar(discordia);
			}
		}while(hayDiscordia);
	}
	return r;
}
template<class T> void ArbolBin<T>::imprimir(int tipo){
	if(raiz==NULL) return;

	if(tipo==0) // recorrido pre-orden
		preorden(raiz,0);

	if(tipo==1) // recorrido in-orden
		inorden(raiz,0);

	if(tipo==2) // recorrido post-orden
		postorden(raiz,0);

	if(tipo==3) // recorrido achura
		anchura();

}


template <class T> NodoA<T> *ArbolBin<T>::menor(NodoA<T> *p,NodoA<T> **pad){
	NodoA<T> *q = p;
	while(q->getHI()){
		*pad = q;
		q = q->getHI();
	}
	return q;
}
template <class T>NodoA<T> *ArbolBin<T>::mayor(NodoA<T> *p,NodoA<T> **pad){
	NodoA<T> *q = p;
	while(q->getHD()){
		*pad=q;
		q = q->getHD();
	}
	return q;
}

template<class T> bool ArbolBin<T>::esHoja(NodoA<T> *p){
	return (!p->getHI() && !p->getHD());
}

template<class T> void ArbolBin<T>::preorden(NodoA<T> *p, int niv){

    for (int i(0) ; i < niv ; i++) cout<<"\t";
    cout<<p->getInfo()<<endl;

	if(p->getHI()) preorden(p->getHI(),niv+1);
	if(p->getHD()) preorden(p->getHD(),niv+1);

}

template<class T> void ArbolBin<T>::inorden(NodoA<T> *p, int niv){


	if(p->getHI()) inorden(p->getHI(),niv+1);

	for (int i(0) ; i < niv ; i++) cout<<"\t";
	cout<<p->getInfo()<<endl;

	if(p->getHD()) inorden(p->getHD(),niv+1);

}

template<class T> void ArbolBin<T>::postorden(NodoA<T> *p, int niv){


	if(p->getHI()) postorden(p->getHI(),niv+1);
	if(p->getHD()) postorden(p->getHD(),niv+1);

	for (int i(0) ; i < niv ; i++) cout<<"\t";
	cout<<p->getInfo()<<endl;

}

template<class T> void ArbolBin<T>::anchura(){

	bicola< NodoA<T>*> aux;
	NodoA<T> *p;

	aux.agregar(raiz,true);

	while(!aux.vacia()){

		aux.eliminar(p,false);
		cout<<p->getInfo()<<endl;
		if(p->getHI()) aux.agregar(p->getHI());
		if(p->getHD()) aux.agregar(p->getHD());

	}

}

template <class T> int ArbolBin<T>::altura(NodoA<T> *p){
	int altI=0,altD=0;
	if(p->getHI()==p->getHD())
		return 0;
	if(p->getHI())
		altI = 1+altura(p->getHI());
	if(p->getHD())
		altD = 1+altura(p->getHD());
	if(altI>altD) return altI;
	return altD;
}
template <class T> int ArbolBin<T>::numNodo(NodoA<T> *p) {
    int numI=0,numD=0;
	if(p->getHI()==p->getHD())
		return 0;
	if(p->getHI())
		numI = 1+NumNodo(p->getHI());
	if(p->getHD())
		numD = 1+NumNodo(p->getHD());
	return numD+numI;

}

template <class T> int ArbolBin<T>::factorE(NodoA<T>*p){
	if(p->getHI()==p->getHD())
		return 0;
	if(p->getHI() && p->getHD())
		return (altura(p->getHD())+1)-(altura(p->getHI())+1);
	if(p->getHI())
		return -(altura(p->getHI())+1);
	if(p->getHD())
		return (altura(p->getHD())+1);
}

template <class T> void ArbolBin<T>::calcularFE(NodoA<T> *p){
	if(!p)return;
	p->setFE(factorE(p));
	if(p->getFE()<-1 || p->getFE()>1){
		discordia = p;
		hayDiscordia = true;
		//cout<<endl<<"si hay discordia"<<endl;
	}
	calcularFE(p->getHI());
	calcularFE(p->getHD());
}

template <class T> void ArbolBin<T>::reestructurar(NodoA<T> *p){
	T ele = p->getInfo();
	if(p->getFE()<=-2){
		eliminar(p,NULL,false,true);
	}
	else{
		eliminar(p,NULL,true,true);
	}
	agregar(ele);
}

#endif
