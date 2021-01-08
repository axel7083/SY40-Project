#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "utils_threads.h"
#include "utils_sem.h"
#include "global_vars.h"

pthread_cond_t* getCond(int index)
{
    switch(index)
    {
        case 0:
            return &factory->full;
        break;
        case 1:
            return &factory->placed;
        break;
        case 2:
            return &factory->clock_;
        break;
        case 3:
            return &factory->alterned;
        break;
        case 4:
            return &factory->finished;
        break;
    }
}

void P(int index) {
    if(isProcessus)
        P_sem(index);
    else
        P_threads(factory,getCond(index));
}

void V(int index) {
    if(isProcessus)
        V_sem(index);
    else
        V_threads(factory,getCond(index));
}

int create_processus ( void *(*f)(void *) ) {
	int pid = fork();
    if (! pid) {
        (*f)(NULL);
        exit(0);
    }
	return pid;
}

void log_(char TAG[], char *fmt, ...)
{
    int id;
    if(isProcessus)
        id = getpid();
    else
        id =  pthread_self();
        
    printf("\n[%s][%d] ", TAG, id);
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;
    va_start(ap, fmt);
    for (p = fmt; *p; p++)
    {
        if (*p != '%')
        {
            putchar(*p);
            continue;
        }
       switch (*++p)
        {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
            break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
            break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            default:
                putchar(*p);
            break;
        }
    }
    va_end(ap); /*clean up when done */
    fflush(stdout);
}

int isNumber(char *tmp)
{
    int isDigit = 0;
    int j=0;
    while(j<strlen(tmp) && isDigit == 0){
        isDigit = isdigit(tmp[j]);
        j++;
    }
    
    return isDigit;
}

char TAG[] = "Info";

int extract_number(int argc, char *argv[], int i)
{
    if(argc <= i+1)
    {
        log_(TAG,help_msg,argv[0]);
        exit(1);
    }
            
    if(isNumber(argv[i+1])) {
        int nb = atoi(argv[i+1]);
        if(nb == 0)
        {
            log_(TAG,"Number cannot be 0");
            exit(1);
        }
        return nb;
    }
    else
    {
        log_(TAG,"Please provide a valid number");
        exit(1);
    }
}

int extract_cmds(int argc, char *argv[]) {
    
    int skipNext = 0;
    
    for(int i = 1; i < argc; i ++)
    {
        if(skipNext)
        {
            skipNext = 0;
            continue;
        }
    
        if(strcmp(argv[i],"-h") == 0 || strcmp(argv[i],"--help") == 0)
        {
            log_(TAG,help_msg,argv[0]);
            exit(0);
        }
        else if(strcmp(argv[i],"--version") == 0)
        {
            log_(TAG,"Version %s",version);
            exit(0);
        }
        else if(strcmp(argv[i],"-t") == 0)
        {
            log_(TAG,"Running using Threads and Monitors");
            isProcessus = 0;
        }
        else if(strcmp(argv[i],"-v") == 0 || strcmp(argv[i],"--verbose") == 0)
        {
            log_(TAG,"Running verbose");
            isDebug = 1;
        }
        else if(strcmp(argv[i],"-g1") == 0)
        {
            skipNext = 1;
            goal_1 = extract_number(argc, argv, i);
            log_(TAG,"g1 = %d",goal_1);
        }
        else if(strcmp(argv[i],"-g2") == 0)
        {
            skipNext = 1;
            goal_2 = extract_number(argc, argv, i);
            log_(TAG,"g2 = %d",goal_2);
        }
        else
        {
            log_(TAG,"Invalid arg %s",argv[i]);
        }
    }
    
}
