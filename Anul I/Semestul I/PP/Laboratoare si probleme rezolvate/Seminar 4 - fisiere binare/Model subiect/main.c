#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///nu merge indicele de traductibilitate
typedef struct
{
    char romana[21];
    char straina[21];
}Cuvant;

int cmpCrescator(const void *a,const void *b)
{
    Cuvant *va=(Cuvant *)a;
    Cuvant *vb=(Cuvant *)b;
    int na=strlen(va->romana);
    int nb=strlen(vb->romana);
    return na-nb;
}


void incarcareSiSortare(Cuvant **v,int *n,char *numeFisier)
{
    FILE *f;

    f=fopen(numeFisier,"r");

    if(f==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }
    fscanf(f,"%d",n);
    (*v)=(Cuvant *)malloc((*n)*sizeof(Cuvant));

    int i;
    for(i=0;i<*n;i++)
    {
        fscanf(f,"%s%s",(*v)[i].romana,(*v)[i].straina);
       // printf("\n%s  %s\n",(*v)[i].romana,(*v)[i].straina);
    }
    qsort(*v,*n,sizeof(Cuvant),cmpCrescator);
}

int caut(char *s,Cuvant *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        if(strcmp(v[i].romana,s)==0)
        return i;
    return -1;
}


char * traducereCuvant(char *s,Cuvant *v,int n)
{
    int poz=caut(s,v,n);
    if(poz!=-1)
        return v[poz].straina;
    return "-1";
}


void traductibil(char *s,Cuvant *v,int n,int * traduct, int * part_traduct,int *intraduct)
{
    (*traduct)=0;
    (*part_traduct)=0;
    (*intraduct)=0;
    char *p;
    p=strtok(s," ");
    while(p)
    {
        char *t;
        strcpy(t,traducereCuvant(p,v,n));
        if(strcmp(t,"-1")!=0)
            (*traduct)++;
        else
        {
            char t[21];
            int lung=strlen(p);
            p[lung-1]='\0';
            strcpy(t,traducereCuvant(p,v,n));
            if(strcmp(t,"-1")!=0)
                (*part_traduct)++;
            else
            {
                p[lung-2]='\0';
                strcpy(t,traducereCuvant(p,v,n));
                if(strcmp(t,"-1")!=0)
                   (*part_traduct)++;
                else (*intraduct)++;
            }

        }
        p=strtok(NULL," ");
    }
}


void indiceTraductibilitate(char *s,Cuvant *v,int n)
{
    int t,pt,i;
    traductibil(s,v,n,&t,&pt,&i);
    printf("%d %d %d",t,pt,i);
    //return (float)(t+pt)/(float)(t+pt+i);
}
void afisare(Cuvant *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%s  %s\n",v[i].romana,v[i].straina);
}
int main()
{
    Cuvant *v;
    int n,t,pt,i;
    incarcareSiSortare(&v,&n,"dictionar_engleza.txt");
    //afisare(v,n);
    char s[]="cainele lucra bloc";
   // traductibil(s,v,n,&t,&pt,&i);
    indiceTraductibilitate(s,v,n);
    //printf("%f",x);
    return 0;
}
