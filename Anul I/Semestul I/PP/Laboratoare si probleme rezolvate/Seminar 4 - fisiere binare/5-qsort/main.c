#include <stdio.h>
#include <stdlib.h>


int dimensiune(char *nume)
{
    FILE *f;
    f=fopen(nume,"rb");

    if(f==NULL)
    {
        printf("Eroare");
        return -1;
    }
    fseek(f,0,2);
    int x=ftell(f);
    fclose(f);
    return x/4;
}

void fisier2binar(char *numeText,char *numeBinar)
{
    FILE *fin,*fout;
    fin=fopen(numeText,"r");

    if(fin==NULL)
    {
        printf("Eroare");
        return ;
    }
    fout=fopen(numeBinar,"wb");


    int x;
    while(fscanf(fin,"%d",&x)==1)
    {
        fwrite(&x,sizeof(int),1,fout);

    }
    fclose(fin);
    fclose(fout);
}

void binar2vector(char *numeFisier,int **v,int *n)
{
    FILE *f;
    f=fopen(numeFisier,"rb");

    if(f==NULL)
    {
        printf("Eroare");
        return ;
    }

    (*n)=dimensiune(numeFisier);
    (*v)=(int *)malloc((*n)*sizeof(int));

    int x,i=0;
    while(fread(&x,sizeof(int),1,f)==1)
    {
        (*v)[i]=x;
        i++;
    }
    fclose(f);
}

int cmpCrescator(const void *a,const void *b)
{
    int va=*(int *)a;
    int vb=*(int *)b;
    return va-vb;
}


void afisare(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
}
int main()
{
    int *v,n;
    fisier2binar("f.txt","f.bin");
    binar2vector("f.bin",&v,&n);
    qsort(v,n,sizeof(int),cmpCrescator);
    afisare(v,n);
    return 0;
}
