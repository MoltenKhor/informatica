#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


#define BUFFDIMENSION 50 //buffer dimension

int nWorkers;
long memoryDim;
long storageDim;
char *socketfile;

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
                    socketfile = (char*)malloc(sizeof(char)*(strlen(token)+1));
                    strcpy(socketfile, token);
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

fprintf(stdout,"Server Configuration complete:\nlogfile: %s | socketfile: %s | Memory Dimension: %ld | Storage Dimension: %ld | Number of Workers: %d\n", logfile, socketfile, memoryDim, storageDim, nWorkers);


}