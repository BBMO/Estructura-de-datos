#ifndef NODOA_H
#define NODOA_H

template <class T>
class NodoA{
        T info;
        NodoA<T> *HI,*HD;
        int FE;
	public:
		NodoA(T ele){info = ele; HI = HD= NULL;}
		NodoA(){HI = HD = NULL;}
		void setHI(NodoA<T> *p){HI = p;}
		void setHD(NodoA<T> *p){HD=p;}
		void setInfo(T e){info=e;}
		void setFE(int f){ FE = f;}
		int getFE(){return FE;}
		NodoA<T> *getHI(){return HI;}
		NodoA<T> *getHD(){return HD;}
		T getInfo(){return info;}
};

#endif
