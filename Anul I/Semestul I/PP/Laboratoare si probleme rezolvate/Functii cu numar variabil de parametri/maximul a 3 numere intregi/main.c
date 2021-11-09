#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int maxim(int n,...)
{
    va_list(lista);
    va_start(lista,n);
    int i,maxi,x;
    maxi=va_arg(lista,int);
    for(i=0;i<n-1;i++)
    {
        x=va_arg(lista,int);
        if(x>maxi)maxi=x;

    }
    va_end(lista);
    return maxi;
}

int main()
{
    printf("%d",maxim(7,1,0,-4,3,8,-2,8));
    return 0;
}
