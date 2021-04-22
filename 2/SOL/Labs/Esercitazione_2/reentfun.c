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
    char* str1 = strndup(argv[1], MY_ARGV_MAX);
    char* savet1 = NULL;
    char* savet2 = NULL;
    char* token1 = strtok_r(str1, " ", &savet1);

    while(token1){
        printf("%s\n", token1);
        char* str2 = strndup(argv[2], MY_ARGV_MAX);
        char* token2 = strtok_r(str2, " ", &savet2);
        while(token2){
            printf("%s\n", token2);
            token2 = strtok_r(NULL, " ", &savet2);
        }
        token1 = strtok_r(NULL, " ", &savet2);
    }
    return 0;
}