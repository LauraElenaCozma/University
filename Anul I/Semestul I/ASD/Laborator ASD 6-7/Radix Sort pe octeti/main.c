#include <stdio.h>
#include <stdlib.h>

typedef union
{
    unsigned int x;
    unsigned char b[4];
}Bytes;

void citire(FILE *f,int v[],int *n)
{
    f=fopen("f.in","r");
    fscanf(f,"%d",n);
    int i;
    for(i=1;i<=(*n);i++)
        fscanf(f,"%d",&v[i]);
    fclose(f);
}


void afisare(int v[],int n)
{
    int i;
    for(i=1;i<=n;i++)
        printf("%d ",v[i]);
    printf("\n");
}

unsigned char octetk(unsigned int nr,int k)
{
    Bytes a;
    a.x=nr;
    return a.b[k-1];//ls byte e b[0]
}

void adaugInMatrice(int a[][101],int x,unsigned int c)
{
    a[c][0]++;
    a[c][a[c][0]]=x;
}

void initializareZero(int a[][101])
{
    int i;
    for(i=0;i<=255;i++)
        a[i][0]=0;
}

void copiereInVector(int x[],int a[][101])
{
    int k=0,i,j;
    for(i=0;i<=255;i++)
        for(j=1;j<=a[i][0];j++)
            x[++k]=a[i][j];
}

void RadixSort(int v[],int n,int a[][101])
{
    initializareZero(a);
    int k,i;
    for(k=1;k<=4;k++)
    {
        initializareZero(a);
        for(i=1;i<=n;i++)
        {
            unsigned int c=octetk(v[i],k);
            adaugInMatrice(a,v[i],c);
        }
        copiereInVector(v,a);

    }
}
int main()
{
    FILE *f;
    int v[101],n,a[256][101];
    citire(f,v,&n);
    RadixSort(v,n,a);
    afisare(v,n);

    return 0;
}
