#define _POSIX_C_SOURCE  200112L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokenizer.h"

void tokenizer(char* stringa, FILE* out){
    char* token = strtok(stringa, " ");
    while(token){
        fprintf(out, "%s\n", token);
        token = strtok(NULL, " ");
    }
}

void tokenizer_r(char* stringa, FILE* out){
    char* tmpstr;
    char* token = strtok_r(stringa, " ", &tmpstr);
    while(token){
        fprintf(out, "%s\n", token);
        token = strtok_r(NULL, " ", &tmpstr);
    }
}