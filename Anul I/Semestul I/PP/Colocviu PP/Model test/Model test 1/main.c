#include <stdio.h>
#include <stdlib.h>

int * linie(int n,int k)
{
    int *v;
    v=(int *)malloc(n*sizeof(int));

    int i;
    for(i=0;i<n;i++)
        if(i%2==0)v[i]=k;
        else v[i]=i;


    return v;
}

void construire_matrice_alternanta(int ***a,int *nrl,int *nrc)
{
    scanf("%d%d",nrl,nrc);


    (*a)=(int **)malloc((*nrl)*sizeof(int));
    int i;
    for(i=0;i<*nrl;i++)
        (*a)[i]=linie(*nrc,i);
}

void afisare(int **a,int nrl,int nrc)
{
    int i,j;
    for(i=0;i<nrl;i++)
    {
        for(j=0;j<nrc;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }

}


void scriere(char *numeFisier,int **a,int nrl,int nrc)
{
    FILE *f=fopen(numeFisier,"wb");

    fwrite(&nrl,sizeof(int),1,f);
    fwrite(&nrc,sizeof(int),1,f);

    int i;
    for(i=0;i<nrl;i++)
        fwrite(a[i],nrc*sizeof(int),1,f);

    fclose(f);
}


void binar2text(char *numeFisier)
{
    FILE *f=fopen(numeFisier,"rb");

    if(f==NULL)
    {
        printf("Eroare deschidere fisier");
        return ;
    }

    int nrl,nrc,x;
    fread(&nrl,sizeof(int),1,f);
    fread(&nrc,sizeof(int),1,f);
    int i,j;
    for(i=0;i<nrl;i++)
    {
        for(j=0;j<nrc;j++)
        {
            fread(&x,sizeof(int),1,f);
            printf("%d ",x);
        }
        printf("\n");
    }

    fclose(f);
}
int main()
{
    int **a,nrl,nrc;

    construire_matrice_alternanta(&a,&nrl,&nrc);
    afisare(a,nrl,nrc);
    printf("\n");

    scriere("tablou.out",a,nrl,nrc);
    binar2text("tablou.out");
    int i;
    for(i=0;i<nrl;i++)
        free(a[i]);
    free(a);
    a=NULL;
    return 0;
}
