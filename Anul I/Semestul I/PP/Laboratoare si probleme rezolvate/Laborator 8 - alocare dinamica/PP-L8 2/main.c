#include <stdio.h>
#include <stdlib.h>

unsigned char octet(int x,int nr)
{
    unsigned char *p;
    p=&x;
    return *(p+nr);
}

int main()
{
    int x;
    scanf("%d",&x);
    int i;
    for(i=0;i<=3;i++)
        printf("%d ",octet(x,i));
    return 0;
}
