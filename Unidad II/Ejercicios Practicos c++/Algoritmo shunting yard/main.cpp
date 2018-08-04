#include <iostream>
#include <string.h>
#include <conio.h>

/**
	@autor Brayan Montañez
	@title Practica Colas y Pilas (Estructura de datos)
**/


using namespace std;
#include "Colas.h"
#include "Pila.h"
#include "token.h"
//Variables globales
int n, nCola;

//Transformo cada caracter de la expresion en un objeto tipo Token
void exportarATokens(string expr, Token  vectorTokens[]) {
	 n = expr.length(); nCola=n;
    for(int i=0; i<expr.length(); i++) {
        if(isdigit(expr[i])) {
    		vectorTokens[i]=Token(1, expr[i]);
        } else {
        	int tipo = 0;
            int pr = -1;           // precedencia
            bool ad = false;        // asociacionDerecha
            switch(expr[i]) {
	            case '(':   tipo = 3;     nCola--;  break;
	            case ')':   tipo = 4;     nCola--;  break;
	            case '^':   tipo = 2;     pr = 4; ad = true;  break;
	            case '*':   tipo = 2;     pr = 3; break;
	            case '/':   tipo = 2;     pr = 3; break;
	            case '+':   tipo = 2;     pr = 2; break;
	            case '-':   tipo = 2;     pr = 2; break;
	            default:{
	            	cout<<"Hay caracteres no permitidos el programa se cerrara, gracias"<<endl;
	            	exit(0);
					break;
				}
            }
            vectorTokens[i]=Token(tipo, expr[i], pr, ad);
        }
    }

}

void shuntingYard(Token vectorTokens[]) {
	Token t(0, ' ');
    Cola<Token> colaSalida(nCola);
    Pila<Token> pilaOperadores(n, t);

    // While there are tokens to be read:
    for(int i=0; i<n; i++) {
        // Read a token
        switch(vectorTokens[i].getTipo()) {
	        case 1:{
	        	// Si el token es un numero, etonces lo agrego a la cola de salida
	            colaSalida.agregar(vectorTokens[i]);
				break;
			}
	            
	        case 2:{
	                // Si el token es un operador o1, entonces:
	                Token o1 = vectorTokens[i];
	
	                // mientras haya un operador token,            
	                int x=pilaOperadores.getTope(), a=1;
	                while(x!=-1 && pilaOperadores.getTope() != -1) {
	                	Token o2;
	                	a=pilaOperadores.Eliminar(o2);
	                	
	                    if(! o1.getAsociativoDerecha() && o1.getPrecedencia() <= o2.getPrecedencia()
	                    	||  (  o1.getAsociativoDerecha() && o1.getPrecedencia() <  o2.getPrecedencia())) {                      
	                        colaSalida.agregar(o2);
	                    }else{  	
	                        if(o2.getTipo() != 3) pilaOperadores.Agregar(o2);
	                        break; 
						}
						       
	                }
					
	                // agrego o1 a la pila de operadores
	                pilaOperadores.Agregar(o1);
	            break;
	        }
	        	
	        case 3:{
	        	pilaOperadores.Agregar(vectorTokens[i]);
	         	break;
	        }
	         
			case 4:{				
				int x=pilaOperadores.getTope();
	            while(x!=-1) {	            	
                    Token to;
                    x = pilaOperadores.Eliminar(to);                 
                    if(to.getTipo() != 3) colaSalida.agregar(to);
                    break;
                }
				break;
			}   
    	}
	}
    
    //Agrego lo que quedó de la pila a la cola
    Token o2; bool ultimo;
    while(pilaOperadores.Eliminar(o2)){
	    colaSalida.agregar(o2);
	    ultimo=true;
	}
	if(ultimo) colaSalida.agregar(o2);
	cout<<"\nAlgoritmo aplicado: "<<endl;
    colaSalida.imprimir(); //IMPRIMIENDO COLA
    cout<<"\nCompletado presione una tecla para volver...."<<endl; getch();
}

int main(){
	
	string pruebas[5] = {"3 + 4 * 2 / (1 - 5) ^ 2 ^ 3 ",
					  "( (2 * 7 * 8) / 2 ) ^ 5 ",
					  "3 + 4 * (2 - 1) ",
					  "(2 * 7 * 8 * 4 / 2) ", 
					  "3 ^ 2 ^ (5 - 1) / 2 * 4 + 3 "};
	string exprf="", expresion;
	
	//Corriendo versiones de prueba
	/*for(int j=0; j<5; j++){
		exprf="";
		for(int i=0; i<pruebas[j].length(); i++)
			if(pruebas[j][i] != ' ') exprf += pruebas[j][i];
		
		Token vectorTokens[exprf.length()];
		exportarATokens(exprf, &vectorTokens[0]);
		shuntingYard(&vectorTokens[0]);
	}*/
	int opcion;
	do{
		system("cls");
		cin.sync();
		cout<<"[1]-> Usar"<<endl;
		cout<<"[0]-> Salir"<<endl;
		cout<<"	Entrada: ";cin>>opcion;
		cin.sync();
		
		if(opcion==1){
			cout<<"\nIntroduce la expresion a procesar: ";
			getline(cin, expresion);
			exprf="";
			
				for(int i=0; i<expresion.length(); i++)
					if(expresion[i] != ' ') exprf += expresion[i];
					
			Token vectorTokens[exprf.length()];
			exportarATokens(exprf, &vectorTokens[0]);
			shuntingYard(&vectorTokens[0]);
		}
		
	}while(opcion != 0);
	
	
	return 0;
}
