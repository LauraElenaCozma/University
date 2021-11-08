#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#define MAX_RESOURCES 5

pthread_mutex_t mtx;
int available_resources = MAX_RESOURCES;

int decrease_count(int count)
{
	pthread_mutex_lock(&mtx);
	if(available_resources < count)
	{
		pthread_mutex_unlock(&mtx);
		return -1;
	}
	else
	{
		available_resources -= count;
		printf("Got %d resources %d remaining\n" , count , available_resources);
		pthread_mutex_unlock(&mtx);
		return 0;
	}
}



void increase_count(int count)
{
	pthread_mutex_lock(&mtx);
	available_resources += count;
	printf("Released %d resources %d remaining\n" , count , available_resources);
	pthread_mutex_unlock(&mtx);
}

void * solve ( void * v)
{
	int count = *(int *)v;

	while(decrease_count(count) == -1) //we don't have enough resources
		increase_count(count);
	return NULL;
}
int main()
{

if(pthread_mutex_init(&mtx , NULL))
{
	perror(NULL);
	return errno;
}

printf("MAX_RESOURCES = %d\n" , MAX_RESOURCES);

int count;
pthread_t thr[MAX_RESOURCES];

for(int i = 0 ; i < MAX_RESOURCES ; i++)
{
	count = rand() % (MAX_RESOURCES + 1); //we can get 0 or the maximum number of resources
	if(pthread_create(&thr[i] , NULL , solve , &count))
	{
		perror(NULL);
		return errno;
	}
}

for(int i = 0 ; i < MAX_RESOURCES ; i++)
	pthread_join(thr[i] , NULL);

pthread_mutex_destroy(&mtx);
 return 0;
}
