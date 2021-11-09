#include <stdio.h>
#include <stdlib.h>


void citire(int ***a,int *nrl,int *nrc)
{
    scanf("%d",nrl);
    scanf("%d",nrc);

    (*a)=(int **)malloc((*nrl)*sizeof(int *));

    int i,j;
    for ( i = 0; i < *nrl ; i++)
    {
        (*a) [i] = (int *)malloc((*nrc) * sizeof(int));

        for(j=0;j<*nrc;j++)
        {
            scanf("%d",&(*a)[i][j]);
        }
    }
}



void nrZU(int **a,int nrl,int nrc,int *zero,int *unu)
{

    (*zero) = 0;
    (*unu) = 0;

    int i,j;
    for ( i = 0; i < nrl ; i++)
        for(j = 0; j< nrc ; j++)
    {
        if(a[i][j]==0)
            (*zero)++;
        else if(a[i][j]==1)
            (*unu)++;
    }
}


void binar(int **a,int nrl,int nrc)
{
    int zero,unu;
    nrZU(a,nrl,nrc,&zero,&unu);
    printf("%d %d\n",zero,unu);

    if((zero+unu)==(nrl*nrc))
        printf("e binara");
    else printf("nu e binara");
}


void afisare(int **a,int nrl,int nrc)
{
    int i,j;
    for ( i = 0; i < nrl ; i++)
    {
        for(j = 0; j< nrc ; j++)
            printf("%d " , a[i][j]);
        printf("\n");
    }
    printf("\n");
}
int main()
{
    int **a,nrl,nrc;
    citire(&a,&nrl,&nrc);
    afisare(a,nrl,nrc);
    binar(a,nrl,nrc);


    int i;
    for(i=0;i<nrl;i++)
        free(a[i]);
    free(a);
    return 0;
}
