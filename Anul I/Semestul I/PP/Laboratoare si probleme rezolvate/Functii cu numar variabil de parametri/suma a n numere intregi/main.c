#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int suma(int n,...)
{
    va_list lista;
    va_start(lista,n);

    int i,s=0;
    for(i=0;i<n;i++)
    {
        s+=va_arg(lista,int);
    }
    va_end(lista);
    return s;
}


int main()
{
    printf("%d",suma(5,1,2,0,5,3));
    return 0;
}
