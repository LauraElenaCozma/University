#include <stdio.h>
#include <stdlib.h>


int * citire(FILE *in,int *n)
{
    int i,*v;
    fscanf(in,"%d",n);
    v=(int)malloc(((*n)+100)*sizeof(int));
    for(i=0;i<(*n);i++)
        fscanf(in,"%d",&v[i]);
    return v;
}

void adaugareelem(int *v,int *n,int t,int k)
{
    int i,j,ok=0;
    for(i=0;i<(*n) && !ok;i++)
        if(v[i]==k)
    {
        for(j=*n-1;j>i;j--)
            v[j+1]=v[j];
        v[i+1]=t;
        (*n)++;
        ok=1;
    }
    if(!ok)printf("Elementul k nu se gaseste in vector");
    else
    {
        printf("Vectorul dupa inserare este:");
        for(i=0;i<(*n);i++)
              printf("%d ",v[i]);
        printf("\n");
    }

}


void adaugarevector(int *v,int *n,int *w,int k,int t)
{

    int i,j,ok=0;
    for(i=0;i<(*n) && !ok;i++)
        if(v[i]==k)
    {
        for(j=*n-1;j>i;j--)
            v[j+t]=v[j];
        for(j=i+1;j<=i+t;j++)
            v[j]=w[j-i-1];
        (*n)+=t;
        ok=1;
    }
    if(!ok)printf("Elementul k nu se gaseste in vector");
    else
    {
        printf("Vectorul dupa inserare este:");
        for(i=0;i<(*n);i++)
              printf("%d ",v[i]);
        printf("\n");
    }

}
int main()
{
    FILE *in=fopen("f.in","r");

    int n,i,k,t,opt,*v;
    fscanf(in,"%d%d",&k,&t);
    v=citire(in,&n);
    printf("Optiunea ta 1-element;2-vector:");
    scanf("%d",&opt);
    if(opt==1)
    {
        adaugareelem(v,&n,t,k);
    }
    else
    {
        int *w;
        w=(int *)malloc(t*sizeof(int));
        printf("Elementele vectorului de inserat sunt:");
        for(i=0;i<t;i++)
            scanf("%d",&w[i]);
        adaugarevector(v,&n,w,k,t);

    }

    return 0;
}
