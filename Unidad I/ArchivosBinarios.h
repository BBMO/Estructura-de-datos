#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>

/**
*
*   @autor Brayan Montañez
*   @repo https://github.com/BBMO
*   @modificaciones  Yorman Galindo
*   @Guias Kevin Sanchez
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
      int posicionar_l( int p );
      int tamano();
      void imprimir();
      int busquedaSecuencial( T &bus, int pos=0, int Max=99999999 );//Puede modificarse a bool
      T getBuffer(){ return buffer;}
		//Mezcla directa
	 	void mezclaDirecta();
	  void escribirArchivoAux(int j,int i,ArchivosBinarios &aux);
	  int getN();
	  int get_lon(){return lon;}
	  bool comparar(ArchivosBinarios &aux1,int pos1,ArchivosBinarios &aux2,int pos2);
	  void escribirNuevo(ArchivosBinarios &aux,int posAux);
      //Debe tener el archivo ordenado para poder usarlo
      int busquedaBinaria ( T &bus );//Puede modificarse a bool
      int busquedaBloques( T &bus ,int n);
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
    while ( true ){
      leer(buffer);
      if ( esFin() ) break;
      cout<<++cont<<")->"<<buffer<<endl;
    }
    cout<<endl;
}

template <class T>int ArchivosBinarios<T>::busquedaSecuencial( T &bus, int pos, int Max ){
     int i=-1;
     pos=0;
     //bool enc= false
     int enc=0;
     limpiar();
     posicionar(pos);

     while (i<=Max){
       leer(buffer);
       if ( esFin() ) break;
       if ( bus.get_clave()==buffer.get_clave() ){
           if(i==-1) i=0;
           enc=i;
           bus= buffer;
           break;
       }
	   else i++;
     } // fin while
     return enc;
}

//Hay que ordenar el archivo primero para poder usarse
template <class T> int ArchivosBinarios<T>::busquedaBinaria( T &bus ){
     //bool enc=false;
     int enc=-1;
     int li=0, ls=tamano()-1, pm;
     limpiar();
     while (li<=ls){
           pm= (li+ls)/2;
           posicionar(pm);
           leer(buffer);
           if ( bus.get_clave()==buffer.get_clave() ){
                enc=pm;
                bus=buffer;
                break;
           }
           else if ( bus.get_clave()< buffer.get_clave() )
                ls= pm-1;
           else
                li= pm+1;
     }
     return enc;
}

template <class T> int ArchivosBinarios<T>::busquedaBloques(T &bus,int n){
	int i,enc=-1,tamblo=sqrt(n);
	for(i=tamblo-1;i<n && enc==-1;i+=tamblo){

		posicionar(i);
		leer(buffer);
			if(bus.get_clave()<=buffer.get_clave()){
				for(int j=i;j>i-tamblo-1 && enc==-1;j--){
					posicionar(j);
					leer(buffer);
					if(bus.get_clave()==buffer.get_clave()){

			        enc=j;
			        bus=buffer;
			        return enc;
	              }
				}
			}

	}
	if(enc==-1)
	if(n%tamblo!=0){

		for(i=tamblo*tamblo;i<=n && enc==-1;i++){
		posicionar(i);
		leer(buffer);
	      if(bus.get_clave()==buffer.get_clave()){
			enc=i;
			bus=buffer;
			return enc;
		   }
		}
	}
	return enc;
}
//Mezcla directa
template <class T> void ArchivosBinarios<T>::mezclaDirecta(){

	ArchivosBinarios aux1("aux1.dat");
	ArchivosBinarios aux2("aux2.dat");

    int ind1,ind2,indNuevo,cont=0;
    tamano();
   	for(int i=1;i<N;i*=2){
   	 	indNuevo=0;
   	aux1.abrir(ios::out | ios::binary);
	if(aux1.falla()){
		cout<<"fallo";

		exit(0);
	}
	aux1.cerrar();
	 aux2.abrir(ios::out | ios::binary);
	if(aux2.falla()){
		cout<<"fallo";

		exit(0);
	}
	aux2.cerrar();
		for(int j=0;j<N;j+=i){
        	escribirArchivoAux(j,i,aux1);
			j+=i;
			if(j<N){
				escribirArchivoAux(j,i,aux2);
			}
	   }

		ind1=0;ind2=0;

		aux1.limpiar();
 	    aux1.abrir( ios::in | ios::binary);
	    if(aux1.falla()){
		    cout<<"fallo";
	       	exit(0);
	    }
	    aux1.tamano();
	    aux1.cerrar();
	    aux2.limpiar();
 		aux2.abrir( ios::in | ios::binary);
	    if(aux2.falla()){
			cout<<"fallo";
	       	exit(0);
	    }
	    aux2.tamano();
	   	aux2.cerrar();


	        posicionar(0);
	          int j=1;


		    while(ind1<aux1.getN() || ind2<aux2.getN() ){

		      	if(ind1<(j*i) && ind2<(j*i) && ind1<aux1.getN() && ind2<aux2.getN()){


	   	      	 if(comparar(aux1,ind1,aux2,ind2)){
	   	      	 	 escribirNuevo(aux1,ind1);
	   	      	     ind1++;
				}
				else{

					escribirNuevo(aux2,ind2);
				     ind2++;

				}
			  }
			  else{
				if(ind1<(j*i) && ind1<aux1.getN()){

					escribirNuevo(aux1,ind1);
				    ind1++;
				    if(ind1==(j*i)){
				    	j++;

					}
				}
				else{
					if(ind2<(j*i) && ind2<aux2.getN() ){

					escribirNuevo(aux2,ind2);
					ind2++;
					if(ind2==(j*i)){
				    	j++;

					}

	              }
				}
			  }
	      }

	  cont++;
	  cerrar();

	  abrir(ios::in | ios::out | ios::binary);
	   if(falla()){
		cout<<"Error al abrir el archivo "<<endl;

		exit(0);
	   }
	}
}

template <class T> void ArchivosBinarios<T>::escribirNuevo(ArchivosBinarios &aux,int posAux){

	 T buffer1;
	 aux.limpiar();
 	 aux.abrir( ios::in | ios::binary);
	 if(aux.falla()){
		cout<<"fallo";
		exit(0);
	}
	 aux.falla();
	 aux.posicionar(posAux);
	 aux.leer(buffer1);
     escribir(buffer1);
    aux.cerrar();
}

template <class T> bool ArchivosBinarios<T>::comparar(ArchivosBinarios &aux1,int pos1,ArchivosBinarios &aux2,int pos2){
    T buffer1,buffer2;
    aux1.limpiar();
    aux2.limpiar();
	aux1.abrir( ios::in | ios::binary);
	aux2.abrir( ios::in | ios::binary);
	if(aux1.falla() || aux2.falla()){
		cout<<"fallo";
		exit(0);
	}
	aux1.get_lon();
	aux2.get_lon();
	aux1.posicionar(pos1);
	aux2.posicionar(pos2);
	aux1.leer(buffer1);
	aux2.leer(buffer2);

	if(buffer1.get_clave()<buffer2.get_clave()){//Depende del objeto a ordenar, en este caso es por cedula
	    aux1.cerrar();
		aux2.cerrar();
		return true;
	}

	aux1.cerrar();
	aux2.cerrar();
	return false;
}

template <class T> int ArchivosBinarios<T>::getN(){
	return N;
}

template <class T> void ArchivosBinarios<T>::escribirArchivoAux(int j,int i,ArchivosBinarios &aux){
	T buffer1;

	 aux.limpiar();

 	aux.abrir( ios::in | ios::out | ios::app | ios::binary);
	if(aux.falla()){
		cout<<"fallo";

		exit(0);
	}

	for(int k=j;k<(j+i) && k<N;k++){
		posicionar(k);
			leer(buffer1);
		    aux.escribir(buffer1);

    }
	aux.cerrar();
}
