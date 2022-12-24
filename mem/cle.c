#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>

int main () 
{
	int segment_id;
	char* shared_memory_2;
	struct shmid_ds shmbuffer;
	int segment_size;
	const int shared_segment_size = 1000;
	segment_id = shmget (IPC_PRIVATE, shared_segment_size, 0);
	shared_memory_2 = (char*) shmat (segment_id, 0, 0); 
	printf ("ylylyl%s\n", shared_memory_2); 
	shmdt (shared_memory_2);  
}
