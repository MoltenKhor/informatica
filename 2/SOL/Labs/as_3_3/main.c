#include <stdio.h>
#include <stdlib.h>

#define dimN 16 
#define dimM 8

#define CHECK_PTR(X, str)	\
    if ((X)==NULL) {		\
	perror(#str);		    \
	exit(EXIT_FAILURE);	    \
    }

#define ELEM(Mat, i, j) (Mat[(i*dimM)+j])

#define PRINTMAT(MAT)                               \
    do {                                            \
        printf("Stampo la matriche %s:\n", #MAT);   \
        for(size_t i=0; i<dimN; i++){               \
            for(size_t j=0; j<dimM; j++){           \
                printf("%4ld ", ELEM(MAT, i, j));   \
            }                                       \
            printf("\n");                           \
        }                                           \
    }while(0);                                     

int main(){
    long *M = malloc(dimN*dimM*sizeof(long));
    CHECK_PTR(M, "malloc");
    for(size_t i=0; i<dimN; i++){
        for(size_t j=0; j<dimM; j++){
            ELEM(M,i,j) = i+j;
        }
    }
    PRINTMAT(M);
    free(M);
    return 0;
}