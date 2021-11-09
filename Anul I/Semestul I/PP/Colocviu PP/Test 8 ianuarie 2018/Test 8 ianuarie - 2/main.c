#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int majuscula(char c)
{
    if(!(c>='A' && c<='Z'))
        return 0;
    return 1;
}

void citire(char **cuv,char **s,int *nr,char *numeFisier)
{

    (*nr)=0;//numarul de majuscule

    FILE *f;
    f=fopen(numeFisier,"r");

    if(f==NULL)
    {
        printf("Eroare deschidere fisier");
        return ;
    }

    (*cuv)=NULL;
    char c;
    int lung=0;

    c=fgetc(f);   //pe prima linie e un singur cuvant
    while(c!='\n')
    {
       if(majuscula(c))(*nr)++;
       lung++;
       char *aux;
       aux=realloc(*cuv,(lung+1)*sizeof(char));
       if(aux==NULL)
       {
           return ;
       }
       (*cuv)=aux;
       (*cuv)[lung-1]=c;
       (*cuv)[lung]='\0';

       c=fgetc(f);
    }



    lung=0;
    (*s)=NULL;
    while((c=fgetc(f))!=EOF)
    {
        if(majuscula(c))(*nr)++;

        lung++;
        char *aux;
        aux=realloc(*s,(lung+1)*sizeof(char));
        if(aux==NULL)
        {
           return ;
        }
        (*s)=aux;
        (*s)[lung-1]=c;
        (*s)[lung]='\0';

    }

   // printf("%s  \n%s",*cuv,*s);
    fclose(f);
}



void citirev2(char **cuv,char **s,int *nr,char *numeFisier)
{
    FILE *f=fopen(numeFisier,"r");

    if(f==NULL)
        return ;

    (*cuv)=(char *)malloc(50*sizeof(char));
    fscanf(f,"%s",*cuv);
    (*s)=NULL;

    (*nr)=0;

    int lung=1;
    char c;
    while((c=fgetc(f))!=EOF)
    {
        lung++;
        char *aux;
        aux=realloc((*s),(lung)*sizeof(char));

        if(aux==NULL)
            return ;

        (*s)=aux;
        (*s)[lung-1]='\0';
        (*s)[lung-2]=c;
    }

    printf("%s\n%s",(*cuv),(*s));
    fclose(f);
}



int identic(char *c,char *s,int p)
{
    int lung=strlen(c);
    int poz=1,i;
    for(i=p;i<=p+lung-2;i++)
    {
        if(s[i]!=c[poz])return -i;
        poz++;
    }
    return 1;
}


void aparitie(char *c,char *s,char *numeFisier)
{
    FILE *f;
    f=fopen(numeFisier,"w");

    if(f==NULL)
    {
        printf("Eroare deschidere fisier");
        return ;
    }



    int lung=strlen(s),i;
    int linie=2,aparitii=0;
    for(i=0;i<lung;i++)
        {
            if(s[i]=='\n')
            {
                fprintf(f,"linie=%d    aparitie=%d\n",linie,aparitii);
                linie++;
                aparitii=0;
            }
            else if(s[i]==c[0])
            {
                int ok=identic(c,s,i+1);
                if(ok==1)
                {
                    aparitii++;
                    i+=(strlen(c)-1);
                }
                else i=(-ok);
            }
        }

        fclose(f);
}


typedef struct
{
    int majuscule;
    char *cuv;

}Cuvant;


int caut(Cuvant *v,int n,char *c)
{
    int i;
    for(i=0;i<n;i++)
        if(strcmp(v[i].cuv,c)==0)return 1;
    return 0;
}



int nr_majuscule_in_cuvant(char *c)
{
    int i;
    int nr=0;
    for(i=0;c[i]!=NULL;i++)
        if(majuscula(c[i]))nr++;
    return nr;
}
void despartire_in_cuvinte(Cuvant **v,int *n,char *s)
{
    char *p=strtok(s," .?!\n");

    (*v)=NULL;
    (*n)=0;
    while(p!=NULL)
    {
        if(!caut(*v,*n,p))
        {
            (*n)++;
        Cuvant *aux;
        aux=(Cuvant *)realloc(*v,(*n)*sizeof(Cuvant));
        if(aux==NULL)
            return -1;

        (*v)=aux;

        (*v)[(*n)-1].majuscule=nr_majuscule_in_cuvant(p);

        char *auxc;
        int lung=strlen(p);
        (*v)[(*n)-1].cuv=NULL;
        auxc=(char *)realloc((*v)[(*n)-1].cuv,lung*sizeof(char));

        if(auxc==NULL)
            return -1;

        (*v)[(*n)-1].cuv=auxc;
        strcpy((*v)[(*n)-1].cuv,p);


        }

        p=strtok(NULL," .?!\n");

        //printf("\n %s    %d \n",(*v)[(*n)-1].cuv,(*v)[(*n)-1].majuscule);
    }
}
int cmpNrMajuscule(const char *a,const char *b)
{
    Cuvant va=*(Cuvant *)a;
    Cuvant vb=*(Cuvant *)b;
    return (vb.majuscule-va.majuscule);
}

void sortare(Cuvant *v,int n)
{
    qsort(v,n,sizeof(Cuvant),cmpNrMajuscule);
}
int main()
{
    char *cuv,*s;
    //Cuvant *v;
    int n,nr;
    citirev2(&cuv,&s,&n,"cuvinte.in");
    /*printf("nr majuscule=%d\n",n);
    aparitie(cuv,s,"cuvinte.out");
    despartire_in_cuvinte(&v,&nr,s);
    sortare(v,nr);
    int i;
    for(i=0;i<nr;i++)
        printf("%s   ",v[i].cuv);*/

    free(cuv);
    free(s);
    return 0;
}
