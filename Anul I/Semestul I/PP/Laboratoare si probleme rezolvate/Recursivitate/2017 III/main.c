#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
int minim(int x,...)
{
    va_list lista;
    va_start(lista,x);
    int mini=x,y;

    while((y=va_arg(lista,int))!=0)
        if(y<mini)mini=y;
    va_end(lista);
    return mini;

}

int f(int a,int b,int c,int d)
{
    int x=minim(a,b,c,d,0);
    int y=minim(a,b,c,0);
    int z=minim(a,b,0);
    //printf("%d %d %d\n",x,y,z);
    if(d==x && c==y && b==z)return 1;
    return 0;
}
int main()
{
    printf("%d",f(6,9,3,2));
    //printf("%d",minim(4,3,9,0));
    return 0;
}
