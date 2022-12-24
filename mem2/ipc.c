#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h> 

#define KEY ((key_t)(1234))
#define SEGSIZE sizeof(char[1000]))

char *ap;

int main () {

int id = shmget (1234, 1000, IPC_CREAT | 0666);

ap = (char*) shmat(id, 0, 0);

sprintf (ap, "Hello World!");

}
