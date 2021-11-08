#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

int NTHRS = 5;
sem_t sem;
pthread_mutex_t mtx;
int number_threads_passed = 0;

int barrier_point()
{
	pthread_mutex_lock(&mtx);
	number_threads_passed ++;
	pthread_mutex_unlock(&mtx);

	if(number_threads_passed == NTHRS)
	{
		if(sem_post(&sem))
		{
			perror(NULL);
			return errno;
		}
	}
	if(sem_wait(&sem))
	{
		perror(NULL);
		return errno;
	}
	if(sem_post(&sem))
	{
		perror(NULL);
		return errno;
	}
}

void * tfun(void * v)
{
	int *tid = (int *)v;
	printf("%d reached the barrier\n" , *tid);
	barrier_point();
	printf("%d passed the barrier\n" , *tid);
	free(v);
        return NULL;
}


int main()
{

if(pthread_mutex_init(&mtx , NULL))
{
	perror(NULL);
	return errno;
}

if(sem_init(&sem , 0 , 0))
{
	perror(NULL);
	return errno;
}

printf("NTHRS = %d\n" , NTHRS);
pthread_t thr[NTHRS];

for(int i = 1 ; i<=NTHRS ; i++)
{
	int * index = (int *) malloc(sizeof(int));

	if(index == NULL)
	{
		fprintf(stderr , "Lack of memory\n");
		return -1;
	}

	(*index) = i;

	if(pthread_create(&thr[i - 1] , NULL , tfun , index))
	{
		perror(NULL);
		return errno;
	}
}

for(int i = 1 ; i <= NTHRS ; i++)
{
	if(pthread_join(thr[i - 1] , NULL))
	{
		perror(NULL);
		return errno;
	}
}
pthread_mutex_destroy(&mtx);
sem_destroy(&sem);
return 0;
}