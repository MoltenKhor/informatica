#ifndef THREADPOOL_H_
#define THREADPOOL_H_
#include <pthread.h>

typedef struct taskfun_t{
    void(*fun)(void*);
    void *arg;
}taskfun_t;


typedef struct threadpool_t{
    pthread_mutex_t lock;
    pthread_cond_t cond;
    pthread_t * threads;
    int numthreads;
    taskfun_t *pending_queue;
    int queue_size;
    int taskonthefly;
    int head, tail;
    int count;
    int exiting;
}threadpool_t;

threadpool_t *createThreadPool(int numthreads, int pending_size);

int destroyThreadPool(threadpool_t *pool, int force);

int addToThreadPool(threadpool_t *pool, void (*fun)(void*), void *arg);

int spawnThread(void (*f)(void*), void* arg);

#endif