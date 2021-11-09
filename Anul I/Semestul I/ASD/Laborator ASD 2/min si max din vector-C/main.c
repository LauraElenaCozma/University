#include <stdio.h>
#include <stdlib.h>

int * citire(FILE *in,int *v,int *n)
{
    fscanf(in,"%d",n);
    int i;
    v=(int *)malloc((*n)*sizeof(int));
    for(i=0;i<(*n);i++)
        fscanf(in,"%d",&v[i]);
    return v;
}


void minmax(int *min,int *max,int *v,int n)
{
    if(v[0]<v[1])      //o comparatie
    {
        *min=v[0];    //*min acceseaza valoarea
        *max=v[1];
    }
    else
    {
        *min=v[1];
        *max=v[0];
    }
    int i;
    for(i=2;i<n;i++)
    {
        if(v[i]>(*max))(*max)=v[i];
        else if(v[i]<(*min))(*min)=v[i];
    }
}
int main()
{
    int *v,n,i;
    FILE *in=fopen("f.in","r");
    v=citire(in,v,&n);
    for(i=0;i<n;i++)
        printf("%d ",v[i]); //afisam vectorul pentru a fi mai usor de urmarit
    int min,max;
    minmax(&min,&max,v,n);
    printf("\nmin=%d si max=%d",min,max);
    return 0;
}
