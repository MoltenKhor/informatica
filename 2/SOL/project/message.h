#if !defined(_MESSAGE_H)
#define _MESSAGE_H

typedef struct msg{
    int len;
    long nfiles;
    int path_size;
    char *path;
    char action;
    char *buffer;
}msg_t;

#endif