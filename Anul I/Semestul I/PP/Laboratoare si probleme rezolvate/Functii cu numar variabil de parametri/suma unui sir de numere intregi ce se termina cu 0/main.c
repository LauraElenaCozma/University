#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int suma(int x,...)
{
    va_list(lista);
    if(x==0)
    {
        va_end(lista);
        return 0;
    }
    else
    {
        va_start(lista,x);
        int y=va_arg(lista,int),s=x;
        while(y!=0)
        {
            s+=y;
            y=va_arg(lista,int);
        }
        va_end(lista);
        return s;

    }

}
int main()
{
    printf("%d",suma(4,7,-2,3,0));
    return 0;
}
