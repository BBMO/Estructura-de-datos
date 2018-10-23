template <class T>
class Nodo
{
      T info;
      Nodo<T> *ant, *sig;
    public:
        Nodo(T E)                  { info=E; ant=sig=NULL; }
        void  setInfo( T val )     { info=val; }
        void  setAnt( Nodo<T> *p ) { ant= p;   }
        void  setSig( Nodo<T> *p ) { sig= p;   }
        T getInfo()        		   { return info; }
        Nodo<T> *getSig() 		   { return sig;  }
        Nodo<T> *getAnt()          { return ant;  }                          
};
