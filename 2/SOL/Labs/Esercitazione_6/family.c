#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

void lancia(int n){
    int ppid = getpid();
    if(n>0){
        for(int i=0; i<n; i++) fprintf(stdout, "-");
        fprintf(stdout, "%d: creo un processo figlio\n", ppid);
        fflush(stdout);
        int pid = fork();
        if(pid == -1){ perror("fork"); exit(EXIT_FAILURE);}

        if(pid == 0){
            lancia(n-1); //figlio
        }else{
            int status;
            if(waitpid(pid, &status, 0)==-1){
                perror("wait");
                return;
            }
            if(!WIFEXITED(status)){
                fprintf(stdout,"%d: figlio %d terminato con fallimento\n", ppid, pid);
                fflush(stdout);
            }
            for(int i=0; i<n-1; i++){ fprintf(stdout, "-");}
            if(n>1) fprintf(stdout, " ");
            fprintf(stdout, "%d: terminato con successo\n", pid);
            fflush(stdout);
        }
    }else{
        fprintf(stdout, "%d, sono l'ultimo discendente\n", getpid());
    }
}

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "use %s <num>\n", argv[0]);
        return -1;
    }

    int n = atoi(argv[1]);
    int pid = getpid();
    lancia(n);

    if(pid==getpid()){
        for(int i=0; i<n; i++){
            fprintf(stdout, "-");
        }
        fprintf(stdout, "%d: terminato con successo\n", pid);
        fflush(stdout);
    }
}