#include <stdio.h>
#include <stdlib.h>


/*int palindrom(int x,int ogl)
{
    static int ogl=0;
    static int copie=x;
    if(x!=0)
    {
        ogl=ogl*10+x%10;
        return palindrom(x/10);
    }
    if(x==0)
        if(copie==ogl)return 1;
    return 0;
}*/

int f(int n,int c)
{
    if(n==0)
        return 0;
    else
    {
        int x=f(n/10,c);
        if(n%10==c)return x;
        else return x*10+n%10;
    }
}

int ogl(int n,int o)
{
    if(n==o || n/10==o)return 1;
    else if(n>o)
    {
        return ogl(n/10,o*10+n%10);
    }
    return 0;
}

int main()
{
    printf("%d",ogl(14241,0));
    return 0;
}
