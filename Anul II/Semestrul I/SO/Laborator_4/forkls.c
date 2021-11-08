#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	pid = fork();

	if(pid < 0)             //an error occured
	{
		fprintf(stderr , "Fork failed\n");
		return -1;
	}

	else if(pid == 0)       //child process
	{
		char *argv[] = {"ls" , NULL};
		execve("/bin/ls" , argv , NULL);
		perror(NULL);

	}
	else                    //parent process
	{
		//parent will wait for the child to complete
		printf("My PID = %d , Child PID = %d\n" , getpid() , pid);
		wait(NULL);
		printf("\nChild %d Complete\n" , pid);
	}
	return 0;
}
