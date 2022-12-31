/*
@file main.c
@brief Main implementation of a file Farm (SOL Project, UNIPI 2022-2023)
@author Marco Pontone 2022
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <getopt.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <utils.h>
#include <masterworker.h>
#include <threadpool.h>
#include <collector.h>
#include <format.h>
/*
@brief help method that prints a small manual for this application.
@note this function is invoked whenever an invalid argument is present.
@param argument - a char* value, tipically argv[0] for a filename as a string.
@returns none - void method.
*/
static void help(char* argument){
    fprintf(stdout,
    "|===================FARM HELP MANUAL===================|\n"\
    "Valid Arguments: %s -n <n>, -q <q>, -t <t> -d <d> <file>\n"\
    "[-n <n>]: integer value, use this argument to specify how manu worker thread to be initialized, defaul value of 4.\n"\
    "[-t <t>]: integer value, use this argument to specify the delay in msec between files elaboration.\n"\
    "[-d <d>]: directory value, use this argument to specify a directory of files to be elaborated by the farm.\n"\
    "[-q <q>]: integer value, use this argument to specify the file queue dimension, default value of 8.\n"\
    "[<file>]: file value, use this argument with no limits to specify files to be elaborated.\n"\
    "|======================================================|\n", argument);
}                                                                                                  

/*working variables*/
long n_thread = DEFAULT_THREAD_NUMBER;
long n_queue = DEFAULT_QUEUE_SIZE;
long delay = DEFAULT_DELAY;
char* dir = NULL;
int main(int argc, char** argv){
                                 
    if(argc == 1){
        fprintf(stderr, "not enough arguments.\n");
        help(argv[0]);
        return -1;
    }

    int _N, _Q, _T, _D = -1;                            //opt guards
    dir = malloc(MAX_PATHNAME*sizeof(char));            //directory pathname memory allocation
    long r_getopt;                                      //getopt read buffer
    opterr = 0;  
    int options;                                        //getopt variable

    while((options = getopt(argc, argv, ':n:q:t:d:')) != -1){
        switch(options){
            case 'n': GETOPT_GUARD_CHECK_INT(_N, n_thread); break;
            case 'q': GETOPT_GUARD_CHECK_INT(_Q, n_queue); break;
            case 'd': GETOPT_GUARD_CHECK_STR(_D, dir); break;
            case 't': GETOPT_GUARD_CHECK_INT(_T, delay); break;
        }
    }
/*
@breif Checks if no filenames have been input
*/
    if(argv[optind] == NULL && _D==-1){
        fprintf(stderr, "Error: no file specified, terminating.\n");
        help(argv[0]);
        return -1;
    }
/*@brief fork invoke and Collector initialization*/
pid_t pid;
pid = fork();
if(pid == -1){
    fprintf(stderr, "Error: Fork\n");
}

if(pid == 0){
    free(dir);
    if(collector_signal() == -1){
        fprintf(stderr, "Error: collector signal ignore\n");
        exit(EXIT_FAILURE);
    }
    if(collector_connection() != 0){
        fprinf(stderr, "Error: collector connection\n");
    }
    if(atexit(&c_conn_collector) != 0){
        fprintf(stderr, "Error: collector close connection\n");
    }
    if(atexit(&unlink_socket)){
        fprintf(stderr, "Error: collector socket unlink\n");
    }
    message_T* mess;
    int i=0;
    while(i != -1){
        mess = mallog(sizeof(message_T));
        if((i=response_Master(mess)) != 1){
            if(i==-1){
                fprintf(stderr, "Error: Master response\n");
            }else if(i == 2){
                farm_plot();
                free(mess);
                continue;
            }
            free(mess);
            break;
        }
        if(insert_result(mess) == -1){
            fprintf(stderr,"Error: result add\n");
            return -1;
        }
    }
    farm_plot();
    clean_result();
    return 0;
}else{
    /*@brief MasterWorker initialization*/
    init_sighandler_MW();
    struct stat stbuff;
    int k;
    if((k=stat(dir,&stbuff)) == -1){
        fprintf(stderr, "Error: stat\n");
        help(argv[0]);
        return -1;
    }
    if(S_ISREG(stbuff.st_mode)){
        fprintf(stderr, "Error: %s is not a valid directory, terminating.\n", dir);
        help(argv[0]);
        return -1;
    }
    if(open_connection_MW() != 0){
        fprintf(stderr, "Error: connection with master worker\n");
        return -1;
    }
    if(createThdreadPool(n_thread, n_queue, delay) == -1){
        fprintf(stderr, "Error: ThreadPool creation\n");
        return -1;
    }
    if(atexit(&freePoolRes) != 0){
        fprintf(stderr, "Error: Atexit free resources from ThreadPool\n");
    }
    standalone_files(dir);
    free(dir);
    while((optind<argc) && EXIT_PROT == 0){
        if((k=stat(argv[optind], &stbuff)) == -1){
            fprintf(stderr, "Error: stat\n");
            help(argv[0]);
            return -1;
        }
        if(S_ISREG(stbuff.st_mode)){
            char* file_pathname = malloc(sizeof(char)*MAX_PATHNAME);
            if(strncpy(&file_pathname, argv[optind], MAX_PATHNAME) == -1){
                fprintf(stderr, "Error: Directory error\n");
            }
            push_threadPool(file_pathname);
        }else{
            fprintf(stderr, "Error: %s not a file, ignoring this one\n", argv[optind]);
        }
        optind++;
    }
    if(closeThreadPool() == -1){
        fprintf(stderr, "Error: closing thread pool\n");
        return -1;
    }
    if(waitpid(pid, NULL, 0) == -1){
        fprintf(stderr, "Error: waitpid\n");
        return -1;
    }
    kill_sighandler();
    return 0;

    }
}








