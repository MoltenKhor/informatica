#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <util.h>
#include <threadpool.h>

#include <util.h>


static void *workerpool_thread(void *threadpool){

    threadpool_t *pool = (threadpool_t *)threadpool;
    taskfun_t task;
    pthread_t self = pthread_self();
    int myid = -1;

    do{
        for (int i=0; i<pool->numthreads; ++i){
            if(pthread_equal(pool->threads[i], self)){
                myid = i;
                break;
            }
        }
    }while(myid<0);

    if(pthread_mutex_lock(&(pool->lock))!=0){
        fprintf(stderr, "Error Lock\n");
    }

    for(;;){

        //attesa di un messaggio
        while((pool->count == 0) && (!pool->exiting)){
            pthread_cond_wait(&(pool->cond), &(pool->lock));
        }

        if(pool->exiting >1) break; //exit forzato

        if(pool->exiting ==1 && !pool->count) break;    //se ci sono messaggi pendenti

        //nuovo task
        task.fun = pool->pending_queue[pool->head].fun;
        task.arg = pool->pending_queue[pool->head].arg;

        pool->head++; pool->count--;
        pool->head = (pool->head == abs(pool->queue_size)) ? 0 : pool->head;

        pool->taskonthefly++;

        if(pthread_mutex_unlock(&(pool->lock))!=0){
            fprintf(stderr, "Error unlock\n");
        }
        
        (*(task.fun))(task.arg);
        if(pthread_mutex_lock(&(pool->lock)) != 0){
            fprintf(stderr, "error lock\n");
        }

        pool->taskonthefly--;
    }

    if(pthread_mutex_unlock(&(pool->lock)) != 0){
        fprintf(stderr, "error unlock\n");
    }

    fprintf(stderr, "thread %d exiting\n", myid);
    return NULL;
}

static int freePoolResources(threadpool_t *pool){
    if(pool->threads){
    free(pool->threads);
    free(pool->pending_queue);

    pthread_mutex_destroy(&(pool->lock));
    pthread_cond_destroy(&(pool->cond));
    }
    free(pool);
    return 0;
}

threadpool_t *createThreadPool(int numthreads, int pending_size){
    if(numthreads <= 0 || pending_size < 0){
        errno = EINVAL;
        return NULL;
    }

    threadpool_t *pool = (threadpool_t *)malloc(sizeof(threadpool_t));
    if(pool == NULL) return NULL;

    //init conditions
    pool->numthreads    = 0;
    pool->taskonthefly  = 0;
    pool->queue_size    = (pending_size == 0 ? -1 : pending_size);
    pool->head = pool->tail = pool->count = 0;
    pool->exiting = 0;

    //thread allocation and task queue
    pool->threads = (pthread_t *)malloc(sizeof(pthread_t)*numthreads);
    if(pool->threads == NULL){
        free(pool);
        return NULL;
    }
    pool->pending_queue = (taskfun_t *)malloc(sizeof(taskfun_t)*abs(pool->queue_size));
    if(pool->pending_queue == NULL){
        free(pool->threads);
        free(pool);
        return NULL;
    }
    if((pthread_mutex_init(&(pool->lock), NULL)!= 0) || (pthread_cond_init(&(pool->cond), NULL) !=0)){
        free(pool->threads);
        free(pool->pending_queue);
        free(pool);
        return NULL;
    }
    for(int i=0; i< numthreads; i++){
        if(pthread_create(&(pool->threads[i]), NULL, workerpool_thread, (void*)pool) != 0){
            destroyThreadPool(pool, 1);
            errno = EFAULT;
            return NULL;
        }
        pool->numthreads++;
    }
    return pool;
}

int destroyThreadPool(threadpool_t *pool, int force){
    if(pool == NULL || force <0){
        errno = EINVAL;
        return -1;
    }

    if(pthread_mutex_unlock(&(pool->lock))!=0){
        fprintf(stderr, "error unlock\n");
        return -1;
    }

    pool->exiting = 1 + force;

    if(pthread_cond_broadcast(&(pool->cond)) !=0 ){
        if(pthread_mutex_unlock(&(pool->lock))!=0){
            fprintf(stderr, "error unlock\n");
        }
        errno= EFAULT;
        return -1;
    }

    if(pthread_mutex_unlock(&(pool->lock))!=0){
        fprintf(stderr, "error unlock\n");
        return -1;
    }

    for(int i=0; i<pool->numthreads; i++){
        if(pthread_join(pool->threads[i], NULL) !=0){
            errno = EFAULT;
            if(pthread_mutex_unlock(&(pool->lock)) != 0){
                return -1;
            }
            return -1;
        }
    }
    freePoolResources(pool);
    return 0;
}

int addToThreadPool(threadpool_t *pool, void (*f)(void *), void *arg){
    if(pool == NULL || f == NULL){
        errno = EINVAL;
        return -1;
    }
    LOCK_RETURN(&(pool->lock), -1);

    int queue_size = abs(pool->queue_size);
    int nopending = (pool->queue_size == -1);   //nessun messaggio pendente

    if(pool->count >= queue_size || pool->exiting){
        UNLOCK_RETURN(&(pool->lock), -1);
        return 1;
    }

    if(pool->taskonthefly >= pool->numthreads){
        if(nopending){
            assert(pool->count == 0);

            UNLOCK_RETURN(&(pool->lock), -1);
            return 1;
        }
    }

    pool->pending_queue[pool->tail].fun = f;
    pool->pending_queue[pool->tail].arg = arg;
    pool->count++;
    pool->tail++;

    if(pool->tail >= queue_size) pool->tail = 0;

    int r;
    if((r=pthread_cond_signal(&(pool->cond)))!=0){
        UNLOCK_RETURN(&(pool->lock), -1);
        errno = r;
        return -1;
    }
    UNLOCK_RETURN(&(pool->lock), -1);
    return 0;
}

static void *proxy_thread(void *arg){
    taskfun_t *task = (taskfun_t *)arg;

    (*(task->fun))(task->arg);

    free(task);
    return NULL;
}

int spawnThread(void (*f)(void*), void* arg){
    if(f==NULL){
        errno = EINVAL;
        return -1;
    }

    taskfun_t *task = malloc(sizeof(taskfun_t));

    if(!task) return -1;
    task->fun = f;
    task->arg = arg;

    pthread_t thread;
    pthread_attr_t attr;
    if(pthread_attr_init(&attr) != 0) return -1;
    if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) return -1;
    if(pthread_create(&thread, &attr, proxy_thread, (void*)task)!=0){
        free(task);
        errno = EFAULT;
        return -1;
    }
    return 0;
}