#include <stdlib.h>
#include <stdio.h>

#define dimN 16
#define dimM  8

//la macro CHECK_PTR_EXIT controlla se il puntatore è null, in tal caso stampa la stringa str e termina il programma
#define CHECK_PTR_EXIT(X, str)  \
    if(X==NULL){                \
        perror(#str);           \
        exit(EXIT_FAILURE);     \
    } 

//la macro ELEM ritorna l'elemento nella posizione i,j della matrice M
#define ELEM(M, i, j) M[(i*dimM)+j] 

//la macro PRINTMAT stampa gli elementi della matrice M
#define PRINTMAT(M, righe, colonne)             \
    for(int i=0; i<righe; i++){                 \
        for(int j=0; j<colonne; j++){           \
            printf("%4ld ", ELEM(M, i, j));     \
        }                                       \
        printf("\n");                           \
    }

int main() {
    long *M = malloc(dimN*dimM*sizeof(long));
    CHECK_PTR_EXIT(M, "malloc"); 
    for(size_t i=0;i<dimN;++i)
	for(size_t j=0;j<dimM;++j)			
	    ELEM(M,i,j) = i+j;    
    
    PRINTMAT(M, dimN, dimM);
    free(M);
    return 0;
}