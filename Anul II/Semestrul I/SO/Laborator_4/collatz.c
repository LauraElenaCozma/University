#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc , char ** argv)
{
	if(argc != 2)
	{
		fprintf(stderr , "Invalid number of arguments\n");
		return -1;
	}
	pid_t pid;

	pid = fork();
	if(pid < 0)
	{
		fprintf(stderr , "Fork failed\n");
		return -1;
	}
	if(pid == 0)
	{
		int n = atoi(argv[1]);
		printf("%d: %d" , n , n);
		while(n != 1)
		{
			if(n % 2 == 0)
				n /= 2;
			else n = 3 * n + 1;
			printf(" %d" , n);
		}

	}
	else
	{
		wait(NULL);
		printf("\nChild %d finished\n" , pid);
	}

	return 0;
}
