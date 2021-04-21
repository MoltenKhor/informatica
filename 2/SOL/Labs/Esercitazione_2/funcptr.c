#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>

#define NOPTIONS    4                           //numero di opzioni consentite
#define MY_ARGV_MAX 512                         //numero massimo di caratteri consentiti nel comando o

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

int argh(const char* programname, void** a) {
    printf("usage: %s -n <num> -m <num> -o <string> -h\n", programname);
    return -1;
}

int argn(const char* n, void** a) {
  long tmp;
  if (isNumber(n, &tmp) != 0) {
    printf("l'argomento %s non e' valido\n", n);
    return -1;
  }
  *a = malloc(sizeof(long));
  if (!*a) {
    perror("malloc");
    return -1;
  }
  *(long*)*a = tmp;
  return 0;
}

int argm(const char* m, void** a) {
  return argn(m,a);
}

int argo(const char* o, void** a) {
  if ((*a = strndup(o, MY_ARGV_MAX)) == NULL) {
    perror("strndup");
    return -1;
  }
  return 0;
}

typedef int (*F_t)(const char*, void** arg);

typedef struct V_entry {
  F_t   F;   // puntatore a funzione
  void* a;   // valore dell'argomento gestito dalla funzione
} V_entry;

int main(int argc, char* argv[]){
  if (argc==1) {
    printf("almeno una opzione deve essere passata\n");
    argh(argv[0], NULL);
    return -1;
  }

    V_entry V[NOPTIONS] = {
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL}
    };

    V[0].F = argh;
    V[1].F = argn;
    V[2].F = argm;
    V[3].F = argo;

    int opt;

    int r = EXIT_SUCCESS;

    while((opt = getopt(argc, argv, ":n:m:o:h"))!= -1){
        switch(opt){
            case ':':{
                printf("l'opzione '-%c' richiede un argomento\n", opt);
                r = EXIT_FAILURE;
            }break;
            case '?':{
                printf("l'opzione '-%c' non è gestita\n", opt);
                r = EXIT_FAILURE;
            }break;
            default: if(V[opt % NOPTIONS].F((optarg==NULL?argv[0]:optarg), &V[opt % NOPTIONS].a) == -1)
            r = EXIT_FAILURE;
        }
    }

    if (V[1].a)  printf("m = %ld\n",     *(long*)(V[1].a));
    if (V[2].a)  printf("n = %ld\n",     *(long*)(V[2].a));
    if (V[3].a)  printf("o = \"%s\"\n",   (char*)(V[3].a));

    free(V[1].a);
    free(V[2].a);
    free(V[3].a);

}