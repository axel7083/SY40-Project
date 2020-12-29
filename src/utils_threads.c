#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <pthread.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdarg.h>
#include "utils_threads.h"

// Wait
void P_threads(Factory *fac, pthread_cond_t *cond) {
    pthread_cond_wait( cond, &fac->mutex);
    pthread_mutex_unlock(&fac->mutex);
}

// Wake up
void V_threads(Factory *fac, pthread_cond_t *cond) {
    pthread_mutex_lock(&fac->mutex);
    pthread_cond_signal(cond);
    pthread_mutex_unlock(&fac->mutex);
}

void init_factory(Factory *fac)
{
    pthread_mutex_init(&fac->mutex,NULL);
    
    pthread_cond_init(&fac->full,NULL);
    pthread_cond_init(&fac->placed,NULL);
    pthread_cond_init(&fac->clock_,NULL);
    pthread_cond_init(&fac->alterned,NULL);
    pthread_cond_init(&fac->finished,NULL);
}


