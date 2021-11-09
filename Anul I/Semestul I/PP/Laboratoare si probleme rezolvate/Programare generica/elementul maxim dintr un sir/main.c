#include <stdio.h>
#include <stdlib.h>

int cmpIntregi(const void *a,const void *b)
{
    int va=*(int *)a;
    int vb=*(int *)b;
    if(va<vb)return -1;
    else if(va>vb)return 1;
    return 0;
}

void * maxim(void *v,int n,int dim,int (*cmp)(const void *,const void *))
{
    ///ATENTIE
    if(n==0)return NULL;
    int i;
    void *maxim;
    char *p;
    p=v;
    maxim=p;

    for(i=1;i<n;i++)
        if(cmp(p+i*dim,maxim)>0)
           maxim=p+i*dim;
   return maxim;
}

int cmpSiruri(const void *a,const void *b)
{
    return strcmp(*(char **)a,*(char **)b);
}
int main()
{
    char *v[100]={"laura","simte","caldura","soarelui"};
    int x=(char **)(maxim(v,0,sizeof(char *),cmpSiruri));
    printf("%d",x);
    return 0;
}
