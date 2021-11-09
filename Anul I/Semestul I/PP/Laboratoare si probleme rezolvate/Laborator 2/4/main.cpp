#include <iostream>
#include <cstdio>
using namespace std;
/*
4. Scrieți un program care cuprinde instrucțiunile de mai jos. Afișați valorile lui a și b după fiecare citire, dacă introduceți de la tastatură, pentru fiecare citire, numărul 123. Explicați efectul.
int a,b,c,d;
scanf(“%d”,&a);
scanf(“%1d”,&a);
scanf(“%1d  %*1d  %1d”,&a,&b);

*/
int main()
{
    int a,b,c,d;
    scanf("%d",&a);
    printf("a=%d\n",a);
    scanf("%1d",&a);
    printf("a=%d\n",a);
    scanf("%1d  %*1d  %1d",&a,&b);
    printf("a=%d b=%d\n",a,b);
    return 0;
}
