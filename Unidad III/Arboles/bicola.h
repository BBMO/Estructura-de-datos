

using namespace std;
template <class T>
class bicola{

	Nodo<T> *izq,*der;

	public:

	bicola() {	izq=der=NULL;}
	int agregar(T E, bool band=true);
	int eliminar(T &E, bool band=true);
	void imprimir(bool band=true);
	void imprimir_data(bool band);
	bool vacia() {return izq==NULL;}

};

template <class T> void bicola<T>::imprimir_data(bool band){

	Nodo<T> *p=izq;
	if(!band) p= der;


		cout << "\n\n\n ITINERARIO DE VUELOS ";

		while(p){

			cout << "\n\n Codigo de la Aeronave: " << p->getInfo().get_id();
			cout << "\n Puntos Por donde Pasa: "; p->getInfo().imprimir();
			cout << "\n Distancia Minima Recorrida: " << p->getInfo().get_dis();

			if(band) p = p->getSig();
			else p = p->getAnt();

		}


}

template <class T> int bicola<T>::agregar(T E,bool band){

	Nodo<T> *nue;

	nue = new Nodo<T>(E);

	if(nue == NULL) return 0;

	if(izq==NULL) izq=der=nue;
	else if(band){				//agregar por izquierda

		nue->setSig(izq);
		izq->setAnt(nue);
		izq=nue;

	}else{

		nue->setAnt(der);
		der->setSig(nue);
		der=nue;

	}
}

template <class T> int bicola<T>::eliminar(T &E, bool band){

	Nodo<T> *p;

	if(izq==NULL) return 0;
	if(izq==der){
		p=izq;
		izq=der=NULL;
	}else if(band){		//eliminar por la izquierda

		p=izq;
		izq=izq->getSig();
		izq->setAnt(NULL);

	}else {

		p=der;
		der=der->getAnt();
		der->setSig(NULL);

	}

	E=p->getInfo();
	delete p;
}

template <class T> void bicola<T>::imprimir( bool band){

	Nodo<T> *p=izq;
	if(!band) p= der;

	while(p){

		cout<<" "<<p->getInfo()<<" ";

		if(band) p = p->getSig();
		else p = p->getAnt();

	}
}
