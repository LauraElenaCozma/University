#include <stdio.h>
#include <stdlib.h>


void matrice(int ***a,int n)
{
     (*a)=(int **)malloc(n*sizeof(int *));
     int i,j;
     for( i=0;i<n;i++)
     {(*a)[i]=(int *)malloc((i+1)*sizeof(int));
       (*a)[i][0]=i+1;
     }
     for(i=1;i<n;i++)
        (*a)[n-1][i]=n-i;
     for(i=n-2;i>=1;i--)
        for(j=1;j<=i;j++)
        (*a)[i][j]=(*a)[i][j-1]+(*a)[i+1][j]+(*a)[i+1][j-1];
}

void afisare(int **a,int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {for(j=0;j<=i;j++)
         printf("%d ",a[i][j]);
    printf("\n");
    }
}
int main()
{
    int **a;
    matrice(&a,7);
    afisare(a,7);
    return 0;
}
