#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

void * reverse(void * v)
{
	char * s = (char *)v;
	int length = strlen(s);

	char *result = (char *)malloc(length * sizeof(char));

	if(result == NULL)
	{
		fprintf(stderr , "Lack of memory\n");
		return NULL;
	}

	int pos = 0;
	for(int i = length - 1 ; i >= 0 ; i--)
		result[pos++] = s[i];
	result[pos]='\0';

	return result;
}

int main(int argc , char **argv)
{
	if(argc != 2)
	{
		fprintf(stderr , "Invalid number of arguments\n");
		return -1;
	}

	pthread_t thr;

	if(pthread_create(&thr , NULL , reverse , argv[1]))
	{
		perror(NULL);
		return errno;
	}
	char * result;

	if(pthread_join(thr , &result))
	{
		perror(NULL);
		return errno;
	}
	printf("%s \n" , result);
	free(result);
	return 0;
}
