#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "usare %s <num>\n", argv[0]);
        return -1;
    }
    int pid = fork();
    if(pid == 0){               //primo figlio
        if((pid=fork())==0){    //secondo figlio
            execl("/bin/sleep", "/bin/sleep", argv[1], NULL);
            perror("execl");
            exit(EXIT_FAILURE);
        }
        if(waitpid(pid, NULL, 0)<0){
            fprintf(stderr, "wait error\n");
            return -1;
        }
        printf("mio= %d, padre= %d\n", getpid(), getppid());
        return 0;
    }
    return 0;
}