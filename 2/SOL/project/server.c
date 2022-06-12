#define _POSIX_C_SOURCE 2001112L
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <sys/select.h>
#include <pthread.h>

#include <connect.h>
#include <threadpool.h>
#include <threadF.h>
#include <memory.h>


#define BUFFDIMENSION 50 //buffer dimension

int nWorkers;
long memoryDim;
long storageDim;
long memory_used;
long storage_used;

typedef struct{
    sigset_t *set;          //set of signal to be handled
    int signal_pipe;        //Pipe FD
}sigHandler_t;

static void *sigHandler(void *arg){
    sigset_t *set = ((sigHandler_t*)arg)->set;
    int fd_pipe = ((sigHandler_t*)arg)->signal_pipe;

    for( ;; ){
        int sig;
        int r = sigwait(set, &sig);
        if(r!=0){
            errno = r;
            perror("Sigwait fatal error");
            return NULL;
        }

        switch(sig){
            case SIGINT:
            case SIGQUIT:
            case SIGHUP:{ close(fd_pipe); return NULL;}
            default: ;
        }
    }
    return NULL;
}

int main(int argc, char* argv[]){

    FILE *config;
    fprintf(stdout,"FileSystem Manager Server Initializaton...\n");
    switch(argc){
        case 1: {       //in case of no arguments, load default config.txt file
            fprintf(stdout, "Reading default config file\n");
            if((config = fopen("config.txt", "r"))==NULL){
                perror("Opening default config file");
                exit(errno);
            }
        }break;
        case 2: {       //in case of 1 argument, load user selected config file
            fprintf(stdout, "Reading user defined config file\n");
            if((config = fopen(argv[1], "r"))==NULL){
                perror("Opening non-default config file");
                exit(errno);
            }break;
        }
        default: {      //non valid execution
            fprintf(stderr, "Use: %s <config file> || %s ", argv[0], argv[0]);
            exit(errno);
        }break;
    }

    char buff[BUFFDIMENSION], *token, *logfile;

    if(fgets(buff, BUFFDIMENSION, config) != NULL){
        int cont = 0;
        token = strtok(buff, ":");
        while(token){
            switch(cont){
                case 0:{
                    logfile = (char*)malloc(sizeof(char)*(strlen(token)+1));
                    strcpy(logfile, token);
                }break;
                case 1:{
                    SOCKNAME = (char*)malloc(sizeof(char)*(strlen(token)+1));
                    strcpy(SOCKNAME, token);
                }
                case 2:{
                    memoryDim = atol(token);
                }break;
                case 3:{
                    storageDim = atol(token);
                }break;
                case 4:{
                    nWorkers = atol(token);
                }break;
                default:{
                    perror("Bad configuration file format");
                    exit(1);
                }
            }
            cont++;
            token = strtok(NULL, ":");
        }
    }else{
        perror("Reading configuration file");
        exit(errno);
    }

    if(fclose(config)==-1){
        perror("Closing config file");
        exit(errno);
    }

    fprintf(stdout,"Server Configuration complete:\nlogfile: %s | socketfile: %s | Memory Dimension: %ld | Storage Dimension: %ld | Number of Workers: %d\n", logfile, SOCKNAME, memoryDim, storageDim, nWorkers);

    Memory_Index* memory = createMemory(memoryDim, storageDim);
    if(!memory){
        perror("creating memory index");
        goto _exit;
    }else{
        printf("Memory successfully created.\n");
    }

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGHUP);
    sigaddset(&mask, SIGQUIT);

    if(pthread_sigmask(SIG_BLOCK, &mask, NULL)!=0){ fprintf(stderr, "Fatal Error\n"); goto _exit;}

    struct sigaction s;
    memset(&s, 0, sizeof(s));
    s.sa_handler=SIG_IGN;
    if((sigaction(SIGPIPE, &s, NULL))==-1){
        perror("sigaction");
        goto _exit;
    }

    int signal_pipe[2];
    if(pipe(signal_pipe)==-1){
        perror("pipe");
        goto _exit;
    }

    pthread_t signalhandler_thread;
    sigHandler_t handlerArgs = {&mask, signal_pipe[1]};

    //initialisation of the sig handler thread 
    if(pthread_create(&signalhandler_thread, NULL, sigHandler, &handlerArgs)!=0){
        fprintf(stderr, "error creating signal handler thread\n");
        goto _exit;
    }

    int listenfd;
    if((listenfd = socket(AF_UNIX, SOCK_STREAM, 0))==-1){
        perror("socket");
        goto _exit;
    }
   

    struct sockaddr_un serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, SOCKNAME, strlen(SOCKNAME)+1);

    unlink(SOCKNAME);

    if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1){
        perror("bind");
        goto _exit;
    }
    if(listen(listenfd, MAXBACKLOG) ==-1){
        perror("listen");
        goto _exit;
    }

    threadpool_t *pool = NULL;

    pool = createThreadPool(nWorkers, nWorkers);
    if(!pool){
        fprintf(stderr, "Errore nella creazione della pool di thread\n");
        goto _exit;
    }

    fd_set set, tmpset;
    FD_ZERO(&set);
    FD_ZERO(&tmpset);
    FD_SET(listenfd, &set);             //aggiungo il listener al master set
    FD_SET(signal_pipe[0], &set);       //descrittore di lettura per il signal pipe

    int fdmax = (listenfd > signal_pipe[0])? listenfd : signal_pipe[0];

    volatile long terminate = 0;

    while(!terminate){
        tmpset = set;
        if(select(fdmax+1, &tmpset, NULL, NULL, NULL)==-1){
            perror("select");
            goto _exit;
        }
        
        for(int i=0; i<=fdmax; i++){
            if(FD_ISSET(i, &tmpset)){
                long connfd;
                if(i==listenfd){
                    if((connfd=accept(listenfd, (struct sockaddr*)NULL, NULL))==-1){
                        perror("accept");
                        goto _exit;
                    }
                    arg_pack *args = malloc(sizeof(arg_pack));

                    args->connfd = connfd;
                    args->terminate = (long*)&terminate;
                    args->memory_index = memory;
                    
                    int r = addToThreadPool(pool, threadF, (void*)args);
                    if(r==0) continue; 
                    if(r<0){ fprintf(stderr, "error adding thread to pool\n");}else{
                        fprintf(stderr, "all thread are busy\n");
                    }
                    free(args);
                    close(connfd);
                    continue;
                }
                if(i == signal_pipe[0]){
                    terminate = 1;
                    break;
                }
            }
        }
    }

    destroyThreadPool(pool, 0);

    pthread_join(signalhandler_thread, NULL);

    unlink(SOCKNAME);
    return 0;

    
_exit: 
unlink(SOCKNAME);
return -1;
}