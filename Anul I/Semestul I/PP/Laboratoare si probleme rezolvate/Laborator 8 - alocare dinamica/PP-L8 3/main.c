#include <stdio.h>
#include <stdlib.h>


void citireMatrice(int ***a,int *n,char *numeFisier)
{
    FILE *fin;

    fin=fopen(numeFisier,"r");

    if(fin==NULL)
    {
        printf("\nProbleme la deschiderea fisierului\n");
        return ;
    }
    fscanf(fin,"%d",n);
    (*a)=(int **)malloc((*n)*sizeof(int *));
    int i,j;
    for(i=0;i<*n;i++)
    {
        (*a)[i]=malloc((*n)*sizeof(int));
        for(j=0;j<*n;j++)
           fscanf(fin,"%d",&(*a)[i][j]);
    }


}


void afisareMatrice(int **a,int n)
{
    printf("\n\n");
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
           printf("%d ",a[i][j]);
        printf("\n");
    }
}


int elemMijloc(int **a,int n)
{
    return a[n/2][n/2];
}

void elemDiagonale(int **a,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",a[i][i]);
    printf("\n");
    for(i=0;i<n;i++)
        printf("%d ",a[i][n-i-1]);
}


void interschimbareLinii(int **a,int n,int i,int j)
{
    int k;
    for(k=0;k<n;k++)
    {
        int aux=a[i][k];
        a[i][k]=a[j][k];
        a[j][k]=aux;
    }

}


int main()
{
    int **a,n;

    citireMatrice(&a,&n,"f.in");
    afisareMatrice(a,n);

    printf("\nElementul de la intersectia diagonalelor este %d\n",elemMijloc(a,n));

    printf("\nElementele de pe diagonale sunt:\n");
    elemDiagonale(a,n);

    interschimbareLinii(a,n,0,4);
    afisareMatrice(a,n);
    return 0;
}
