#include <stdio.h>
#include <stdlib.h>

void citire(int **v,int *n)
{
    scanf("%d",n);

    *v=(int *)malloc((*n)*sizeof(int));
    int i;
    for(i=0;i<*n;i++)
         scanf("%d",&(*v)[i]);
}

void majoritar(int *v,int n)
{
    int x=v[0];
    int k=1;
    int i;

    for(i=1;i<n;i++)
    {
        if(v[i]==x)k++;
        else
        {
            k--;
            if(k==0){x=v[i];k=1;}
        }
    }

    k=0;
    for(i=0;i<n;i++)
    {
        if(v[i]==x)k++;
    }


    if(k>=(n/2+1))printf("%d e element majoritar",x);
    else printf("Nu exista element majoritar");
}
int main()
{
    int *v,n;
    citire(&v,&n);
    majoritar(v,n);
    return 0;
}
