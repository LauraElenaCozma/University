#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


void citire_si_val_max(int ***a,int *m,int *n,int *maxi,char *numeFisier)
{
    FILE *f;
    f=fopen(numeFisier,"r");

    if(f==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }
    fscanf(f,"%d%d",m,n);
    (*a)=(int **)malloc((*n)*sizeof(int *));
    (*maxi)=INT_MIN;

    int i,j;
    for(i=0;i<*n;i++)
    {
        (*a)[i]=(int *)malloc((*m)*sizeof(int));
        for(j=0 ; j< *m ; j++)
        {
            fscanf(f,"%d",&(*a)[i][j]);
            if((*a)[i][j]>*maxi)(*maxi)=(*a)[i][j];
        }

    }
}


void pozitii_max(int **a,int m,int n,int maxi)
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
          if(a[i][j]==maxi)
             printf("(%d,%d)  ",i,j);
}



void afisare(int **a,int m,int n)
{
    int i,j;
    for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
                printf("%d ",a[i][j]);
            printf("\n");
        }
    printf("\n");
}


void suma(int **a,int m,int n)
{
    int i,j;
    for(i=0;i<n;i++)
        {
            int s=0;
            for(j=0;j<m;j++)
                s+=a[i][j];
            printf("%d ",s);
        }
}


void rotire(int ***a,int m,int n)
{
    int **b;
    b=(int **)malloc(m*sizeof(int *));
    int **aux1;
    aux1=realloc(*a,sizeof(int *)*m);
    if(aux1==NULL)return -1;
    *a=aux1;
    int i,j;
    for(i=0;i<m;i++)
    {
        b[i]=malloc(n*sizeof(int));
        int *aux2;
        aux2=realloc((*a)[i],n*sizeof(int));
        if(aux2==NULL)return -1;
        (*a)[i]=aux2;
        for(j=0;j<n;j++)
            b[i][j]=(*a)[j][m-i-1];
    }

    (*a)=b;
}

int cmpColoana(const void *a,const void *b)
{
    int va=*(int *)a;
    int vb=*(int *)b;
    return (va-vb);
}
void sortare(int **a,int m,int n)
{
    int i;
    for(i=0;i<n;i++)
        qsort(a[i],m,sizeof(int),cmpColoana);

}


int main()
{
    int **a,**b,m,n,maxi;
    citire_si_val_max(&a,&m,&n,&maxi,"matrice.txt");


    rotire(&a,m,n);
    afisare(a,n,m);
    sortare(a,n,m);
    afisare(a,n,m);

    //pozitii_max(a,m,n,maxi);
    //printf("\n");
    //suma(a,m,n);

    return 0;
}
