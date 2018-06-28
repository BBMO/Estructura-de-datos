#ifndef TEMPLATESORDENAMIENTO_H_INCLUDED
#define TEMPLATESORDENAMIENTO_H_INCLUDED

#define sufpeq 5
/***********************************************/
/*************** Métodos externos **************/
/***********************************************/

template <class T> void intercambio(T &a, T &b){
    T aux = a;
    a = b;
    b = aux;
}

/***********************************************/
/***********************************************/


/***********************************************/
/************* Métodos de Ordenación ***********/
/***********************************************/
//asc_desc = 0 ascendente
//asc_desc !=0 descendente

template <class T> void burbuja(T v[], int n, int asc_desc = 0){
    for(int j=1; j<n; j++){
        for(int i=0; i<n-j; i++){
            if(asc_desc == 0){
                if(v[i] > v[i+1]) intercambio(v[i], v[i+1]);
            }
            else{
                if(v[i] < v[i+1]) intercambio(v[i], v[i+1]);
            }
        }
    }
}

template <class T> void burbujaOP(T v[], int n, int asc_desc = 0){
    bool band = true;
    for(int j=1; j<n && band; j++){
        band = false;
        for(int i=0; i<n-j; i++){
            if(asc_desc == 0){
                if(v[i] > v[i+1]) intercambio(v[i], v[i+1]);
                band = true;
            }
            else{
                if(v[i] < v[i+1]) intercambio(v[i], v[i+1]);
                band = true;
            }
        }
    }
}

template <class T> void shakerSort(T v[], int n, int asc_desc = 0){
    int limiteS = n-1, limiteI = 0;
    bool band = true;

    while(limiteI <= limiteS && band){
        band = false;

        for(int i=limiteI; i<limiteS; i++){
            if(asc_desc == 0){
                if(v[i] > v[i+1]) intercambio(v[i], v[i+1]);
                band = true;
            }
            else{
                if(v[i] < v[i+1]) intercambio(v[i], v[i+1]);
                band = true;
            }
        }

        limiteS--;

        for(int i=limiteS; i>limiteI; i--){
            if(asc_desc == 0){
                if(v[i] < v[i-1]) intercambio(v[i], v[i-1]);
                band = true;
            }
            else{
                if(v[i] > v[i-1]) intercambio(v[i], v[i-1]);
                band = true;
            }
        }

        limiteI++;

    }

}

template <class T> void seleccionDirecta(T v[], int n, int asc_desc = 0){
    int posmen, i, j;
    T men;
    for(j=1; j<n; j++){
        men = v[j-1];
        posmen = j-1;
        for(i=j; i<n; i++){
            if(asc_desc == 0){
                if(v[i] < men){
                    men = v[i];
                    posmen = i;
                }
            }
            else{
                if(v[i] > men){
                    men = v[i];
                    posmen = i;
                }
            }
        }
        if(posmen != j-1)
            intercambio(v[posmen], v[j-1]);
    }
}

template <class T> void seleccionDirectaAdaptadoPractica(T v[], int n, T vaux[], int asc_desc = 0){
    int posmen, i, j;
    T men;
    for(j=1; j<n; j++){
        men = v[j-1];
        posmen = j-1;
        for(i=j; i<n; i++){
            if(asc_desc == 0){
                if(v[i] < men){
                    men = v[i];
                    posmen = i;
                }
            }
            else{
                if(v[i] > men){
                    men = v[i];
                    posmen = i;
                }
            }
        }
        if(posmen != j-1){
            intercambio(v[posmen], v[j-1]);
            intercambio(vaux[posmen], vaux[j-1]);
        }
    }
}

template <class T> void sellSort(T v[], int n){
	int paso = n/2, i;
	bool band = true;
	while(paso != 0){
		do{
			band = false;
			for(i=0; i + paso < n; i++){
				if(v[i] > v[i+paso]){
					intercambio(v[i], v[i+paso]);
					band=true;
				}
			}
		}while(band);
		paso /= 2;
	}
}

/************ MERGE SORT ***********/

template <class T> void partir(T v[], T *x1, T *x2, int n){
	int i;
	for(i=0; i<n/2; i++)
		x1[i]=v[i];
	for(; i<n; i++)
		x2[i-(n/2)]=v[i];
}
template <class T> void mezclar(T *v, T *x1, T *x2, int n, int asc_desc = 0){
	int i=0, j=0, k=0;
	for(; k<n; k++){
		if(i==n/2 && j<n-n/2){
			v[k]=x2[j];
			j++;
		}
		else if(j==n-n/2 && i<n/2){
			v[k]=x1[i];
			i++;
		}
        else{
            if(asc_desc==0){
                if(x1[i] < x2[j]){
                    v[k]=x1[i]; i++;
                }
                else{
                    v[k]=x2[j]; j++;
                }
            }
            else{
                if(x1[i] > x2[j]){
                    v[k]=x1[i]; i++;
                }
                else{
                    v[k]=x2[j]; j++;
                }
            }
        }
	}
}
template <class T> void mergeSort(T v[], int n, int asc_desc = 0){
    if(n <= sufpeq) {
		burbuja(v,n, asc_desc);
	}
	else {
		int *x1,*x2;
		x1 = new int[n/2];
		x2 = new int[n-(n/2)];

		partir(v,x1,x2,n);

		mergeSort(x1,n/2, asc_desc);
		mergeSort(x2,n-(n/2), asc_desc);

		mezclar(v,x1,x2,n, asc_desc);
	}
}

/************* QUICK SORT **********/
template <class T> void quickSort(T v[], int primero, int ultimo, int asc_desc = 0){

    int i = primero, j = ultimo, central = (primero+ultimo)/2;
    T pivote = v[central];

    do{
        if(asc_desc == 0){
            while(v[i] < pivote) i++;
            while(v[j] > pivote) j--;
        } else{
            while(v[i] > pivote) i++;
            while(v[j] < pivote) j--;
        }


        if(i <= j){
            intercambio(v[i], v[j]);
            i++;
            j--;
        }

    }while( i<=j );

    if(primero < j) quickSort(v, primero, j, asc_desc);
    if(ultimo > i) quickSort(v, i, ultimo, asc_desc);

}

/***********************************************/
/***********************************************/

#endif // TEMPLATESORDENAMIENTO_H_INCLUDED
