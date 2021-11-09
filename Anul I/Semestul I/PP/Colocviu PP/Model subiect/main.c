#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *r,*s;
}CUVANT;

void citire(CUVANT **v,int *n,char *numef)
{
    FILE *f;
    f=fopen(numef,"r");
    fscanf(f,"%d",n);
    (*v)=(CUVANT *)malloc((*n)*sizeof(CUVANT));
    char linie[1001];
    int i;
    for(i=0;i<(*n);i++)
    {
        char x[100],y[100];
        fscanf(f,"%s %s",x,y);

        (*v)[i].r=(char *)malloc(strlen(x)+1);
        strcpy((*v)[i].r,x);

        (*v)[i].s=(char *)malloc(strlen(y)+1);
        strcpy((*v)[i].s,y);
    }
    fclose(f);
}

int cmplungime(const void *a,const void *b)
{
    CUVANT x=*(CUVANT *)a;
    CUVANT y=*(CUVANT *)b;

    if(strlen(x.r)<strlen(y.r))return -1;
    if(strlen(x.r)>strlen(y.r))return 1;
    return 0;
}


void sortare(CUVANT **v,int *n,char *numef)
{
    citire(v,n,numef);
    qsort((*v),(*n),sizeof(CUVANT),cmplungime);
}

void afisare(CUVANT *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%s %s\n",v[i].r,v[i].s);
}

char * caut(char *cuv,CUVANT *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        if(strcmp(cuv,v[i].r)==0)
         return v[i].s;
    return NULL;
}

char * traducere(char *cuv,char *eng,char *fr,char *ger,char *limba,CUVANT *e,int nre,CUVANT *f,int nrf,CUVANT *g,int nrg)
{
    char *p=strstr(eng,limba);
    if(p!=NULL)
        return caut(cuv,e,nre);

    p=strstr(fr,limba);
    if(p!=NULL)
        return caut(cuv,f,nrf);
    p=strstr(ger,limba);
    if(p!=NULL)
        return caut(cuv,g,nrg);
    return NULL;
}



int main()
{
    CUVANT *e,*f,*g;
    int nre,nrf,nrg;
    sortare(&e,&nre,"dictionar_engleza.txt");
    sortare(&f,&nrf,"dictionar_franceza.txt");
    sortare(&g,&nrg,"dictionar_germana.txt");
    printf("%s",traducere("noapte","dictionar_engleza.txt","dictionar_franceza.txt","dictionar_germana.txt","germana",e,nre,f,nrf,g,nrg));
    return 0;
}
