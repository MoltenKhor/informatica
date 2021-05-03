#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_INPUT_LINE 1024
#define MAX_PARAM 256

#define MALLOC(ptr, sz)                 \
    if((ptr=(char*)malloc(sz))==NULL){  \
        perror("malloc");               \
        exit(EXIT_FAILURE);             \
    } 
            

void build_args(char *line, char *argv[]){
    int i=0;
    char *tmpstr, *token = strtok_r(line, " ", &tmpstr);
    size_t len = strlen(token)+1;

    MALLOC(argv[i], len);
    strncpy(argv[i], token, len);

    while((token=strtok_r(NULL, " ", &tmpstr))!=NULL){
        i++;
        len = strlen(token)+1;
        MALLOC(argv[i], len);
        strncpy(argv[i], token, len);
    }
    argv[i+1] = NULL;
}

static void cleanarg(char* argv[]){
    int i=0;
    while(argv[i] != NULL){
        free(argv[i]);
        i++;
    }
}

static void print_prompt(){
    printf("> ");
    fflush(stdout);
}

int main(){
    int pid;
    int childforked = 0;
    int status;
    char inputline[MAX_INPUT_LINE];
    char *argv[MAX_PARAM];

    while(1){
        print_prompt();
        memset(inputline, 0, MAX_INPUT_LINE);                   //fill the first MAX_INPUT_LINE chars of inputline with 0
        if(read(STDIN_FILENO, inputline, MAX_INPUT_LINE) == -1){
            perror("leggendo linea di comando: ");
            continue;
        }
        inputline[strlen(inputline)-1] = '\0';
        if(inputline[0] != '\0') build_args(inputline, argv);
        else continue;

        if(strncmp(inputline, "exit", 4)==0){
            cleanarg(argv);
            break;
        }

        if((pid = fork())<0){
            perror("fork");
            continue;
        }

        if(pid == 0){
            execvp(argv[0], &argv[0]);
            perror("execvp");
            exit(errno);
        }

        childforked++;
        if((pid=waitpid(-1, &status, 0))!=-1){
            if(pid!=0){
                childforked--;
                if(WIFEXITED(status)){
                    fprintf(stdout, "Processo %d terminato con ", pid);
                    fprintf(stdout, "exit(%d)\n", WIFEXITED(status));
                    fflush(stdout);
                }
            }
        }
        cleanarg(argv);
    }
    while(childforked>0){
        if((pid=waitpid(-1, &status, WNOHANG))!= -1){
            if(pid != 0){
                childforked--;
                if(WIFEXITED(status)){
                    fprintf(stdout, "Processo %d terminato con ", pid);
                    fprintf(stdout, "exit(%d)\n", WIFEXITED(status));
                    fflush(stdout);
                }
            }
        }
    }
    printf("shell done ....\n");
    return 0;
}