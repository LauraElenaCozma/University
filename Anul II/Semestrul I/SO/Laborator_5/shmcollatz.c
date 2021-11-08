#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc , char ** argv)
{
	if(argc < 2)
	{
		fprintf(stderr , "Invalid number of arguments\n");
		return -1;
	}
	printf("Starting parent %d\n" , getpid());
	char shm_name[] = "myshm";
	int shm_fd;

	shm_fd = shm_open(shm_name , O_CREAT|O_RDWR , S_IRUSR|S_IWUSR);
	if(shm_fd < 0)
	{
		shm_unlink(shm_name);
		perror(NULL);
		return errno;
	}

	size_t page_size = getpagesize();
	size_t shm_size = (argc - 1) * page_size;

	if(ftruncate(shm_fd , shm_size) == -1)
	{
		//shorten or grow the object associated with the file descriptor shm_fd
		perror(NULL);
		shm_unlink(shm_name); //delete the object
		return errno;
	}

	for(int i = 1 ; i < argc ; i++)
	{


		pid_t pid;
		pid = fork();
		if(pid < 0)
		{
			fprintf(stderr , "Fork failed\n");
			return -1;
		}
		else if(pid == 0)
		{
			void *shm_ptr;
      	       	        shm_ptr = mmap(0 , page_size , PROT_WRITE , MAP_SHARED , shm_fd , (i - 1) * page_size);
               	        //shm_ptr indicates to a memory zone of page_size bytes that begin at the (i-1)*page_size byte
	                if(shm_ptr == MAP_FAILED)
    	   	        {
               	 		   perror(NULL);
               	        	   shm_unlink(shm_name);
               		  	   return errno;
                        }
			int n = atoi(argv[i]);
			int * ptr = shm_ptr;
			(*ptr) = n;
			int k = 0;
			while(n != 1 && k < page_size / sizeof(int))
			{
				if(n % 2 == 0)
					n /= 2;
				else n = 3 * n + 1;
				ptr ++;
				k++;
				(*ptr) = n;
			}
			munmap(shm_ptr , page_size);
			return 0;
		}

	}

	for(int i = 1 ; i < argc ; i++)
		printf("Done Parent %d Me %d\n" , getpid() , wait(NULL));

	void * shm_ptr;
	shm_ptr = mmap(0 , shm_size , PROT_READ , MAP_SHARED , shm_fd , 0);

	if(shm_ptr == MAP_FAILED)
	{
		perror(NULL);
		shm_unlink(shm_name);
		return errno;
	}
	for(int i = 1 ; i < argc ; i++)
	{
		int *ptr = (int *)(shm_ptr + (i - 1) * page_size);
 		int k = 0;
		printf("\n%d: ",(*ptr));

		while((*ptr) != 1 && k < page_size / sizeof(int))
		{
			printf("%d " , (*ptr));
			ptr++;
			k++;
		}
		printf("%d ",(*ptr));
	}
	printf("\n");
	munmap(shm_ptr , shm_size);
	shm_unlink(shm_name);
	return 0;
}