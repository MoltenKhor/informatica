#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <connect.h>
#include <api.h>
#include <util.h>

static int socketFD;
char *socketNM;


int openConnection(const char* sockname, int msec/*, const struct timespec abstime*/){
    socketNM = malloc(strlen(sockname)*sizeof(char));
    strncpy(socketNM, sockname, strlen(sockname));

    struct sockaddr_un serv_addr;
    
    SYSCALL_EXIT("socket", socketFD, socket(AF_UNIX, SOCK_STREAM, 0), "socket", "");
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, socketNM, strlen(socketNM)+1);

    int notused;
    SYSCALL_EXIT("connect", notused, connect(socketFD, (struct sockaddr*)&serv_addr, sizeof(serv_addr)), "connect", "");
    return 1;
}

int closeConnection(const char* sockname){

    if((strcmp(sockname, socketNM))==0){
        close(socketFD);
        return 0;
    }
    return 1;
}
/*
int openFile(const char* pathname, int flags){

}

int readFile(const char* pathname, void** buf, size_t* size){

}

int writeFile(const char* pathname, const char* dirname){

}*/

/*
int appendToFile(const char* pathname, void* buf, size_t size, const char* dirname){

}

int lockFile(const char* pathname){

}

int unlockFile(const char* pathname){

}

int closeFile(const char* pathname){

}

int removeFile(const char* pathname){
    
}
*/