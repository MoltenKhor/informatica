#include <stdio.h>
#include <stdlib.h>

#if !defined(INIT_VALUE)
#error("init not declared\n");
#endif
//versione non rientrante, utilizza una variabile static al suo interno 
int somma(int val){
    static int s = INIT_VALUE;      
    s += val;
    return s;
}
//versione rientrante
int somma_r(int val, int *s){
    *s += val;
    return *s;
}

int main(int argc, char* argv[]){

    if(argc != 2){
        printf("errore argomenti\n");
        return -1;
    }
    int N = strtol(argv[1], NULL, 10);
    int s = INIT_VALUE;                                     //per la versione rientrate utilizzo una variabile statica, non globale

    for(int i=0; i<N; i++){
        int val;
        fprintf(stdout, "inserisci un numero, %d mancanti", N-i);
        if(fscanf(stdin, "%d", &val)!=1){
            perror("fscanf");
            return -1;
        }

        fprintf(stdout, "somma: %d\n", somma(val));
        fprintf(stdout, "somma_r: %d\n", somma_r(val, &s));
    }
}