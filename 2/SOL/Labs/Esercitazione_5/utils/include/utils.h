#if !defined(_UTIL_H)
#define _UTIL_H
#endif

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#if  !defined(BUFSIZE)
#define BUFSIZE 256
#endif

#if !defined(EXTRA_LEN_PRINT_ERROR)
#define EXTRA_LEN_PRINT_ERROR 512
#endif

#define SYSCAL_EXIT(name, r, sc, str, ...)  \
    if((r=sc)==-1){                         \
        perror(#name);                      \
        int errno_copy = errno;             \
        print_error(str, __VA_ARGS__);      \
        exit(errno_copy);                   \
    }


static inline void print_error(const char* str, ...){
    const char err[] = "ERROR: ";
    va_list argp;
    char* p=(char*)malloc(strlen(str)+strlen(err)+EXTRA_LEN_PRINT_ERROR);
    if(!p){
        perror("malloc");
        fprintf(stderr, "fatal error\n");
        return;
    }
    strcpy(p,err);
    strcpy(p+strlen(err), str);
    va_start(argp, str);
    vfprintf(stderr, p, argp);
    va_end(argp);
    free(p);
}

static inline int isNumber(const char* s, long* n) {
  if (s==NULL) return 1;
  if (strlen(s)==0) return 1;
  char* e = NULL;
  errno=0;
  long val = strtol(s, &e, 10);
  if (errno == ERANGE) return 2;    // overflow/underflow
  if (e != NULL && *e == (char)0) {
    *n = val;
    return 0;   // successo 
  }
  return 1;   // non e' un numero
}