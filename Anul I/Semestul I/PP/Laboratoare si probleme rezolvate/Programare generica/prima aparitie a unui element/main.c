#include <stdio.h>
#include <stdlib.h>

int cmpIntregi(const void *a,const void *b)
{
    int va=*(int *)a;
    int vb=*(int *)b;
    if(va<vb)return -1;
    if(va>vb)return 1;
    return 0;
}

void * prima_aparitie(const void *x,void *v,int n,int dim,int (*cmp)(const void *,const void *))
{
    char *p;
    p=v;
    int i;
    for(i=0;i<n;i++)
    {
        if(cmp(p+i*dim,x)==0)return p+i*dim;
    }
    return NULL;
}


void aparitii(int *v,int n,int x)
{
    int *p,ok=0;
    int *vinit=v;
    while((p=prima_aparitie(&x,vinit,n,sizeof(int),cmpIntregi))!=NULL)
    {
        printf("%d %d\n",p,v);
        ok=1;
        printf("%d ",(int)(p-v));
        n=n-((p-vinit)+1);
        vinit=p+1;

    }
    if(ok==0)printf("Nu exista");
}

int main()
{
    int v[]={3,7,1,7,4,2,7,4,7};
    int x=4;
    //printf("%d %d",v,prima_aparitie(&x,v,9,sizeof(int),cmpIntregi));
    aparitii(v,9,2);
    return 0;
}
