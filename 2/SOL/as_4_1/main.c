#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSW_FILE "/etc/password"
#define MAX_LEN 1024

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "too few arguments\nuse: %sfilename\n", argv[0]);
        return -1;
    }

    FILE *fd =NULL;
    FILE *fout = NULL;
    char *buffer = NULL;

    if((fd=fopen(PASSW_FILE, "r"))==NULL){
        perror("opening password file");
        goto error;
    }
    if((fout=fopen(argv[1],"w"))==NULL){
        perror("opening list file");
        goto error;
    }
    if((buffer=malloc(MAX_LEN*sizeof(char)))==NULL){
        perror("memory allocation");
        goto error;
    }

    while(fgets(buffer, MAX_LEN, fd)!=NULL){
        char* newline;
        if((newline=strchr(buffer, '\n'))==NULL){
            fprintf(stderr, "consider increasing max_len");
            goto error;
        }
        *newline = '\0';
        char *colons;
        if((colons=strchr(buffer, ':'))==NULL){
            fprintf(stderr, "wrong format");
            goto error;
        }
        *colons = '\0';

        fprintf(fout, "%s\n", buffer);
    }

    fclose(fd);
    fclose(fout);
    free(buffer);

    return 0;

    error:
    if(fd) fclose(fd);
    if(fout) fclose(fout);
    if(buffer) free(buffer);

    exit(EXIT_FAILURE); 
  
}
