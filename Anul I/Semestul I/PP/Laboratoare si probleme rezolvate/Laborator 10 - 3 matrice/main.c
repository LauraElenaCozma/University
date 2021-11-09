#include <stdio.h>
#include <stdlib.h>

void citire(char *numeFisier,int ***a,int *nrl)
{
    FILE * f;
    f=fopen(numeFisier,"r");

    if(f==NULL)
    {
        printf("Eroare");
        return ;
    }
    int x,i;
    (*nrl)=0;
    (*a)=NULL;
    while(fscanf(f,"%d",&x)==1)
    {
        (*nrl)++;
        int **aux;
        aux=realloc(*a,(*nrl)*sizeof(int *));
        if(aux==NULL)
            break;
        else
        {
           (*a)=aux;
           (*a)[*nrl-1]=(int *)malloc((x+1)*sizeof(int));
           (*a)[*nrl-1][0]=x;
           for(i=1;i<=x;i++)
           {
               int y;
               fscanf(f,"%d",&y);
               (*a)[*nrl-1][i]=y;
           }
        }

    }

    fclose(f);
}

int cmpElement(const void *a,const void *b)
{
    int va=*(int *)a;
    int vb=*(int *)b;
    return va-vb;
}

void sortare_pe_linie(int **a,int n)
{
    int i;
    for(i=0;i<n;i++)
        qsort(a[i]+1,a[i][0],sizeof(int),cmpElement);
}


int cmpLinie(const void *a,const void *b)
{
    int *va=*(int *)a;
    int *vb=*(int *)b;
    int nra=va[0];
    int nrb=vb[0];
    return nra-nrb;
}

void sortare_linii(int **a,int n)
{
    qsort(a,n,sizeof(int *),cmpLinie);
}


void interclasare(int **v,int *n,int **w,int m)
{
    int *z;
    int i=0,j=0,nr=-1;
    while(i<(*n) && j<m)
    {
        if((*v)[i]<(*w)[j])
            z[++nr]=(*v)[i++];
        else z[++nr]=(*w)[j++];
    }
    while(i<(*n))
        z[++nr]=(*v)[i++];
    while(j<m)
        z[++nr]=(*w)[j++];
    int *aux;
    aux=(int *)realloc(*v,(nr+1)*sizeof(int));
    if(aux==NULL)
    {
        printf("Eroare");
        return ;
    }
    else
    {
        (*v)=aux;
        (*n)=nr;
        for(i=0;i<nr;i++)
            (*v)[i]=z[i];
        free(*w);
    }
}

void interclasare_matrice(int ***a,int n)
{
    int i,nr;
    for(i=1;i<n;i++)
    {
        nr=(*a)[0][0];
        interclasare(&(*a)[0],&nr,&(*a)[i],(*a)[i][0]);
        (*a)[0][0]=nr;
    }
}

void afisare(int **a,int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        int x=a[i][0];
        for(j=1;j<=x;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
}
int main()
{
    int **a,n;
    citire("siruri.txt",&a,&n);
//     afisare(a,n);
   sortare_pe_linie(a,n);
//     afisare(a,n);
    sortare_linii(a,n);
    interclasare_matrice(&a,n);
   afisare(a,n);
    return 0;
}
