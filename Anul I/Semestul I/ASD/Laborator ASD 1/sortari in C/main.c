#include <stdio.h>
#include <stdlib.h>

int * citire(FILE *in,int *n)
{
    fscanf(in,"%d",n);
    int *v,i;
    v=(int *)malloc((*n)*sizeof(int));
    for(i=0;i<(*n);i++)
        fscanf(in,"%d",&v[i]);
    return v;
}

void bubble(int *v,int n)
{
    int ok=1,p,i;
    while(ok)
    {
        ok=0;
        for(i=0;i<=n-2;i++)
            if(v[i]>v[i+1])
        {
            int aux=v[i];
            v[i]=v[i+1];
            v[i+1]=aux;
            ok=1;
            p=i+1;

        }

        if(p<n-1)n=p;
        else n--;
    }
}

void insertion(int *v,int n)
{
    int i;
    for(i=1;i<n;i++)
    {
        int x=v[i];
        int p=i-1;
        while(p>=0 && v[p]>x)
        {
            v[p+1]=v[p];
            p--;
        }
        v[p+1]=x;
    }
}

void afisare(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
}

int main()
{
    FILE *in=fopen("f.in","r");
    int *v,n;
    v=citire(in,&n);
    insertion(v,n);
    afisare(v,n);
    return 0;
}
