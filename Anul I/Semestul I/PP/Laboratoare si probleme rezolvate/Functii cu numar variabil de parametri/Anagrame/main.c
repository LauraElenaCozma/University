#include <stdio.h>
#include <stdlib.h>

int anagrame(char *x,char *y)
{
    if(!x[0] && !y[0])return 1;
    if(strlen(x)!=strlen(y))return 0;

    char *p=strchr(y,x[0]);
    if(p==NULL)return 0;
    strcpy(p,p+1);
    return anagrame(x+1,y);
}


int main()
{
    char a[20],b[20];
    scanf("%s %s",a,b);
    int x=anagrame(a,b);
   printf("%d",x);
   //char x[]="amicitie";
   //char *p=x+2;
   //strcpy(p,"anal");
   //printf("%s",x);
    return 0;
}
