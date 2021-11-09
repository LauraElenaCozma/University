#include <stdio.h>
#include <stdlib.h>

void binar(int **v,int *n,char *numef)
{
    FILE *f;
    f=fopen(numef,"rb");
    int x;
    (*v)=NULL;
    (*n)=0;
    while(fread(&x,sizeof(int),1,f)==1)
    {
        (*n)++;
        int *aux;
        aux=realloc((*v),(*n)*sizeof(int));
        if(aux==NULL)
        {
            printf("Eroare realocare");
            free(*v);
             return 0;
        }

        (*v)=aux;
        (*v)[(*n)-1]=x;
    }
    fclose(f);
}

int cmp(const void *a,const void *b)
{
    int va=*(int *)a;
    int vb=*(int *)b;

    if(va>vb)return -1;
    if(va<vb)return 1;
    return 0;
}

void sortare(int v,int n)
{
    qsort(v,n,sizeof(int),cmp);
}

void text2binar(char *numeBinar,char *numeText)
{
    int x;
    FILE *fb,*ft;
    fb=fopen(numeBinar,"wb");
    if(fb==NULL)
        printf("Eroare deschidere");
    ft=fopen(numeText,"r");
    if(ft==NULL)
        printf("Eroare deschidere");
    while(fscanf(ft,"%d",&x)==1)
        fwrite(&x,sizeof(int),1,fb);
    fclose(fb);
    fclose(ft);
}

void binar2text(char *numeBinar,char *numeText)
{
    int x;
    FILE *fb,*ft;
    fb=fopen(numeBinar,"rb");
    ft=fopen(numeText,"w");
    while(fread(&x,sizeof(int),1,fb)==1)
        fprintf(ft,"%d ",x);
    fclose(fb);
    fclose(ft);
}

void modif_semn(char *numeBinar)
{
    int x;
    FILE *f;
    f=fopen(numeBinar,"rb+");
    while(fread(&x,sizeof(int),1,f)==1)
    {
        x=-x;
        fseek(f,-sizeof(int),SEEK_CUR);
        fwrite(&x,sizeof(int),1,f);
        fflush(f);
    }
    fclose(f);
}
int main()
{
    text2binar("f.bin","f.txt");
    int *v,n;
    modif_semn("f.bin");
    binar(&v,&n,"f.bin");
    int i;
    sortare(v,n);
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
    free(v);
    return 0;
}
