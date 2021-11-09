#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
int suma(int a,int b)
{
    return a+b;

}

int produs(int a,int b)
{
    return a*b;
}

int rest(int a,int b)
{
    if(b==0)return a;
    return a%b;
}


int (*functie(int x))(int ,int )
{
    if(x==0)return suma;
    if(x==1)return produs;
    return rest;
}

int suma1(int n,...)
{
    va_list lp;
    va_start(lp,n);
    int x,s=0,i;
    for(i=0;i<n;i++)
    {
        x=va_arg(lp,int);
        s+=x;
    }
    va_end(lp);
    return s;
}



int maxim(int n,...)
{
    if(n==0)return 0;
    va_list lp;
    va_start(lp,n);
    int x,i;
    int maxi=va_arg(lp,int);
    for(i=1;i<n;i++)
    {
        x=va_arg(lp,int);
        if(x>maxi)maxi=x;
    }
    va_end(lp);
    return maxi;
}


int (*functie2(int x))(int ,...)
{
    if(x==0)return suma1;
    else return maxim;
}


int main()
{
    int val=functie2(0)(4,42,3,200,4);
    printf("%d\n\n",val);

    printf("%d",functie(100)(3,6));
    int (*tpf[3])(int ,int )={suma,produs,rest} ;
    printf(" %d\n",tpf[1](2,10));

    char s[100];
    scanf("%s",s);
    int x;
    int y;
    sscanf(s,"%d+%d=",&x,&y);


    sprintf(s,"%d+%d=%d",x,y,x+y);

    printf("%s",s);
    return 0;
}
