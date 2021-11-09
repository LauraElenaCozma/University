#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmpIntregi(const void *a,const void *b)
{
    int va=*(int *)a;
    int vb=*(int *)b;

    if(va<vb)return -1;
    else if(va>vb)return 1;
    return 0;
}


int cmpSiruri(const void *a,const void *b)
{
    char *va=(char *)a;
    char *vb=(char *)b;
    return strcmp(va,vb);

}

int egal(void *v,void *w,int n,int m,int dim,int (*cmp)(const void *,const void *))
{

    if(n!=m)
        return 0;
    else
    {
        int i;
        char *p,*q;
        p=v;
        q=w;
        for(i=0;i<n;i++)
            if(cmp(p+i*dim,q+i*dim))
                return 0;
        return 1;
    }
}
int main()
{
    char *v[100]={"laura","nu","simte"};
    char *w[100]={"lara","nu","simte"};
    int p[]={4,5,7,2,1};
    int q[]={4,5,7,2,1};
    printf("%d",egal(v,w,3,3,sizeof(char * ),cmpSiruri));
    return 0;
}
