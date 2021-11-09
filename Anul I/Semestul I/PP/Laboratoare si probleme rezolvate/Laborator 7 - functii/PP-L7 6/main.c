#include <stdio.h>
#include <stdlib.h>


/*void afisare(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",*(v+i));
    printf("\n");
}*/


void permutVector(int *v,int n,int m)
{
    int i,x,y;
    x=v[0];
    i=0;
    int N=n;
    while(n)
    {
        int poz=(i+m)%N;
       // printf("x=%d i=%d poz=%d\n",x,i,poz);
        i=v[poz];
        v[poz]=x;
        x=i;
        i=poz;
        n--;
    }

}

void citire(int ***a,int *n,char *numeFisier)
{
    FILE *fin;

    fin=fopen(numeFisier,"r");
    fscanf(fin,"%d",n);

    if(fin==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }


    (*a)=(int **)malloc((*n)*sizeof(int *));

    int i,j;
    for(i=0;i<(*n);i++)
        {
            (*a)[i]=malloc((*n)*sizeof(int));
            for(j=0;j<*n;j++)
                fscanf(fin,"%d",&(*a)[i][j]);

        }
    fclose(fin);
}


void afisare(int **a,int n)
{
     int i,j;
     for(i=0;i<n;i++)
     {
         for(j=0;j<n;j++)
            printf("%d ",a[i][j]);
        printf("\n");
     }

}

void permutMatrice(int **a,int n)
{
    int i;
    for(i=0;i<n;i++)
        permutVector(a[i],n,i);
}

int main()
{
    int **a,n;
    citire(&a,&n,"f.in");
    afisare(a,n);
    printf("\n");
    permutMatrice(a,n);
    afisare(a,n);
    return 0;
}
