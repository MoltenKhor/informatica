#if !defined(CONNECT_H)
#define CONNECT_H

#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

typedef struct arg_pack{
    long connfd;
    long *terminate;
    Memory_Index *memory_index;
}arg_pack;

#if !defined(BUFFERSIZE)
#define BUFFERSIZE 256
#endif

#if !defined(MAXBACKLOG)
#define MAXBACKLOG 32
#endif

char *SOCKNAME;



static inline int readn(long fd, void *buf, size_t size){
    size_t left = size;
    int r;
    char *bufptr = (char*)buf;
    while(left>0){
        if((r=read((int)fd, bufptr, left))==-1){
            if(errno==EINTR) continue;
            return -1;
        }
        if(r==0)return 0; //EOF
        left -= r;
        bufptr += r;
    }
    return size;
}
static inline int writen(long fd, void *buf, size_t size){
    size_t left = size;
    int r;
    char *bufptr = (char*)buf;
    while(left>0){
        if((r=write((int)fd, bufptr, left))==-1){
            if(errno==EINTR) continue;
            return -1;
        }
        if(r==0)return 0; //EOF
        left -= r;
        bufptr += r;
    }
    return 1;
}

#endif