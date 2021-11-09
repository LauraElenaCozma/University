#include <stdio.h>
#include <stdlib.h>
/*
 Scrieți un program care conține declarațiile
float a=67.78; double b=-98.9;
long double c=32.7; long int d=100000;
și apoi afișează liniile de mai jos:
a=+67.8
b=-98.900
c=32.70
d=100000

*/
int main()
{
    float a=67.78;
    double b=-98.9;
    long double c=32.7;
    long int d=100000;
    printf("%+.1lf\n",a);
    printf("%.3lf\n",b);
    //printf("%.2lf\n",c);     ?????
    printf("%d",d);
    return 0;
}
