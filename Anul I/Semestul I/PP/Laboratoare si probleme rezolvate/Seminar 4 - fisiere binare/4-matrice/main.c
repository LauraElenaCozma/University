#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void generareMatrice(int *n,int ***a)
{
    srand(time(NULL));
    (*n)=10+rand()%90;

    (*a)=(int **)malloc((*n)*sizeof(int *));

    int i,j;
    for(i=0;i<*n;i++)
    {
        (*a)[i]=malloc((*n)*sizeof(int));
        for(j=0;j<*n;j++)
            (*a)[i][j]=abs(i-j);

    }
}

void scrieBin(int n,int **a,char * numeBin)
{
    FILE *f;
    f=fopen(numeBin , "wb" );

    if(f==NULL)
    {
        printf("Eroare fisier");
        return ;
    }

    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
           fwrite(&a[i][j],sizeof(int),1,f);

    fclose(f);
}

int aleator(int n)
{
    //genereaza un nr aleator de la 0 la n-1
    srand(time(NULL));
    int x=rand()%n;
    return x;
}

void interschimbareLinii(int n,char *numeBin)
{
    FILE *f;
    f=fopen(numeBin , "rb+" );

    if(f==NULL)
    {
        printf("Eroare fisier");
        return ;
    }

    int *aux1,*aux2;
    aux1=(int *)malloc(n*sizeof(int));
    aux2=(int *)malloc(n*sizeof(int));
    int i=aleator(n),j;
    do
    {
        j=aleator(n);
    }
    while(i==j);

    printf("\ni=%d    j=%d  \n ",i,j);

    fseek(f,i*n*sizeof(int),0);
    fread(aux1,n*sizeof(int),1,f);
    fseek(f,j*n*sizeof(int),0);
    fread(aux2,n*sizeof(int),1,f);

    fseek(f,i*n*sizeof(int),0);
    fwrite(aux2,n*sizeof(int),1,f);
    fseek(f,j*n*sizeof(int),0);
    fwrite(aux1,n*sizeof(int),1,f);
    fclose(f);

}

void binar2text(int n,char *numeBinar,char *numeText)
{
    FILE *fin,*fout;

    fin=fopen(numeBinar,"rb");
    fout=fopen(numeText,"w");

    if(fin==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }
    if(fout==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }

    int x,i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            fread(&x, sizeof(int),1 , fin);
            fprintf(fout,"%d ",x);
        }
        fprintf(fout,"\n");
    }


    fclose(fin);
    fclose(fout);
}

int main()
{
    int n,**a;
    generareMatrice(&n,&a);
    scrieBin(n,a,"f.bin");
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
    interschimbareLinii(n,"f.bin");
    binar2text(n,"f.bin","f.txt");
    return 0;
}
