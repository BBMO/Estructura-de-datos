/*
 tipos (significado)
 	0 desconocido
 	1 numero
 	2 operador
 	3 parentesis izquierdo
 	4 parentesis derecho
*/
class Token {
	int tipo;
    int precedencia;
    bool asociativoDerecha;
    char str;
public:
	Token(){};
    Token(int t, char s, int prec = -1, bool ad = false);
    int getTipo(){return tipo;}
    bool getAsociativoDerecha(){return asociativoDerecha;}
    int getPrecedencia(){return precedencia;}
    
    friend ostream & operator<<(ostream &os, Token c){
		os<<" "<<c.str;
		return os;
	}
};

Token::Token(int t, char s, int prec, bool ad){
	tipo=t; str=s; precedencia=prec; asociativoDerecha=ad;
}
