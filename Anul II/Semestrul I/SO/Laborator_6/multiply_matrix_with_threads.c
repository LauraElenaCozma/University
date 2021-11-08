#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

_Bool createMatrix(int ***a , int m , int n)
{
	(*a) = (int **)malloc(m * sizeof(int *));

	if((*a) == NULL)
	{
		fprintf(stderr , "Lack of memory\n");
		return 0;
	}
	for(int i = 0 ; i < m ; i++)
	{
		(*a)[i] = (int *)malloc(n * sizeof(int));

		if((*a)[i] == NULL)
		{
			fprintf(stderr , "Lack of memory\n");
			return 0;
		}
	}

	for(int i = 0 ; i < m ; i++)
		for(int j = 0 ; j < n ; j++)
			(*a)[i][j] =  rand() % 20;
	return 1; //success

}

void printMatrix(int **a , int m , int n)
{
	for(int i = 0 ; i < m ; i++)
	{
		for(int j = 0 ; j < n ; j++)
		{
			printf("%d " , a[i][j]);
		}
		printf("\n");
	}
	printf("\n");}

int **a , **b , **c;
void * multiply_matrix(void *v)
{
	int *ptr = (int *)v;
	int poz_i = ptr[0];
	int poz_j = ptr[1];
	int n = ptr[2];
	free(v);

	int *sum = (int *) malloc(sizeof(int));

	if(sum == NULL)
	{
		fprintf(stderr , "Lack of memory\n");
		return NULL;
	}
	(*sum) = 0;
	for(int k = 0 ; k < n ; k++)
		(*sum) += a[poz_i][k] * b[k][poz_j];
	return sum;
}
int main(int argc , char ** argv)
{
	//we pass as parameters the dimensions of matrix a = m * n and b = n * t
	if(argc != 4)
	{
		fprintf(stderr , "Invalid number of arguments\n");
		return -1;
	}
	int m = atoi (argv[1]);
	int n = atoi (argv[2]);
	int t = atoi (argv[3]);


	if(!createMatrix(&a , m , n) || !createMatrix(&b , n , t) || !createMatrix(&c , m  , t))
	{
		fprintf(stderr , "Error at creating the matrix");
		return -1;
	}
	
	printMatrix(a ,m , n);
	printMatrix(b , n , t);

	pthread_t thr[m][t];
	
	for(int i = 0 ; i < m ; i++)
		for(int j = 0 ; j < t ; j++)
			{
				int *point = (int *) malloc(3 * sizeof(int));
			 	
				if(point == NULL)
				{
					fprintf(stderr , "Lack of memory\n");
					return -1;
				}
				point[0] = i;
				point[1] = j;
				point[2] = n;
				if(pthread_create(&thr[i][j] , NULL , multiply_matrix , point))
				{
					perror(NULL);
					return errno;
				} 
			}
	for(int i = 0 ; i < m ; i++)
		for(int j = 0 ; j < t ; j++)
		{
			void *result;

			if(pthread_join(thr[i][j] , &result))
			{
				perror(NULL);
				return errno;
			}

			c[i][j] =(*(int *)result);
			free(result);
		}

	printMatrix(c , m , t);
	for(int i = 0 ; i < m ; i++)
		{
			free(a[i]);
			free(c[i]);
		}
	free(a);
	free(c);

	for(int i = 0 ; i < n ; i++)
		free(b[i]);
	free(b);
	return 0;
}
