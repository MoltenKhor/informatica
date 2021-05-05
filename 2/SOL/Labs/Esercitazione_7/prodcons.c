
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include <util.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int buffer;
static char bufferempty = 1;

void *Produtt(void* unused){
    for(int i=0; i<1000; i++){
        LOCK(&mutex);
        while(!bufferempty){
            WAIT(&cond, &mutex);
        }
        buffer = i;
        bufferempty = 0;
        SIGNAL(&cond);
        UNLOCK(&mutex);
    }
    fprintf(stdout, "Consumatore exit\n");

    LOCK(&mutex);
    while(!bufferempty){
        WAIT(&cond, &mutex);
    }
    buffer = -1;
    bufferempty = 0;

    SIGNAL(&cond);
    UNLOCK(&mutex);

    return NULL;
}

void *Consume(void* unused){
    int val = 0;
    while(val>=0){
        LOCK(&mutex);
        while(bufferempty){
            WAIT(&cond, &mutex);
        }

        val = buffer;
        bufferempty = 1;
        SIGNAL(&cond);
        UNLOCK(&mutex);
        fprintf(stdout, "Consumer; %d\n", val);
    }
    fprintf(stdout, "consumer exit\n");

    return NULL;
}

int main(){
    pthread_t cons, prod;
    if(pthread_create(&cons, NULL, Consume, NULL) != 0){
        fprintf(stderr, "errore creazione consumatore\n");
        return -1;
    }
    if(pthread_create(&prod, NULL, Produtt, NULL) != 0){
        fprintf(stderr, "errore creazione produttore\n");
        return -1;
    }
    if(pthread_join(cons, NULL) != 0){
        fprintf(stderr, "errore join consumatore\n");
        return -1;
    }
    if(pthread_join(prod, NULL) != 0){
        fprintf(stderr, "errore join produttore\n");
        return -1;
    }
    return 0;
}