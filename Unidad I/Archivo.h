/**
*   @autor Brayan Montañez
**/
using namespace std;

template<class T>
class Archivo{

		char nom[40];
		T buffer;//Para implementacion en otra clase
		fstream obj;
	public:
		Archivo(){}
		Archivo(char *c){strcpy(nom, c);}

		/**** Archivos .txt ****/
		void crear();
		bool abrirModoLectura();
		bool abrirModoEscritura();
		void cerrar();
		void escribir(string datos, bool finLinea = false);
		void leer(char cad[]);
		void leerCampo(char cad[], char delimitador);
		bool esFin();
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

//Crear nuevo archivo
template<class T> void Archivo<T>::crear(){
    this->obj.open(nom, ios::out);
}

//Abrir archivo para leer datos
template<class T> bool Archivo<T>::abrirModoLectura(){
    this->obj.open(nom, ios::in);
    return !this->obj.fail();
}

//Abrir archivo para escribir datos
template<class T> bool Archivo<T>::abrirModoEscritura(){
    obj.open(nom, ios::app);
    return !this->obj.fail();
}

//Cerrar archivo
template<class T> void Archivo<T>::cerrar(){
    this->obj.close();
}

//Escribir datos en el archivo
template<class T> void Archivo<T>::escribir(string datos, bool finLinea){
    obj << datos;
    if(finLinea) obj<<endl;
}

//Lee linea completa hasta un salto de linea
template<class T> void Archivo<T>::leer(char cad[]){
    this->obj.getline(cad, 180,'\n');
}

//Lee hasta el caracter limitador enviado
template<class T> void Archivo<T>::leerCampo(char cad[], char delimitador){
    this->obj.getline(cad, 180, delimitador);
}

template<class T> bool Archivo<T>::esFin(){
    return obj.eof();
}

/*************************/
/*************************/
































