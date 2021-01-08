void P(int index);
void V(int index);
int create_processus ( void *(*f)(void *) );
void log_(char TAG[], char *fmt, ...);
int extract_cmds(int argc, char *argv[]);
int extract_number(int argc, char *argv[], int i);
int isNumber(char *tmp);
void clean_sem();