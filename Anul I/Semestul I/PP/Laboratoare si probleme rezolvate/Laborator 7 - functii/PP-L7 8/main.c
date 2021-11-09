#include <stdio.h>
#include <stdlib.h>


void cif_min_max(int x,int *mini,int *maxi)
{
    if(x==0)
    {
        (*mini)=0;
        (*maxi)=0;
    }
    else
    {
        (*mini)=x%10;
        (*maxi)=x%10;
        while(x!=0)
        {
            if(x%10>(*maxi))(*maxi)=x%10;
            if(x%10<(*mini))(*mini)=x%10;
            x/=10;
        }
    }
}


void cif_egale(int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        int mini,maxi;
        cif_min_max(i,&mini,&maxi);
        if(mini==maxi)printf("%d ",i);
    }
}

int main()
{

    int n;
    scanf("%d",&n);
    cif_egale(n);
    return 0;
}
