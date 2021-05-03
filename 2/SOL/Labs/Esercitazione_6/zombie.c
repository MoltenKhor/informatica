#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "usare %s <num>\n", argv[0]);
        return -1;
    }

    for(int i=0; i<atoi(argv[1]); i++){
        if(fork() == 0) exit(0);
    }

    printf("fra 50 secondi il programma terminerà\n");
    sleep(50);
    return 0;
}