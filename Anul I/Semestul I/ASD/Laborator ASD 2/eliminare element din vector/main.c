#include <stdio.h>
#include <stdlib.h>

int * citire(FILE *in,int *v,int *n)
{
    int i;
    fscanf(in,"%d",n);
    v=(int)malloc((*n)*sizeof(int));
    for(i=0;i<(*n);i++)
        fscanf(in,"%d",&v[i]);
    return v;
}

void elim1(int *v,int *n,int k)
{
    //functia va elimina prima aparitie a elementului k
    int i,j,ok=0;
    for(i=0;i<(*n) && !ok;i++)
         if(v[i]==k)           //am gasit elementul
         {
             for(j=i+1;j<(*n);j++)
                v[j-1]=v[j];
             (*n)--;
              ok=1;
         }
     //afiseaza vectorul dupa eliminare
    if(!ok)//nu s-a rea;ozat nicio eliminare
        printf("Elementul nu se gaseste in vector\n");
    else
    {
        printf("Vectorul dupa eliminarea primei aparitii a lui k:");
        for(i=0;i<(*n);i++)
              printf("%d ",v[i]);
        printf("\n");
    }

}

void elimtot(int *v,int *n,int k)
{
    int i,j,ok=0;
    for(i=0;i<(*n);i++)
        if(v[i]==k)
    {
        for(j=i+1;j<(*n);j++)
            v[j-1]=v[j];
        (*n)--;
        i--;
        ok=1;
    }
    if(!ok)printf("Elementul nu se gaseste in vector");
    else
    {
    printf("Vectorul dupa eliminarea tuturor aparitiilor ale lui k:");
    for(i=0;i<(*n);i++)
        printf("%d ",v[i]);
    printf("\n");
    }
}

int main()
{
    int *v;
    FILE *in=fopen("f.in","r");
    int n,i,k;
    printf("Elementul de eliminat este:");
    scanf("%d",&k);
    v=citire(in,v,&n);
    elim1(v,&n,k);
    elimtot(v,&n,k);
    return 0;
}
