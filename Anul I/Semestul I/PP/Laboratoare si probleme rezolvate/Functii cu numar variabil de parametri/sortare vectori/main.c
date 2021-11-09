#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void afisare(int v[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
    printf("\n");
}

int cmp(const void *a,const void *b)
{
    int va=*(int *)a;
    int vb=*(int *)b;
    if(va>vb)return -1;
    if(va<vb)return 1;
    return 0;
}


 void sortare(int (*cmp)(const void *a,const void *b),...)
 {
     va_list lista;
     va_start(lista,cmp);

     int n,*v;
     while((n=va_arg(lista,int))!=0)
     {
         v=va_arg(lista,int *);
         qsort(v,n,sizeof(int),cmp);
         afisare(v,n);
     }

     va_end(lista);
 }

int main()
{
    int v[]={3,7,1,8,5};
    int w[]={5,1,8,0,35,7};
    int z[]={-4,6,2,1};

    sortare(cmp,5,v,6,w,4,z,0);
    return 0;
}
