#include <stdio.h>
#include <stdlib.h>

void citire(int **v,int *n)
{
    scanf("%d",n);
    (*v)=(int *)malloc((*n)*sizeof(int));
    int i;
    for(i=0;i<*n;i++)
        scanf("%d",((*v)+i));
}

void afisare(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",*(v+i));
}


void minmax(int *v,int n,int *min,int *max)
{
    (*min)=(*max)=v[0];
    int i;
    for(i=1;i<n;i++)
       {if(v[i]<(*min))
            (*min)=v[i];
        else if(v[i]>(*max))
            (*max)=v[i];
       }
}

int main()
{
    int *v,n,mini,maxi;
    citire(&v,&n);
    afisare(v,n);
    minmax(v,n,&mini,&maxi);
    if(mini==maxi)printf("\nDA");
    else printf("\n NU");
    free(v);
    return 0;
}
