#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int populatie;
    char denumire[20];

}Oras;


void citire(Oras **v,int *n)
{
    scanf("%d",n);

    (*v)=(Oras *)malloc((*n)*sizeof(Oras));
    int i;

    for(i=0;i<*n;i++)
    {
        scanf("%s%d",&(*v)[i].denumire,&(*v)[i].populatie);
    }
}


void afisare1(Oras *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%s  %d\n",v[i].denumire,v[i].populatie);
}


void scrieBinar(Oras *v,int n,char *numeFisier)
{
    FILE *f;

    f=fopen(numeFisier,"wb");

    if(f==NULL)
    {
        printf("Eroare deschidere fisier");
        return ;
    }

    int i;
    for(i=0;i<n;i++)
    {
        fwrite(&v[i].populatie,sizeof(int),1,f);
        int lung=strlen(v[i].denumire);
        fwrite(&lung,sizeof(int),1,f);
        fwrite(v[i].denumire,lung*sizeof(char *),1,f);


    }

    fclose(f);
}


void afisare(char *numeBinar,char *numeText)
{
    FILE *fin,*fout;
    fin=fopen(numeBinar,"rb");

    if(fin==NULL)
    {
        printf("Eroare deschidere fisier");
        return ;
    }

    fout=fopen(numeText,"w");

    if(fout==NULL)
    {
        printf("Eroare deschidere fisier");
        return ;
    }

    int x,y;
    while(fread(&x,sizeof(int),1,fin)==1)
    {
        fprintf(fout,"%d ",x);
        fread(&y,sizeof(int),1,fin);
        char s[20];
        fread(s,y*sizeof(char *),1,fin);

        fprintf(fout,"%s \n",s);

    }

    fclose(fin);
    fclose(fout);
}




void copiere(char *numeBinar, char *aux,int n)
{
    FILE *f1,*f2;

    f1=fopen(numeBinar,"rb+");

    if(f1==NULL)
    {
        printf("Eroare deschidere fisier");
        return ;
    }

    f2=fopen(aux,"wb+");

    if(f2==NULL)
    {
        printf("Eroare deschidere fisier");
        return ;
    }
    int x,y,nr=0;
    char s[20];

    while(nr!=n/2)
    {
        fread(&x,sizeof(int),1,f1);
        fread(&y,sizeof(int),1,f1);
        fread(s,sizeof(char *),y,f1);
        nr++;
    }

    while(fread(&x,sizeof(int),1,f1))
    {
        fwrite(&x,sizeof(int),1,f2);
        fread(&y,sizeof(int),1,f1);
        fwrite(&y,sizeof(int),1,f2);
        fread(s,sizeof(char *),y,f1);
        fwrite(s,sizeof(char *),y,f2);
    }
    fclose(f1);
    fclose(f2);
}


void adaugare(char *numeBinar,char *aux,int n)
{
    FILE *f1,*f2;

    f1=fopen(numeBinar,"rb+");

    if(f1==NULL)
    {
        printf("Eroare deschidere fisier");
        return ;
    }

    f2=fopen(aux,"ab+");

    if(f2==NULL)
    {
        printf("Eroare deschidere fisier");
        return ;
    }
    int x,y,nr=0;
    char s[20];
    while(nr!=n/2)
    {
        fread(&x,sizeof(int),1,f1);
        fwrite(&x,sizeof(int),1,f2);
        fread(&y,sizeof(int),1,f1);
        fwrite(&y,sizeof(int),1,f2);
        fread(s,sizeof(char *),y,f1);
        fwrite(s,sizeof(char *),y,f2);
        nr++;
    }

    fclose(f1);
    fclose(f2);
}

int main()
{
    Oras *v;
    int n;
    citire(&v,&n);


    scrieBinar(v,n,"f.bin");
    copiere("f.bin","faux.bin",n);
    adaugare("f.bin","faux.bin",n);
    afisare("faux.bin","f.txt");
    free(v);
    return 0;
}
