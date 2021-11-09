#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>




int aparitie(int x,int n,...)
{
    va_list lista;
    va_start(lista,n);

    int i,k=0;
    for(i=0;i<n;i++)
    {
        int y=va_arg(lista,int);
        if(x==y)k++;
    }
    va_end(lista);
    return k;
}


int main()
{
    printf("%d",aparitie(3,6,1,6,2,3,7,3));
    return 0;
}
