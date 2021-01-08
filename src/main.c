#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdarg.h>
#include "utils.h"
#include "utils_sem.h"
#include "utils_threads.h"

int goal_1 = 1;
int goal_2 = 1;
int isProcessus = 1;
int isDebug = 0;

// Processus Bocal_2
void* Bocal_2(void *arg) {

    int count = 0;
    char TAG[] = "Bocal_2";
        
    while(count < goal_2) {
        if(count < goal_1) //If the goal of bocal is not reached
            P(3);
        log_(TAG, "Put one");
        for(int i = 0 ; i < 2 ; i++) {
            V(1);
            P(0);  
        }
        log_(TAG, "Remove one");
        count++;
        V(3);
    }
    V(4); // Finish
}

// Processus Bocal
void* Bocal(void *arg) {
    int count = 0;
    char TAG[] = "Bocal";
    while(count < goal_1) {
        log_(TAG, "Put one");
        V(1);
        P(0);
        log_(TAG, "Remove one");
        count++;
        if(count-1 < goal_2) { //If the goal of bocal_2 is not reached
            V(3);
            P(3);   
            sleep(1);
        }
    }
    V(3);
    V(4); // Finish
}

// Processus Valve
void* Valve(void *arg) {
    char TAG[] = "Valve";
    while(1) {
        P(1);
        log_(TAG, "Open");
        V(2);
        sleep(1);
        P(2);
        log_(TAG, "Close");
        V(0);
    }
}

// Processus Horloge
void* Horloge(void *arg) {
    char TAG[] = "Horloge";
    while(1) {
        P(2);
        log_(TAG, "Sleeping 10s");
        sleep(10);
        V(2);
        sleep(1); //reset time
    }
}


void setup_processus()
{
    int i,semid; //Semid : identificateur des sémaphores
    initsem(SKEY); //On initialise le tableau de sémaphores

    int pid_clock = create_processus(Horloge);
    int pid_valve = create_processus(Valve);
    create_processus(Bocal_2);
    create_processus(Bocal);
    
    P(4); // Wait one of the processus finish
    P(4); // **
	clean_sem();
	kill(pid_clock, SIGQUIT);
	kill(pid_valve, SIGQUIT);	
}

void setup_threads()
{
    factory = (Factory*) malloc(sizeof(Factory));
    init_factory(factory);
    
    pthread_create(&(tid[0]), NULL, &Horloge,NULL);
    pthread_create(&(tid[1]), NULL, &Valve,NULL);
    pthread_create(&(tid[2]), NULL, &Bocal_2,NULL);
    sleep(1);
    pthread_create(&(tid[3]), NULL, &Bocal,NULL);
    
    pthread_detach(tid[0]);
    pthread_detach(tid[1]);
    pthread_detach(tid[2]);
    pthread_detach(tid[3]);
    
    P(4); // Wait one of the processus finish
    P(4); // **
}

int main(int argc, char *argv[])
{
    char TAG[] = "Main";
    extract_cmds(argc,argv);
    
    if(isProcessus)
        setup_processus();
    else
        setup_threads();

    log_(TAG,"All goals reached.\n");
    return(0);
}




