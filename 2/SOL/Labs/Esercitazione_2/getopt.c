#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

#define NOPTIONS       4
#define MY_ARGV_MAX  512


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

int argh(const char* programname){
    printf("usage: %s -n <num> -m <num> -o <string> -h\n", programname);
    return -1;
}

int argn(const char* n){
    long tmp;
    if(isNumber(n, &tmp) != 0){
        printf("l'argomento di -n non è valido\n");
        return -1;
    }
    printf("-n: %ld\n", tmp);
    return 0;
}

int argm(const char* m){
    long tmp;
    if(isNumber(m, &tmp) != 0){
        printf("l'argomento di -m non è valido\n");
        return -1;
    }
    printf("-m: %ld\n", tmp);
    return 0;
}

int argo(const char* o){
    if(strlen(o)>MY_ARGV_MAX){
        printf("l'argomento di -o è troppo luno\n");
        return -1;
    }
    printf("-o: \"%s\"\n", o);
    return 0;
}



int main(int argc, char* argv[]){

    if (argc==1) {
        printf("almeno una opzione deve essere passata\n");
        argh(argv[0]);
        return -1;
    }

    int opt;

    while((opt = getopt(argc, argv, ":n:m:o:h")) != -1){
        switch(opt){
            case 'n': argn(optarg); break;
            case 'm': argm(optarg); break;
            case 'o': argo(optarg); break;
            case 'h': argh(argv[0]); break;
            case ':': {
                printf("L'opzione '-%c' richiede un argomento", optopt);
            }break;
            case '?': {
                printf("L'opzione '-%c' non è gestita", optopt);
            }break;
            default:;
        }
    }
    return 0;
}