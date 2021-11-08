#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc , char ** argv)
{
	if(argc < 2)
	{
		fprintf(stderr , "Invalid number of arguments\n");
		return -1;
	}

	for(int i = 1 ; i < argc ; i++)
	{
		pid_t pid = fork();

		if(pid < 0)
		{
			fprintf(stderr , "Fork failed\n");
			return -1;
		}
		else if(pid == 0)
		{
			int n = atoi(argv[i]);
			printf("%d: %d " , n , n);
			while(n != 1)
			{
				if(n % 2 == 0) n /= 2;
				else n = 3 * n + 1;
				printf("%d " , n);
			}
			printf("\n");
			return 0;
		}

	}

	for(int i = 1 ; i < argc ; i++)
		printf("Done Parent %d Me %d\n" , getpid() , wait(NULL));
	return 0;
}
