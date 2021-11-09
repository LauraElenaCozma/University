#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct
{
    int re,im,mod;
}Complex;

void citire(Complex **v,int *n,char *numeFisier)
{
    FILE *fin;
    fin=fopen(numeFisier,"r");

    if(fin==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }
    fscanf(fin,"%d",n);
    (*v)=(Complex *)malloc((*n)*sizeof(Complex));

    int i;
    for(i=0;i<*n;i++)
    {
        fscanf(fin,"%d%d",&(*v)[i].re,&(*v)[i].im);
        (*v)[i].mod=abs((*v)[i].re*(*v)[i].re-(*v)[i].im*(*v)[i].im);
    }

}


int maxim(Complex *v,int n)
{
    int maxi=v[0].mod;
    int i;
    for(i=1;i<n;i++)
        if(v[i].mod>maxi)
           maxi=v[i].mod;
    return maxi;
}

void afisare_maxim(Complex *v,int n)
{
    int maxi=maxim(v,n);
    int i;
    for(i=0;i<n;i++)
    {
    if(v[i].mod==maxi)
    {
        printf("\nRe de v[%d] este %d\n",i,v[i].re);
        printf("Im de v[%d] este %d\n",i,v[i].im);

    }
    //printf("\n Mod de v[%d] e %d\n",i,v[i].mod); afisarea tuturor modulelor
    }
}

int main()
{
    Complex *v;
    int n;
    citire(&v,&n,"f.in");
    afisare_maxim(v,n);
    return 0;
}
