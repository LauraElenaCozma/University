#include <stdio.h>
#include <stdlib.h>

/*
1. Scrieți un program care conține declarația
int a=-12;
și apoi afișează liniile de mai jos:
a=-12
a=0000012
a=-0000012
a=fffffff4
a=FFFFFFF4
a=37777777764
a=4294967284


*/

int main()
{
    int a=-12;
    printf("a=%d\n",a); //intreg
    printf("a=%7.7d\n",a);
    //nu am gasit inca forma corecta
    printf("a=%x\n",a); //a in hexadecimal
    printf("a=%X\n",a); //a in hexadecimal cu litere mari
    printf("a=%o\n",a);  //a in octal - baza 8
    printf("a=%u\n",a); //intreg zecimal fara semn


    return 0;
}
