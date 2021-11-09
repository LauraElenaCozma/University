#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *nume;
    float temp;
}Oras;

void citire(char *nume,Oras **v,int *n,float *medie)
{
    FILE *f=fopen(nume,"r");

    if(f==NULL)return ;
    (*v)=NULL;
    char s[40];
    float t;
    (*n)=-1;
    (*medie)=0;
    while(fscanf(f,"%s %f",s,&t)==2)
    {
        (*n)++;

        Oras *aux;
        aux=(Oras *)realloc((*v),((*n)+1)*sizeof(Oras));

        if(aux!=NULL)
            (*v)=aux;
        int lung=strlen(s);
        (*v)[*n].nume=(char *)malloc((lung+1)*sizeof(char));
        strcpy((*v)[*n].nume,s);

        (*v)[*n].temp=t;
         (*medie)+=(*v)[*n].temp;

         printf("%s %f\n",(*v)[*n].nume,(*v)[*n].temp);
    }

    (*medie)=(*medie)/(float)((*n)+1);

    fclose(f);
}



void maxim(char *nume,Oras *v,int n)
{
    FILE *f=fopen(nume,"w");

    float maxi;
    maxi=v[0].temp;

    int i;
    for(i=1;i<n;i++)
        if(v[i].temp>maxi)maxi=v[i].temp;
    fprintf(f,"maxim=%f\n",maxi);
    for(i=0;i<n;i++)
        if(v[i].temp==maxi)
           fprintf(f,"%s  ",v[i].nume);

    fclose(f);
}

int cmpDescrescator(const void *a,const void *b)
{
    Oras va=*(Oras *)a;
    Oras vb=*(Oras *)b;
    float ta=va.temp;
    float tb=vb.temp;

    if(ta>tb)return -1;
    if(ta<tb)return 1;
    char *na=va.nume;
    char *nb=va.nume;
    if(stricmp(na,nb)<0)return -1;
    if(stricmp(na,nb)>0)return 1;
    return 0;
}


void sortare(Oras *v,int n)
{
    qsort(v,n,sizeof(Oras),cmpDescrescator);
}


void afisare(Oras *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%s %f\n",v[i].nume,v[i].temp);
}
int main()
{
    Oras *v;
    int n;
    float medie;
    citire("temperaturi.txt",&v,&n,&medie);
    printf("%.2f",medie);
    maxim("maxime.txt",v,n);

    printf("\n\n");
    sortare(v,n);
    afisare(v,n);
    free(v);
    return 0;
}
