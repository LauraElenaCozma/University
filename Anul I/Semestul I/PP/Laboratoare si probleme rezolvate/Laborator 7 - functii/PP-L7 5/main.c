#include <stdio.h>
#include <stdlib.h>

int modificare(int x,int c)
{
    if(x==c){printf("Nu a mai ramas nimic din numar\n");return ;}
    else
    {
    if(x==0) return 0;
    int nr=0,p=1;
    while(x)
    {
        int cif=x%10;
        if(cif!=c)
        {
            nr=nr+cif*p;
            p*=10;
        }
        x/=10;
    }
    return nr;
    }
}
int main()
{
    printf("%d",modificare(2,2));
    return 0;
}
