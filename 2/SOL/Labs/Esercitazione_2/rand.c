#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#define N 10000
#define K1 1
#define K2 10

int ranr_r(unsigned int *seedp);

int isNumber(const char* s, long* n) {
  if (s==NULL) return 1;
  if (strlen(s)==0) return 1;
  char* e = NULL;
  errno=0;
  long val = strtol(s, &e, 10);
  if (errno == ERANGE) return 2;    // overflow
  if (e != NULL && *e == (char)0) {
    *n = val;
    return 0;   // successo 
  }
  return 1;   // non e' un numero
}

int main(int argc, char* argv[]){

    long k1 = K1;
    long k2 = K2;
    long n = N;

    if(argc>1){
        if(argc!=4){
            printf("Usa %s K1 K2 N\n", argv[0]);
            return -1;
        }
        if((isNumber(argv[1], &k1)!=0)){
            printf("argomento K1 non valido\n");
            return -1;
        }
        if((isNumber(argv[2], &k2))!=0){
            printf("argomento K2 non valido\n");
            return -1;
        }
        if((isNumber(argv[3], &n))!=0){
            printf("argomento N non valido\n");
            return -1;
        }
        if(k2<k1){
            printf("range di k2 e k1 non validi\n");
            return -1;
        }
    }

    unsigned int seed = time(NULL);
    const long k = k2-k1;

    long c[k];

    for(int i=0; i<k; i++){
        c[i]=0;
    }

    for(int i=0; i<n; i++){
        long r = k1+rand_r(&seed)%k;
        c[r%k]++;
    }

    printf("Occorrenze:\n");
    for(int i=0; i<k; i++){
        printf("%ld : %5.2f%% \n", i+k1, (c[i]/(float)n)*100);
    }
    printf("\n");
    return 0;



}