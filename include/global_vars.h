#ifndef GLOB_VARS_H
#define GLOB_VARS_H 

extern int goal_1;
extern int goal_2;
extern int isProcessus;
extern int isDebug;
static char help_msg[] = "\
Usage %s\
\n  -t              , run the demo using threads and monitors. (Default use semaphores and processus)\
\n  -v, --verbose   , explain what is being done\
\n  -g1 [VALUE]     , number of small jar to produce (Default 1)\
\n  -g2 [VALUE]     , number of big jar to produce (Default 1)\
\n  -h, --help      , display this help and exit\
\n      --version   , output version information and exit\n";
static const char version[] = "1.0";

#endif 


