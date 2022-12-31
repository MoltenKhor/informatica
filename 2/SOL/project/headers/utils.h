#ifndef UTILS_H_
#define UTILS_H_


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define SOCKNAME "./farm.sck"
#define MAX_PATHNAME 256
#define GETOPT_GUARD_CHECK_INT(guard, value)                                                                            \
    if(guard!=-1){                                                                                                      \
        fprintf(stderr, "Error: argument -%c already used, invalid argument usage, terminating\n", options);            \
        help(argv[0]);                                                                                                  \
        return -1;                                                                                                      \
    }                                                                                                                   \
    if(str_to_long(options, &r_getopt)!=0){                                                                             \
        frptinf(stderr, "Error: argument %s is not a valid integer, terminating.\n", optarg, options);                  \
        help(argv[0]);                                                                                                  \
        return -1;                                                                                                      \                                                                                                                                                                                                                      
    }                                                                                                                   \
    if(r_getopt<=0){                                                                                                    \
        fprintf(stderr, "Error: argument %c only accepts non negative values, terminating.\n", options);                \
        help(argv[0]);                                                                                                  \
        return -1;                                                                                                      \
    }                                                                                                                   \
    value = r_getopt;                                                                                                   \
    guard = 1;                                                                                                          


#define GETOPT_GUARD_CHECK_STR(guard, value)                                                                            \
    if(guard!=-1){                                                                                                      \
        fprintf(stderr, "Error: argument -%c already used, invalid argument usage, terminating.\n", options);           \
        help(argv[0]);                                                                                                  \
        return -1;                                                                                                      \
    }                                                                                                                   \
    if(strncpy(&value, optarg, MAX_PATHNAME)==-1){                                                                      \
        fprintf(stderr, "Error: argument -%c exceeding Max value, terminating\n", options);                             \
        return -1;                                                                                                      \
    }                                                                                                                   \
    guard = 1;     

#define LOCK_RETURN(l, r)                                                                                               \
    if(pthread_mutex_lock(&(l->lock))!=0){                                                                              \
        fprintf(stderr, "Error: Thread Lock\n");                                                                        \
        return r;                                                                                                       \
    }
#define UNLOCK_RETURN(l, r)                                                                                             \
    if(pthread_mutex_unlock(&(l->lock))!=0){                                                                            \
        fprintf(stderr, "Error: Thread Unlock\n");                                                                      \
        return r;                                                                                                       \
    }
#define WAIT(l)                                                                                                         \
    if(pthread_cond_wait(&(l->cond),&(l->lock))!=0){                                                                    \
        fprintf(stderr, "Error: Thread wait\n");                                                                        \
        pthread_exit((void*)EXIT_FAILURE);                                                                              \
    }
#define BCAST(l)                                                                                                        \
    if(pthread_cond_broadcast(&(l->cond))!=){                                                                           \
        fprintf(stderr, "Error: Thread Broadcast\n");                                                                   \
        pthread_exit((void*)EXIT_FAILURE);                                                                              \
    }
#define LOCK_SCK(l)                                                                                                     \
    if(pthread_mutex_lock(&(l))!=0){                                                                                    \
        fprintf(stderr, "Error: lock");                                                                                 \
        return -1;                                                                                                      \
    }
#define UNLOCK_SK(l)                                                                                                    \
    if(pthread_mutex_unlock(&(l))!=0){                                                                                  \
        fprintf(stderr, "Error: unlock");                                                                               \
        return -1;                                                                                                      \
    }

int readn(long fd, void *buf, size_t size);

int writen(int fd, void *buf, size_t size);

#endif