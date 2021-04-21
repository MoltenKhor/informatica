#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

#define NOPTIONS       4                                    //numero massimo di opzioni consentite
#define MY_ARGV_MAX  512                                    //numero massimo di caratteri consentiti per il comando -o


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

//ogni funzione effettua la stampa della sua tipologia separatamente
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

    int opt;                                                               //inizializzo una variabile per la memorizzazione dell'opzione

    while((opt = getopt(argc, argv, ":n:m:o:h")) != -1){                   //La funzione getopt ritorna o i valori riconosciuti nella stringa ":n:m:o:h" divisi da : oppure ? se nessun comando è stato riconosciuto
        switch(opt){                                                       //utilizziamo opt per lo switch per selezionare quale funzione chiamare 
            case 'n': argn(optarg); break;
            case 'm': argm(optarg); break;
            case 'o': argo(optarg); break;                              
            case 'h': argh(argv[0]); break;
            case ':': {
                printf("L'opzione '-%c' richiede un argomento", optopt);    //in questo caso getopt ha rilevato il carattere - ma seguito da nessun carattere
            }break;
            case '?': {
                printf("L'opzione '-%c' non è gestita", optopt);            //in questo caso getopt ha rilevato un carattere non presente nella stringa degli ammessi
            }break;
            default:;                                                       //il default non effettua nessuna operazione, perché appunto, nessun comando da eseguire
        }
    }
    return 0;
}