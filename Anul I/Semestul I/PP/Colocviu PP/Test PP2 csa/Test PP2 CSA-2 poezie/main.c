#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///lipseste un subpunct.repetitia
void citire(char **s,char **titlu,char *numeFisier)
{
    FILE *f;

    f=fopen(numeFisier,"r");

    if(f==NULL)
    {
        printf("Eroare deschidere fisier");
        return ;
    }

    char c = fgetc(f);
    int lung = 0;
    (*titlu) = NULL;
    while(c!='\n')
    {
        lung ++;
        char *aux1;

        aux1 = realloc (  *titlu, (lung+1)*sizeof(char));

        if(aux1 == NULL)
            return ;

        (*titlu) = aux1;

        (*titlu)[lung-1]=c;
        (*titlu)[lung] = '\0';

        c = fgetc(f);
    }

    lung=0;

    c=fgetc(f);//citim \n de dupa titlu

    (*s) = NULL;
    while( (c = fgetc(f)) != EOF )
    {
        lung++;

        char *aux1;

        aux1 = realloc (  *s, (lung+1)*sizeof(char));

        if(aux1 == NULL)
            return ;

        (*s) = aux1;

        (*s)[lung-1]=c;
        (*s)[lung] = '\0';

    }

    //printf("%s %s",*titlu,*s);
    fclose(f);
}


void initializareZero(int v[],int n)
{
    int i;
    for(i=0;i<n;i++)
        v[i]=0;
}


void transformMic(char *c)
{
    if((*c)>='A' && (*c)<='Z')
        (*c)=(*c)-'A'+'a';
}

void asonanta(char *s)
{
    int v['z'-'a'+1];
    initializareZero(v,'z'-'a'+1);

    int rand=1;
    int maxi=0;

    int i;
    for(i=0;s[i];i++)
    {
        char c=s[i];

        if(c=='\n')
        {
            if(maxi!=0)
            {
                printf("rand=%d  ",rand);
                int j;
                for(j=0;j<'z'-'a'+1;j++)
                   if(v[j]==maxi)
                      printf("%c ",j+'a');
                printf("\n");

                rand++;

                initializareZero(v,'z'-'a'+1);
                maxi=0;
            }


        }

        else
        {
            if(strchr("aeiouAEIOU",c))
            {
                transformMic(&c);
                v[c-'a']++;
                if(v[c-'a']>maxi)maxi=v[c-'a'];
            }

        }
    }

}



void ingambament(char *s,char *numeFisier)
{

    FILE *f;

    f=fopen(numeFisier,"w");

    if(f==NULL)
    {
        printf("Eroare deschidere fisier");
        return ;
    }

    char *t,*p;
    int lung=strlen(s);
    t=(char *)malloc(lung*sizeof(char));
    strcpy(t,s);
    //ca sa nu pierdem sirul initial
    p=strtok(t,"\n");
    while(p)
    {
        if(p[0]>='a' && p[0]<='z')  //e litera mica
            fprintf(f,"%s \n",p);
        p=strtok(NULL,"\n");
    }

    fclose(f);

}




///repetitia

typedef struct
{
    char *cuv;
    int a;
}Repetitie;

int caut(Repetitie *v,int n,char *s)
{
    int i;
    for(i=0;i<n;i++)
        if(stricmp(v[i].cuv,s)==0)return i;
    return -1;
}


int maxim(Repetitie *v,int n)
{
    int i,maxi=0;
    for(i=0;i<n;i++)
        if(v[i].a>maxi)
           maxi=v[i].a;
    return maxi;
}

void repetitie(char *titlu, char *s)
{
    Repetitie *v,*aux;
    v=NULL;
    char *p;
    int nr=0;
    p=strtok(s," .!?,");
    while(p)
    {
        int poz=caut(v,nr,p);
        if(poz==-1)
        {
            nr++;
            aux=(Repetitie *)realloc(v,nr*sizeof(Repetitie));

            if(aux==NULL)
            {
                printf("Eloare realocare");
                return ;
            }

            v=aux;


            int lung=strlen(p);
            v[nr-1].cuv=(char *)malloc(lung*sizeof(char));
            strcpy(v[nr-1].cuv,p);
            v[nr-1].a=1;
        }

        else
            v[poz].a++;
        p=strtok(NULL," .!?,");
    }


   int maxi=maxim(v,nr);
    int i,ok=0;
    for(i=0;i<nr;i++)
        if(v[i].a==maxi)
    {
        if(stricmp(v[i].cuv,titlu)==0){printf("Titlul este sugestiv\n");ok=1;}
        printf("%s\n",v[i].cuv);
    }

    if(ok==0)
        printf("Titlul nu este sugestiv");

    for(i=0;i<nr;i++)
        free(v[i].cuv);
    free(v);
}

int main()
{
    char *titlu,*s;
    citire(&s,&titlu,"poezie.txt");


    asonanta(s);

    printf("\n");
    ingambament(s,"ingambament.out");

    printf("\n");
    repetitie(titlu,s);
    free(titlu);
    free(s);
    return 0;
}
