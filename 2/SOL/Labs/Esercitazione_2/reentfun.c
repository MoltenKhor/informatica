#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MY_ARGV_MAX 512

char *strndup(const char *, size_t);

int main(int argc, char* argv[]){

    if(argc != 3){
        fprintf(stderr, "Use: %s Stringa 1 Stringa2\n", argv[0]);
        return -1;
    }    
    char* str1 = strndup(argv[1], MY_ARGV_MAX);                     //copio per sicurezza il valore di argv[1] dato che viene modificato da strtok
    char* savet1 = NULL;                                            //mi creo una variabile per memorizzare lo status dello strtok per ogni stringa 
    char* savet2 = NULL;
    char* token1 = strtok_r(str1, " ", &savet1);                    //effettuo la prima tokenizzazione, a differenza di strtok, strtok_r necessita di un argomento in più per il save

    while(token1){
        printf("%s\n", token1);
        char* str2 = strndup(argv[2], MY_ARGV_MAX);                 //salvo per sicurezza anche la seconda stringa
        char* token2 = strtok_r(str2, " ", &savet2);                //effettuo la tokenizzazione anche della seconda stringa
        while(token2){
            printf("%s\n", token2);
            token2 = strtok_r(NULL, " ", &savet2);
        }
        token1 = strtok_r(NULL, " ", &savet2);
    }
    return 0;
}