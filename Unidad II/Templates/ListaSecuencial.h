/**
* @autor Brayan Montañez
**/
//Secuencial Simple
using namespace std;

template <class T>
class ListaVec{
		T *v;
		int tam, cab,lib;
	public:
		ListaVec(int s);
		int agregar(T E);
		int eliminar(T &E);
		void imprimir();
		T getCabecera(){return v[cab];}
		bool vacia(){return lib==0;}//lib==0
		bool llena(){return lib==tam;}
};

template <class T> ListaVec<T>::ListaVec(int s){
	tam=s;
	cab=0; lib=0;
	v = new T[tam];
	if(!v) cout<<"Falta Memoria\n";
}

template <class T> int ListaVec<T>::agregar(T E){
	if(!v) return -1;
	if(llena()) return 0;
	int i=lib-1;

	while(i>=cab && E<v[i]){
		v[i+1]=v[i--];
	}
	v[++i]=E;
	lib++;
	return 1;
}

template <class T> int ListaVec<T>::eliminar(T &E){
	if(!v) return -1;
	if(vacia()) return 0;
	int i;
	for(i=cab; i<lib && v[i]!=E; i++);

	if(i==lib) return 404; //No encontrado
	for(; i<(lib-1); i++)
		v[i] = v[i+1];

	lib--;
	return 1;
}

template <class T> void ListaVec<T>::imprimir(){
	for(int i=cab; i<lib; i++)
		cout<<v[i]<<endl;
}

