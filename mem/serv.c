#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <unistd.h>

int main () 
{
	int segment_id;
	char* shared_memory;
	struct shmid_ds shmbuffer;
	int segment_size;
	const int shared_segment_size = 1000;
	segment_id = shmget (IPC_PRIVATE, shared_segment_size, IPC_CREAT);
	shared_memory = (char*) shmat (segment_id, 0, 0); /* Attach the shared memory segment. */
	sprintf (shared_memory, "Hello, world.");
	sleep(10); 
	shmdt (shared_memory);  
}
