#include <stdio.h>
#include <stdlib.h>

void construire_par(int *v,int n,int **w,int *m)
{
    (*w)=NULL;
    (*m)=0;
    int i;
    for(i=0;i<(n);i++)
        if(v[i]%2==0)
    {
        int *aux;
        aux=realloc(*w,((*m)+1)*sizeof(int));

        if(aux==NULL)
        {
            free((*w));
            return 0;
        }

        (*w)=aux;
        (*w)[(*m)]=v[i];
        (*m)++;

    }
}
/*
add(w,m,1);
construire_par(w,m,&n,&n);
add(v,n,-1);
multiply(v,n,-1);
sort(v,n);
multiply(v,n,-1);
display(v,n);

*/

void afisare(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
}

int main()
{
    int v[]={4,3,7,34,6,7,1},*w,n;
    construire_par(v,7,&w,&n);
    afisare(w,n);

    return 0;
}
