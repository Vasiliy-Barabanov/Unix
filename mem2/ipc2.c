#include <stdio.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h> 
#include <fcntl.h> 

#define KEY ((key_t)(1234))
#define SEGSIZE sizeof(char[50]))

int main () {

char *ap2;
int id = shmget(KEY, SEGSIZE, 0 | 0666);
if (id < 0) error_rtn(id);
ap2 = (char*) shmat(id, 0, 0);

printf ("shared memory attached value %s\n", ap2);

}
