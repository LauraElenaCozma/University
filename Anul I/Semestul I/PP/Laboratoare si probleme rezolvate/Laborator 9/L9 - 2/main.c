#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///NETERMINAT


/*void citire(char ***v,int *n,char *numeFisier)
{
    FILE *f;
    f=fopen(numeFisier,"r");

    (*n)=-1;
    (*v)=(char **)malloc(1000*sizeof(char *));
    char s[21];
    while(fscanf(f,"%s ",s)!=EOF)
    {
        printf("%s %d \n",s,strlen(s));
        (*n)++;
        int lung=strlen(s);
        (*v)[*n]=(char *)malloc(lung * sizeof(char));
        strcpy((*v)[*n],s);
    }
    printf("--%d-- ",*n);
    int i;
    (*n)++;
    for(i=0;i<*n;i++)
        printf("%s  ",(*v)[i]);

    fclose(f);
}*/


typedef struct
{
    char *cuv;
    int a;
}Aparitii;

int caut(Aparitii *c,int n,char *s)
{
    int i;
    for(i=0;i<n;i++)
        if(stricmp(c[i].cuv,s)==0)return i;
    return -1;
}


void citire(Aparitii **v,int *n,char *nume)
{
    FILE * f;
    f=fopen(nume,"r");

    (*v)=NULL;
    (*n)=0;

    char s[1001];
    while(fgets(s,1001,f)!=NULL)
    {

        int lung=strlen(s);
        if(s[lung-1]=='\n')
            s[lung-1]='\0';

        char *p;
        p=strtok(s," ");

        while(p)
        {
            int poz=caut(*v,(*n),p);
            if(poz!=-1)
                (*v)[poz].a++;
            else
            {
                (*n)++;
                Aparitii *aux;
                aux=(Aparitii *)realloc(*v,(*n)*sizeof(Aparitii));

                if(aux!=NULL)
                    (*v)=aux;


                char *cuvant;
                int dimensiune=strlen(p);
                cuvant=(char *)malloc((dimensiune+1)*sizeof(char));

                if(cuvant!=NULL)
                    (*v)[(*n)-1].cuv=cuvant;
                strcpy((*v)[(*n)-1].cuv,p);
                (*v)[(*n)-1].a=1;
            }
            p=strtok(NULL," ");
        }
    }

    fclose(f);
}


void afisare(Aparitii *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%s %d\n",v[i].cuv,v[i].a);
}


int cmpDescrescator(const void *a,const void *b)
{
    Aparitii va=*(Aparitii *)a;
    Aparitii vb=*(Aparitii *)b;
    int nra=va.a;
    int nrb=vb.a;

    if(nra>nrb)return -1;
    if(nra<nrb)return 1;
    if(stricmp(va.cuv,vb.cuv)<0)return -1;
    if(stricmp(va.cuv,vb.cuv)>0)return 1;
    return 0;

}


void sortare(Aparitii *v,int n)
{
    qsort(v,n,sizeof(Aparitii),cmpDescrescator);
}
int main()
{
    Aparitii *v;
    int n;
    citire(&v,&n,"f.in");
    afisare(v,n);
    printf("\n\n");
    sortare(v,n);
    afisare(v,n);
    int i;
    for(i=0;i<n;i++)
        free(v[i].cuv);
    free(v);
    v=NULL;
    return 0;
}
