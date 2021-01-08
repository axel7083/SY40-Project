#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdarg.h>
#include "utils_sem.h"

/*********************************************************************/
/*  Pour Operation P et V 					     */

int sem_id ; //identificateur des sémaphores
struct sembuf sem_oper_P ;  /* Operation P */
struct sembuf sem_oper_V ;  /* Operation V */
 union semun {
	int val;
	struct semid_ds *stat;
	short * array;
} ctl_arg;
/*********************************************************************/

int initsem(key_t semkey) 
{
    
	int status = 0;	

	
    if ((sem_id = semget(semkey, 5, IFLAGS)) > 0) { //Création de 4 sémaphores
		
	    	short array[5] = {0, 0, 0, 0, 0}; //initialisation des sémaphores à 0
	    	ctl_arg.array = array;
	    	status = semctl(sem_id, 0, SETALL, ctl_arg); //Création du tableau de sémaphore
    }
    
    if (sem_id == -1 || status == -1) { 
	    perror("Erreur initsem");
	    return (-1);
    } 
    else 
        return (sem_id);
}
 
void P_sem(int semnum) {
	sem_oper_P.sem_num = semnum; //numero du semaphore
	sem_oper_P.sem_op  = -1 ; //valeur pour modifier le sempaphore
	sem_oper_P.sem_flg = 0 ; //sem_undo ?
	semop(sem_id,&sem_oper_P,1); //effectue l'opération sur le sémaphore
}

void V_sem(int semnum) {
	sem_oper_V.sem_num = semnum;
	sem_oper_V.sem_op  = 1 ;
	sem_oper_V.sem_flg  = 0 ;
	semop(sem_id,&sem_oper_V,1);
}

void clean_sem()
{
	semctl(sem_id, 0, IPC_RMID, ctl_arg);
}
