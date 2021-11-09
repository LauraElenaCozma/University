#include <stdio.h>
#include <stdlib.h>

int duplicat(FILE *in,int *n)
{
    int x,i,y;
    fscanf(in,"%d",n);
    fscanf(in,"%d",&x);
    for(i=1;i<(*n);i++)
    {
        fscanf(in,"%d",&y);
        x=(x^y);
    }
    return x;
   //x^x=0, oricare ar fi x. deci elementele egale vor da 2 cate 2 0, iar cel ramas va ajunge in x in urma xorarii
}

int main()
{
    int n,x;
    FILE *in=fopen("f.in","r");
    printf("%d",duplicat(in,&n));
    return 0;
}
