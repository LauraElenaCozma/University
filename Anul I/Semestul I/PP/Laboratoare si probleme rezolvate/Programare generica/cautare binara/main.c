#include <stdio.h>
#include <stdlib.h>

void * cautare_binara(void *v,int n,int dim,const void *x,int (*cmp)(const void *,const void *))
{
    int st=0,dr=n-1;
    char *p=v;
    while(st<=dr)
    {
        int m=(st+dr)/2;
        if(cmp(p+m*dim,x)==0)
            return p+m*dim;
        else if(cmp(p+m*dim,x)<0)
            st=m+1;
        else dr=m-1;
    }
    return NULL;
}

int cmpIntregi(const void *a,const void *b)
{
    int va=*(int *)a;
    int vb=*(int *)b;
    if(va<vb)return -1;
    else if(va>vb)return 1;
    return 0;
}

int main()
{
    int v[]={2,5,6,9,10};
    int x=5;
    int *p;
    p=cautare_binara(v,5,sizeof(int),&x,cmpIntregi);
    printf("%d",(*p));
    return 0;
}
