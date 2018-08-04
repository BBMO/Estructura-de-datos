
using namespace std;

template <class T>

class Cola {
	
	private:
	
		int size, fre, fin;
		T *v;	
		
	public:
	
		Cola(){}
		Cola(int size);
		int agregar(T E);
		int eliminar(T &E);
		void imprimir();
		bool vacia(){ return this->fin== -1; };
		bool lleno(){ return this->fin == this->size-1; }
		T getFrente(){ return this->v[0]; }
		T getFin(){  if(!vacia()) return this->v[fin]; }		
		int getSize(){return size;}
	
	
};

template <class T>
Cola <T>::Cola(int size){

	this->size = size;
	this->fre = 0;
	this->fin = -1;
	this->v = new T[size];
	
	if( v == NULL) cout << "Se agoto memoria" << endl; 	
	
}

template <class T>
int Cola <T>::agregar(T E){
	
	if( v == NULL) return -1;
	if( lleno() ) return 0;
	v[fin+1] = E; fin++; return 1;
	
}

template <class T>
int Cola <T>::eliminar(T &E){
	
	if( v == NULL ) return -1;
	if(vacia()) return 0;
	E = v[fre];
	for(int i = 0; i < fin; i++) v[i] = v[i+1];
	fin--;
	return 1;
	
}

template <class T>
void Cola<T>::imprimir(){

	for(int i=fre; i <= fin; i++){
		cout << v[i];
	}
	cout<<endl;
	
}

