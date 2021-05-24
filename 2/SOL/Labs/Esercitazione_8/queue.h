#ifndef QUEUE_H_
#define QUEUE_H_

#include <pthread.h>

typedef struct Node{
    void * data;
    struct Node * next;
}Node_t;

typedef struct queue{
    Node_t * head;
    Node_t * tail;
    unsigned long qlen;
    pthread_mutex_t qlock;
    pthread_cond_t qcond;
}Queue_t;

Queue_t* initQueue();
void deleteQueue(Queue_t *q);
int push(Queue_t *q, void *data);
void  *pop(Queue_t *q);
unsigne long lenght(Queue_t *q);

#endif
