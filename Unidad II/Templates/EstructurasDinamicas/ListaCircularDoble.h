#include "Nodo.h"

template <class T>
class ListaCircDob{
	Nodo<T> *cab, *p;
	
	public:
		/*TRAZLADAR LAS FUNCIONES FUERA DE LA DECLARACION DE LA CLASE*/
		ListaCircDob();
		Nodo<T>*getCab(){ return cab; }
		Nodo<T>*getVisit(){ return p; }
		void reset();
		void mover(int pasos=1, bool band=true);
		T getInfoVisit();
		int agregar(T E);
		int eliminar(T &E);
		void imprimir(bool band=true);
};

template<class T> ListaCircDob<T>::ListaCircDob(){ cab=p=NULL; }

template<class T> void ListaCircDob<T>::reset(){ p=cab; }

template<class T> void ListaCircDob<T>::mover(int pasos, bool band){
	for(int i=0; i<pasos; i++){
		(band)? p=p->getSig() : p=p->getAnt();
	}
}

template<class T> T ListaCircDob<T>::getInfoVisit(){ return p->getInfo(); }

template<class T> void ListaCircDob<T>::imprimir(bool band){
	reset();
	if(cab == NULL) return;
	if(!band) p=cab->getAnt();
	do{
		cout<<" "<<getInfoVisit()<<" ";	
		band? mover(): mover(1, false);
	}while(band? p!=cab:p!=cab->getAnt());
}

template<class T> int ListaCircDob<T>::agregar(T E){
	Nodo<T> *nue=new Nodo<T>(E);
	if(!nue) return 0;

	if(cab==NULL){
		cab=nue; nue->setSig(nue);
		nue->setAnt(nue);
	}else{
		reset();
		do{
			if(E<getInfoVisit()){
				break;
			}else{
				mover();
			}
		}while(p!=cab);
		nue->setSig(p);
		nue->setAnt(p->getAnt());
		p->getAnt()->setSig(nue);
		p->setAnt(nue);

		if(E<cab->getInfo()) cab=nue;
	}
	return 1;
}

template<class T> int ListaCircDob<T>::eliminar(T &E){

	bool band = false;
	if(cab==NULL) return 0;
	if(E<cab->getInfo() || E>cab->getAnt()->getInfo()) return -1;
	
	reset();	
	
	do{
		if(E==getInfoVisit()) band=true;
		else mover();
	}while(!band && p!=cab);
	
	if(!band) return -1;
	E=getInfoVisit();
	
	if(p->getAnt()==p && p->getSig()==p) cab=NULL;
	else{
		p->getAnt()->setSig(p->getSig());
		p->getSig()->setAnt(p->getAnt());
		if(p==cab) cab=p->getSig();
	}
	delete p;
	return 1;
}






















