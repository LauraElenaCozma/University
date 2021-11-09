#include <stdio.h>
#include <stdlib.h>

//verifica daca e little sau big endian

int main()
{
    unsigned char *p;
    int x=1;
    p=&x;
    if((*p)==1)printf("Little-endian");
    else printf("Big-endian");
    return 0;
}
