#define _POSIX_C_SOURCE 200112L
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <stdatomic.h>

#include <util.h>

typedef pthread_mutex_t forchetta_t;

typedef struct threadArgs{
    int thid;
    int N;
    forchetta_t *fork;
}threadArgs_t;

static long ITER = 2000;

static inline long atomicDec(long *v){
    long r;
    r = atomic_fetch_sub(v, 1);
    return r;
}

void Mangia(unsigned int *seed){
    long r = rand_r(seed) % 80000;
    struct timespec t = {0, r};
    nanosleep(&t, NULL);
}

void Pensa(unsigned int *seed){
    long r = rand_r(seed) % 100000;
    struct timespec t = {0, r};
    nanosleep(&t, NULL);
}

void *Filosofo(void *arg){
    int myid    = ((threadArgs_t*)arg)->thid;
    int N       = ((threadArgs_t*)arg)->N;
    int left    = myid % N;
    int right   = myid-1;

    forchetta_t* destra = &((threadArgs_t*)arg)->fork[right];
    forchetta_t* sinistra = &((threadArgs_t*)arg)->fork[left];
    unsigned int seed = myid * time(NULL);
    int mangia = 0;
    int pensa = 0;

    for(;;){
        if(atomicDec(&ITER)<=0) break;
        Pensa(&seed);
        ++pensa;

        if(left < right){
            LOCK(destra);
            LOCK(sinistra);
            ++mangia;
            Mangia(&seed);
            UNLOCK(sinistra);
            UNLOCK(destra);
        }else{
            LOCK(sinistra);
            LOCK(destra);
            ++mangia;
            Mangia(&seed);
            UNLOCK(destra);
            UNLOCK(sinistra);
        }
    } 
    fprintf(stdout, "Filosofo %d: ho mangiato %d volte e pensato %d volte\n", myid, mangia, pensa);
    fflush(stdout);
    return (NULL);

}

int main(int argc, char* argv[]){
    int N = 5;
    if(argc > 1){
        N = atoi(argv[1]);
        if(N>100){
            fprintf(stderr, "N ridotto a 100\n");
            N=100;
        }
    }
    pthread_t *th;
    threadArgs_t *thargs;
    forchetta_t *forks;

    th = malloc(N*sizeof(pthread_t));
    thargs = malloc(N*sizeof(threadArgs_t));

    forks = malloc(N*sizeof(forchetta_t));

    if(!th || !thargs || !forks){
        fprintf(stderr, "errore allocazione\n");
        return -1;
    }
    for(int i=0; i<N; i++){
        if(pthread_mutex_init(&forks[i], NULL) != 0){
            fprintf(stderr, "errore creazione forchette\n");
            return -1;
        }
    }
    for(int i=0; i<N; i++){
        thargs[i].thid  = (i+1);
        thargs[i].N     = N;
        thargs[i].fork  = forks;
    }

    for(int i=0; i<N; i++){
        if(pthread_create(&th[i], NULL, Filosofo, &thargs[i]) != 0){
            fprintf(stderr, "errore creazione thread\n");
            return -1;
        }
    }
    for(int i=0; i<N; i++){
        if(pthread_join(th[i], NULL) == -1){
            fprintf(stderr, "errore join thread\n");
            return -1;
        }
    }
    free(th);
    free(thargs);
    free(forks);
    return 0;
}