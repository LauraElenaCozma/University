#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void scrieBin(int *n,int ***a,char *numeBin)
{
    FILE * f;
    f=fopen(numeBin,"wb");

    if(f==NULL)
    {
        printf("nu am gasit imaginea sursa din care citesc");
   		return;
    }


    scanf("%d",n);


    (*a)=(int **)malloc((*n)*sizeof(int *));
     int i,j;

     for(i=0;i<*n;i++)
     {
         (*a)[i]=malloc((*n)*sizeof(int));
         for(j=0;j<*n;j++)
            scanf("%d",&(*a)[i][j]);
        fwrite((*a)[i],(*n)*sizeof(int),1,f);
     }

     fclose(f);
}


void binar2text(int n,char *numeBin,char *numeText)
{
    FILE * fin,*fout;
    fin=fopen(numeBin,"rb");

    if(fin==NULL)
    {
        printf("nu am gasit imaginea sursa din care citesc");
   		return;
    }
    fout=fopen(numeText,"w");
    if(fout==NULL)
    {
        printf("nu am gasit imaginea sursa din care citesc");
   		return;
    }

    int *a;
    a=(int *)malloc(n*sizeof(int));
    int i,j;
    for(i=0;i<n;i++)
    {
        fread(a,n*sizeof(int),1,fin);
        for(j=0;j<n;j++)
            fprintf(fout,"%d ",a[j]);
        fprintf(fout,"\n");
    }

    fclose(fin);
    fclose(fout);

}


int nrLinii(char *numeFisier)
{
    FILE *f;
    f=fopen(numeFisier,"rb");
    fseek(f,0,2);
    int x=ftell(f);
    x/=4;
    return sqrt(x);
}


void diag(char *numeFisier)
{
    FILE *f;
    f=fopen(numeFisier,"rb");
    if(f==NULL)
    {
        printf("nu am gasit imaginea sursa din care citesc");
   		return;
    }

    int n=nrLinii(numeFisier),i,x;
    for(i=0;i<n;i++)
    {
        fread(&x,sizeof(int),1,f);
        printf("%d ",x);
        fseek(f,n*sizeof(int),1);
    }
}

int main()
{
    int **a,n;
    scrieBin(&n,&a,"matrice.bin");
    //printf("  %d  ",nrLinii("matrice.bin"));
    diag("matrice.bin");
    binar2text(n,"matrice.bin","rezultat.txt");
    return 0;
}
