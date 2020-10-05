#include <stdio.h>
#include <stdlib.h>

#if !defined(INIT_VALUE)
#error("please compile with flag -DINIT_VALUE=n");
#endif

int somma_r(int x, int *s){
     *s += x;
     return *s;
}

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "usa %s N\n", argv[0]);
        return -1;
    }
    int N = strtol(argv[1], NULL, 10);
    if(N<=0 || N>10){
        fprintf(stderr, "N deve essere maggiore di 0 e massimo 10\n");
        return -1;
    }
    int s = INIT_VALUE;

    for(int i=0; i<N; i++){
        int val;
        fprintf(stdout, "inserisci un numero (%d rimasti):", N-i);
        if(fscanf(stdin, "%d", &val) !=1){
            perror("fscanf");
            return EXIT_FAILURE;
        }
            fprintf(stdout, "somma_r %d\n", somma_r(val, &s));
    }

    return 0;
}