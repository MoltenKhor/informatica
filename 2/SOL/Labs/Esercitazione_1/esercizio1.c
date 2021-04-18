#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void strtoupper(const char* in, size_t len, char* out){
    for(int i=0; i<len; i++){
        out[i] = toupper(in[i]);                                //Per ogni carattere della stringa uso la funzione toupper
    }                                                           //che converte da lowercase a uppercase o lascia inalterato
    out[len] = '\0';                                            //infine aggiungo l'end-of-line
};

int main(int argc, char* argv[]){
    
    for(int i=1; i<argc; i++){                                   //Per ogni argomento passato al main
        size_t len = strlen(argv[i]);                            //memorizzo la dimensione della stringa
        char*str;
        if((str = malloc(len+1))!=NULL){            
            strtoupper(argv[i], len, str);                       //alloco una nuova stringa della stessa dimensione dell'argomento
            printf("%s\n", str);                                 //e la mando alla funzione che converte uppercase ogni carattere
            free(str);                                           //Infine stampo la medesima stringa volta per volta.
        }else{
            exit(-1);
        }
    }
    return 0;
}