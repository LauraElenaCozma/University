#include <stdio.h>
#include <stdlib.h>

int ** creare(int *n)
{
    int **a;
    scanf("%d",n);


    a=(int **)malloc(2*(*n)*sizeof(int *));

    int i,j,k=0;
    for(i=(*n);i>=1;i--)
    {
        a[k]=(int *)malloc(i*sizeof(int));
        for(j=0;j<i;j++)
            scanf("%d",&a[k][j]);
        k++;

    }
    for(i=1;i<=(*n);i++)
    {
        a[k]=(int *)malloc(i*sizeof(int));
        for(j=0;j<i;j++)
            scanf("%d",&a[k][j]);
        k++;

    }

    return a;
}

void afisare(int **a,int n)
{
    int i,j,k=0;
    for(i=n;i>=1;i--)
    {
        for(j=0;j<i;j++)
            printf("%d ",a[k][j]);
        printf("\n");
        k++;
    }
    for(i=1;i<=n;i++)
    {
        for(j=0;j<i;j++)
            printf("%d ",a[k][j]);
        printf("\n");
        k++;
    }
    printf("\n");
}



void toBinar(int **a,int n,char *numefisier)
{
    FILE *f;
    f=fopen(numefisier,"wb");

    if(f==NULL)return ;

    int i,k=0;
    for(i=n;i>=1;i--)
    {
        fwrite(a[k],i*sizeof(int),1,f);
        k++;
    }
    for(i=1;i<=n;i++)
    {
        fwrite(a[k],i*sizeof(int),1,f);
        k++;

    }

    fclose(f);
}


void binar2text(char *numeb,int **a,int n)
{
    FILE *f;

    f=fopen(numeb,"rb");

    if(f==NULL)
        return ;
    int i,j,k=0;
    for(i=n;i>=1;i--)
    {
        fread(a[k],i*sizeof(int),1,f);
        for(j=0;j<i;j++)
            printf("%d ",a[k][j]);
    printf("\n");
        k++;
    }
    for(i=1;i<=n;i++)
    {
        fread(a[k],i*sizeof(int),1,f);
        for(j=0;j<i;j++)
            printf("%d ",a[k][j]);
        printf("\n");
        k++;

    }
    printf("\n\n");
    fclose(f);
}

int maxim(int **a,int n)
{
    int maxi=a[0][0];
    int i,j,k=0;
    for(i=n;i>=1;i--)
    {
        for(j=0;j<i;j++)
           if(a[k][j]>maxi)maxi=a[k][j];
        k++;
    }
    for(i=1;i<=n;i++)
    {
        for(j=0;j<i;j++)
             if(a[k][j]>maxi)maxi=a[k][j];
        k++;
    }
    return maxi;
}

void inlocuire(char *numeb,int **a,int n)
{
    int maxi=maxim(a,n);
    FILE *f;
    f=fopen(numeb,"rb+");
    int x;
    while(fread(&x,sizeof(int),1,f)==1)
    {
        if(x<=3)
            x=maxi;
        fseek(f,-sizeof(int),1);
        fwrite(&x,sizeof(int),1,f);
        fflush(f);

    }


    fclose(f);
}
int main()
{
    int **a,n;
    a=creare(&n);
    afisare(a,n);

    toBinar(a,n,"matrice.bin");
    binar2text("matrice.bin",a,n);

    inlocuire("matrice.bin",a,n);
    binar2text("matrice.bin",a,n);
    int i;
    for(i=0;i<2*n;i++)
        free(a[i]);
    free(a);
    return 0;
}
