#include <stdio.h>
#include <stdlib.h>

///merge, cu exceptia faptului ca eu ii dau un numar si nu pune exact acelasi numar si in celalalt vector. ex v[0]=3.2 w[0]=3.19999
void citire(int *n,float **v)
{
    scanf("%d",n);
    *v=(float *)malloc((*n)*sizeof(float));
    int i;
    for(i=0;i<*n;i++)
        scanf("%f",&(*v)[i]);
}

void creare(int n,float *v,int *m,float **w)
{
    (*m)=2*n-1;
    (*w)=(int *)malloc(sizeof(int)*(*m));
    int i,j=0;
    for(i=0;i<n-1;i++)
    {
        (*w)[j]=v[i];
        float med=((v[i]+v[i+1])/2.0);
        (*w)[++j]=med;
        (*w)[++j]=v[i+1];
    }
}

void afisare(int n,float *v)
{
    int i;
    for(i=0;i<n;i++)
        printf("%f ",v[i]);
    printf("\n");
}

int main()
{
    int *v,*w;
    int n,m;
    citire(&n,&v);
    creare(n,v,&m,&w);
    afisare(m,w);
    return 0;
}
