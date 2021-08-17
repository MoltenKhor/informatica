#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <sys/uio.h>

#include <util.h>
#include <connect.h>
#include <api.h>

#define MAX_ARG_LEN 512
#define MAX_ARG_NAME 128
char *socketfile;
int verbose = 0;
int nCommands = 0;
long requestDelay = 0;
char *missDirectory = NULL;
char *saveDirectory = NULL;


void clean(){
    free(socketfile);
}

/*command execution function, some called directly some from append list*/
int comm_help(const char* programname){
    printf("============FileSystem Manager terminal Client============\n\n \
    Use %s <list of commands>\n\n=========List of commands:=========\n\
    -h : [Accepted once] Prints all available commands and usage for Client, then terminates the Client process.\n\
    -p : [Accepted once] Enables prints on standard output for every operation.\n\
    -f <filename> : [Accepted once] Selects a user-defined AF_UNIX socket.\n\
    -w <dirname>,<n> : Sends to the server all files in -dirname- folder, the server will write them, -n- specifies the number of files that will be written, unlimited if n=0 or unspecified.\n\
    -W <file>,...<file> : List of file to be written by the server separated bi ',' if more than one filename.\n\
    -D <dirname> : Defines the 'Trash' directory in case of capacity misses by the client.\n\
    -r <file>,...<file> : List of file that will be read by the server, separated by ',' if more than one\n\
    -R <n> : Reads all files in the server, if n is 0 or unspecified there's no limit on the list.\n\
    -d <dirname> : Specifies the folder where to store all files coming from the server.\n\
    -t <time> : Specifies a delay in milliseconds from one server request to another.\n\
    -l <file>,...<file> : List of files which sets mutex.\n\
    -u <file>,...<file> : List of files which release mutex.\n\
    -c <file>,...<file> : List of files to be removed from the server.\n\
    =======================================================\n", programname);
    exit(EXIT_SUCCESS);
}

int comm_p(){
    verbose = 1;
    printf("> ==VERBOSE MODE ENABLED==\n");
    return 1;
}

int comm_f(const char *arg){
    if(strlen(arg)>MAX_ARG_LEN){
        printf("-f Argument is too long\n");
        exit(EXIT_FAILURE);
    }

    FILE *test;

    if((test = fopen(arg, "r"))){                                             
        if((socketfile = (char*)malloc(strlen(arg)))){
            if(verbose){
                printf("> User-defined socket file found, memory allocated successfully.\n");
            }
            fclose(test);
            return 1;
        }else{
            perror("During socketfile malloc");
            fclose(test);
            clean();
            exit(EXIT_FAILURE);
        }                  
    }else{
        fclose(test);
        perror("Testing socket file validity");
        clean();
        exit(EXIT_FAILURE);
    }
    return 0;
}

int comm_t_(const char *arg){
    long millis;
    if((isNumber(arg, &millis))==0){
        requestDelay = millis;
        if(verbose){
            printf("> Server request delay set to %ldmilliseconds.\n", requestDelay);
        }
        return 1;
    }else{
        perror("-t argument not valid");
        clean();
        exit(EXIT_FAILURE);
        return 0;
    }
}

int comm_D(const char *arg){
    struct stat st = {0};
    if(stat(arg, &st)==-1){             //if directory doesn't exixts it'll create one with pathname
        mkdir(arg, S_IRWXO);
        if(verbose){
            printf("> Miss Directory not found, created a new one using '%s'\n", arg);
        }
        return 1;
    }else{
       if((missDirectory = (char*)malloc(strlen(arg)))){
           if(verbose){
               printf("> Miss Directory found, memory allocated successfuly.\n");
           }
           return 1;
       }else{
           perror("miss directory malloc");
           clean();
           exit(EXIT_FAILURE);
       }
    }
}

int comm_w(const char *arg){
    return 1;
}

int comm_W(const char *arg){
    return 1;
}

int comm_d(const char *arg){
    return 1;
}

int comm_r(const char *arg){
    return 1;
}

int comm_R(const char *arg){
    return 1;
}

int comm_l(const char *arg){
    return 1;
}

int comm_u(const char *arg){
    return 1;
}

int comm_c(const char *arg){
    return 1;
}



void append_command( char *arg, char* command){
   // struct timespec timer;
    openConnection(socketfile, 1000);

    closeConnection(socketfile);
    return;
}


int main(int argc, char* argv[]){

    if(argc == 1){
        printf("Insert atleast one option as argument\n");
        comm_help(argv[0]); 
        return -1;
    }
    socketfile = "./sk_sock";
    int opt;

    while((opt = getopt(argc, argv, ":f:w:W:d:r:R:D:t:l:u:c:p h")) != -1){
        switch(opt){
            //preliminary setup commands (must execute setup instruction asap)
            case 'h': comm_help(argv[0]); break;
            case 'p': comm_p(); break;
            case 't': comm_t_(optarg); break;
            case 'f': comm_f(optarg); break;
            case 'D': comm_D(optarg); break;        
            case 'd': comm_d(optarg); break;        //todo
            //read-write commands to be append
            case 'w': append_command(optarg, "w"); break;       //todo
            case 'W': append_command(optarg, "W"); break;       //todo
            case 'r': append_command(optarg, "r"); break;       //todo
            case 'R': append_command(optarg, "R"); break;       //todo
            //mutex commands
            case 'l': comm_l(optarg); break;                    //todo 
            case 'u': comm_u(optarg); break;                    //todo
            case 'c': comm_c(optarg); break;                    //todo
            //unrecongized commands
            case ':':{ printf("Option '-%c' requires an argument\n",optopt); }
            case '?':{ printf("Option '-%c' not valid\n", optopt); }
            default : comm_help(argv[0]); break;
        }
    }




    //clean();            //used in devops to clean unused mallocs
    return 0;
}