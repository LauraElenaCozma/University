#include <stdio.h>
#include <stdlib.h>


void citire(long long int **v,int *n)
{
    scanf("%d",n);
    (*v)=(long long int *)malloc((*n)*sizeof(long long int));
    int i;
    for(i=0;i<*n;i++)
        scanf("%lld",((*v)+i));
}

void suma_cif(long long int x,int *nr,int *suma)
{
    if(x==0)
    {
        (*nr)=1;
        (*suma)=0;
    }
    else
    {
        (*suma)=0;
        (*nr)=0;
        while(x)
        {
            (*suma)+=x%10;
            (*nr)++;
            x/=10;
        }
    }
}


void program(long long int *v,int n,int k)
{
    int nr,suma;
    suma_cif(v[0],&nr,&suma);
   // printf("\n%d    %d\n",nr,suma);
    int maxi=suma;
    int i;
    for(i=1;i<n;i++)
    {
        suma_cif(v[i],&nr,&suma);

        if(suma>maxi)maxi=suma;
    }
    for(i=0;i<n;i++)
    {
        suma_cif(v[i],&nr,&suma);
        if(nr>=k && suma==maxi)
            printf("%lld ",v[i]);
    }
}


void afisare(long long int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%lld ",v[i]);
}
int main()
{
    int n,k;
    long long int *v;
    citire(&v,&n);
    printf("k=");
    scanf("%d",&k);
    program(v,n,k);
    //afisare(v,n);
    return 0;
}
