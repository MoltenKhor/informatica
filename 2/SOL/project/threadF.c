#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <sys/select.h>
#include <sys/uio.h>

#include <connect.h>
#include <message.h>
#include <util.h>
#include <memory.h>



static void w_action(long connfd, Memory_Index *memory, struct iovec iov[]){
    int notused;
   // int n=0;
    printf("in action\n");
    //long howmany;
    /*if((n=readn(connfd, &howmany, sizeof(long)))==-1){
        perror("read how many files");
        return;
    }
    howmany = *(long*)(iov[1].iov_base);

           
    if(howmany > (memory->maxFiles-memory->filesStored)){
        fprintf(stderr, "not enough storage for %ld files, %ld free slots available.\n", howmany, memory->maxFiles-memory->filesStored);
        return;
    }*/
  
    long path_len =0;
    char *path_name = NULL;
    //long file_size = 0;

    SYSCALL_EXIT("readn", notused, readn(connfd, &path_len, sizeof(long)), "read", "");
    path_len = iov[3].iov_len;

    path_name = realloc(path_name, path_len);

    SYSCALL_EXIT("readn", notused, read(connfd, path_name, path_len*sizeof(char)), "read", "");
    if(!path_name){
        perror("malloc");
        free(path_name);
    }else{
        printf("received file: %s\n", path_name);
    }
    strncpy(path_name, (char*)iov[3].iov_base, iov[3].iov_len);

    if(insertFileInMemory(memory, path_len, path_name, 15, 15, path_name)!=0){
        fprintf(stderr, "error adding file\n");
    }else{
        printf("file %s successfuly stored for %ld kbytes.\n", path_name, path_len);
    }

    /*for(int i=0; i<howmany; i++){
        
        SYSCALL_EXIT("readn", notused, readn(connfd, &file_size, sizeof(int)), "read", "");
        file_size = *(size_t*)iov[2].iov_base;
        if(file_size > (memory->memorySize - memory->memoryUsed)){
            fprintf(stderr, "File too big, abort write.\n");
            break;
        }


        SYSCALL_EXIT("read", notused, readn(connfd, &path_len, sizeof(long)), "read", "");

        path_len = iov[3].iov_len;
        path_name = realloc(path_name, path_len);
        SYSCALL_EXIT("readn", notused, readn(connfd, path_name, path_len*sizeof(char)), "read", "");
       
        if(!path_name){
            perror("malloc");
            free(path_name);
            break;
        }
         strncpy(path_name, (char*)iov[3].iov_base, iov[3].iov_len);
        long buffer_size = 0;

        SYSCALL_EXIT("readn", notused, readn(connfd, &buffer_size, sizeof(long)), "read", "");
        buffer_size = (long)iov[4].iov_len;
        char *read_buffer = malloc(buffer_size+1);
        SYSCALL_EXIT("readn", notused, readn(connfd, read_buffer, buffer_size*sizeof(char)), "read", "");
        strncpy(read_buffer, (char*)(iov[4].iov_base), iov[4].iov_len);
        read_buffer[buffer_size] = '\0';

        if(insertFileInMemory(memory, path_len, path_name, file_size, buffer_size, read_buffer)!=0){
            fprintf(stderr, "error adding file\n");
            free(read_buffer);
            break;
        } 
        
       // SYSCALL_EXIT("writen", notused, writen(connfd, read_buffer, buffer_size*sizeof(char)), "write", "");
        printf("file %s successfuly stored for %ld kbytes.\n", path_name, file_size);
        free(read_buffer);

    } */
}

void threadF(void *arg){
    
    assert(arg);
    arg_pack *args = arg;
    long connfd = args->connfd;
    long* terminate = args->terminate;
    Memory_Index *memory = args->memory_index;

    free(arg);
    fd_set set, tmpset;
    FD_ZERO(&set);
    FD_SET(connfd, &set);

    do{
        tmpset = set;
        int r;
        struct timeval timeout = {0, 10000};
        if((r=select(connfd+1, &tmpset, NULL, NULL, &timeout))<0){
            perror("select");
            break;
        }
        if(r==0){
            if(*terminate) break;
            continue;
        }
        int action = 1;
        
        //int act;
       /* if((act=readn(connfd, &str.action, sizeof(char)))==-1){
            perror("read_act");
            break;
        }*/
        size_t byteread;
        byteread = 0;
            long n;
            long filesize;
            char pathname[15];
            char content[44];
            struct iovec iov[5];
            iov[0].iov_base = &action;
            iov[0].iov_len = sizeof(char);
            iov[1].iov_base = &n;
            iov[1].iov_len = sizeof(long);
            iov[2].iov_base = &filesize;
            iov[2].iov_len = sizeof(long);
            iov[3].iov_base = pathname;
            iov[3].iov_len = sizeof(char[15]);
            iov[4].iov_base = content;
            iov[4].iov_len = sizeof(char[44]);
        byteread = readv(connfd, iov, 5);
        if(byteread==0) break;
        action = 1;
        printf("action: %d\n", action);
       switch(action){
            case 1: w_action(connfd, memory, iov);
            case '0': //W_action(connfd, &str);
            case '2': //r_action(connfd, &str);
            case '3': //R_action(connfd, &str);
            default: break;
        } 
        break;
     
    }while(*terminate==0);
    close(connfd);
}