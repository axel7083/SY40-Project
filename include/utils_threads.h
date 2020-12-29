typedef struct Factory {
        pthread_mutex_t mutex;
        pthread_cond_t full;
        pthread_cond_t placed;
        pthread_cond_t clock_;
        pthread_cond_t alterned;
        pthread_cond_t finished;
} Factory;

Factory *factory; // Structure ONLY used when using threads.
pthread_t tid[4];

void P_threads(Factory *fac, pthread_cond_t *cond);
void V_threads(Factory *fac, pthread_cond_t *cond);
void init_factory(Factory *fac);
