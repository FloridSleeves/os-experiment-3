#include<stdio.h>
#include<sys/shm.h>
#include<sys/stat.h>
int main()
{
	int segment_id;
	char* shared_memory;
	
	struct shmid_ds shmbuffer;//a struct to record the information of the shared memory
	int segment_size;
	const int shared_segment_size=0x6400;
	
	segment_id=shmget(IPC_PRIVATE,shared_segment_size,
		IPC_CREAT | IPC_EXCL |S_IRUSR |S_IWUSR);
	shared_memory=(char*)shmat(segment_id,0,0);
	printf("shared memory attached at address %p\n",shared_memory);
	shmctl(segment_id,IPC_STAT,&shmbuffer);
	segment_size=shmbuffer.shm_segsz;
	printf("segment size:%d\n",segment_size);
	sprintf(shared_memory,"Hello,world.");//write something into shared memory
	shmdt(shared_memory);//detached from the memory

	shared_memory=(char*)shmat(segment_id,(void*)0x5000000,0);
	//attach the memory at another address
	printf("shared memory reattached at address %p\n",shared_memory);
	printf("%s\n",shared_memory);
	shmdt(shared_memory);//detach
	shmctl(segment_id,IPC_RMID,0);//deallocate
	return 0;

	


}
