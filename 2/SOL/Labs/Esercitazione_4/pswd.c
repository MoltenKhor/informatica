#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PSW_FILE "/etc/passwd"

#if !defined(MAX_LEN)
#define MAX_LEN 1024
#endif

int main(int argc, char* argv[]){

    if(argc != 2){
        fprintf(stderr, "pochi argomenti\nUse %s out-filename\n", argv[0]);
        return -1;
    }

    FILE *fd = NULL;
    FILE *fout = NULL;

    char *buffer = NULL;

    if((fd=fopen(PSW_FILE, "r"))==NULL){
        perror("errore lettura\n");
        goto error;
    }
    if((fout=fopen(argv[1], "w"))==NULL){
        perror("errore scrittura\n");
        goto error;
    }
    if((buffer=malloc(MAX_LEN*sizeof(char)))==NULL){
        perror("ellore buffer");
        goto error;
    }

    while(fgets(buffer, MAX_LEN, fd)!=NULL){
        char* newline;
        if((newline=strchr(buffer, '\n'))==NULL){
            fprintf(stderr, "max_len troppo piccolo\n");
            goto error;
        }
        *newline = '\0';
        char* colons;
        if((colons=strchr(buffer, ':'))==NULL){
            fprintf(stderr, "wrong format\n");
            goto error;
        }
        *colons = '\0';
        if(fprintf(fout, "%s\n", buffer)!=strlen(buffer)+1){
            perror("copy\n");
            goto error;
        }
    }

    fclose(fd);
    fclose(fout);
    free(buffer);

    return 0;

    error:
    if(fd) fclose(fd);
    if(fout) fclose(fout);
    if(buffer) free(buffer);
}