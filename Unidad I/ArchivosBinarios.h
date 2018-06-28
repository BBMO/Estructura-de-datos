#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

/**
*
*   @autor Brayan Montañez
*   @repo https://github.com/BBMO
*
**/

using namespace std;

template <class T>
class ArchivosBinarios{
      fstream pf;
      char nom[40];
      T buffer;
      int lon, N;
  public:
      ArchivosBinarios( ){}
      ArchivosBinarios(char *n){ strcpy(nom,n);  }
      void abrir( const std::_Ios_Openmode &t );
      void leer( T &b );
      void escribir( T &b );
      void cerrar();
      bool esFin();
      bool falla();
      void limpiar();
      void posicionar( int p );
      int tamano();
      void imprimir();
      int busquedaSecuencial     ( T &bus, int pos=0, int Max=99999999 );


      //EN DESARROLLO
      bool busquedaBinaria ( T &bus );
      T getBuffer(){ return buffer;}
};

template <class T> void ArchivosBinarios<T>::abrir( const std::_Ios_Openmode &t ){
    pf.open(nom,t);
}

template <class T> void ArchivosBinarios<T>::leer( T &b ){
    pf.read ((char*)&b,sizeof(T));
}

template <class T> void ArchivosBinarios<T>::escribir( T &b ){
    pf.write((char*)&b,sizeof(T));
}

template <class T> void ArchivosBinarios<T>::cerrar(){
    pf.close();
}

template <class T> bool ArchivosBinarios<T>::esFin(){
    return pf.eof();
}

template <class T> bool ArchivosBinarios<T>::falla(){
    return pf.fail();
}

template <class T> void ArchivosBinarios<T>::limpiar(){
    pf.clear();
}

template <class T> void ArchivosBinarios<T>::posicionar( int p ){
    pf.seekg(p*lon, ios::beg );
}

template <class T> int ArchivosBinarios<T>::tamano(){
     lon= sizeof(T);
     pf.seekg(0,ios::end);
     pf.clear();
     N= pf.tellg()/lon;

     return N;
}

template <class T> void ArchivosBinarios<T>::imprimir(){
    int cont=0;
    limpiar();
    posicionar(0);
    while ( true )
    {
      leer(buffer);
      if ( esFin() ) break;
      cout<<"["<<++cont<<"]"<<buffer<<endl;
    }
    cout<<endl;
}

template <class T>int ArchivosBinarios<T>::busquedaSecuencial( T &bus, int pos, int Max ){
     int i=0;
     int enc=0;
     limpiar();
     posicionar(pos);

     while (i<=Max){
       leer(buffer);
       if ( esFin() ) break;
       if ( bus.get_clave()==buffer.get_clave() ){
           enc=i;
           bus= buffer;
           break;
       }
	   else i++;
     } // fin while
     return enc;
}

//Hay que ordenar el archivo primero, EN DESARROLLO NO USAR
template <class T> bool ArchivosBinarios<T>::busquedaBinaria( T &bus ){
     //bool enc=false;
     bool enc=false;
     int li=0, ls=tamano()-1, pm;
     limpiar();
     while ( !enc && li<=ls )
     {
           pm= (li+ls)/2;
           posicionar(pm);
           leer(buffer);
           if ( bus.get_clave()==buffer.get_clave() )
           {
                enc=true;
                bus=buffer;
           }
           else if ( bus.get_clave()< buffer.get_clave() )
                ls= pm-1;
           else
                li= pm+1;
     }
     return enc;
}

