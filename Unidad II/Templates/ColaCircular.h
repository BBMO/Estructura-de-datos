/**
* @autor Brayan Montañez
**/
/*
	Formula de sigueiente posicion:
		i = (i + 1) % tam
*/

using namespace std;
template<class T>
class ColaCircular {
		int tam, fre, fin;
		T *v;
	public:
		ColaCircular(int size);
		bool vacia(){ return fre==-1; };
		bool lleno(){ return ((fin+1)%tam == fre);}
		int agregar(T E);
		int eliminar(T &E);
		int imprimir();
		T getFrente(){ return this->v[fre]; }
        T getFin(){  if(!vacia()) return this->v[fin]; }
};


template <class T> ColaCircular <T>::ColaCircular(int size){
	tam = size;
	fre = fin = -1;
	v = new T[size];
	if( v == NULL) cout << "Se agoto memoria" << endl;
}

template <class T> int ColaCircular <T>::agregar(T E){
	if(!v) return -1;
	if(lleno()) return 0;
	if(fre==-1) fre=0;
	fin=(fin+1)%tam;
	v[fin] = E;
	return 1;
}

template <class T> int ColaCircular <T>::eliminar(T &E){

	if( v == NULL ) return -1;
	if(vacia()) return 0;

	E = v[fre];

	if(fre == fin) fre=fin=-1;
	else fre=(fre+1)%tam;

	return 1;
}

template <class T> int ColaCircular<T>::imprimir(){

	if( v == NULL ) return -1;
	if(vacia()) return 0;
	int i=fre, j=fin;
	bool band = true;
    while ( band ) {
        if(i==j) band = false;
        cout << endl << v[i];
        i = (i + 1) % tam;
    }
    return 1;
}
