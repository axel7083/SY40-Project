#define IFLAGS (SEMPERM | IPC_CREAT)
#define SKEY   (key_t) IPC_PRIVATE //CLE CREE AU HASARD
#define SEMPERM 0600		 /* Permission */

int initsem(key_t semkey);
void P_sem(int semnum);
void V_sem(int semnum);
