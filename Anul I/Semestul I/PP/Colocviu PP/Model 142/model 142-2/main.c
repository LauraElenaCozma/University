#include <stdio.h>
#include <stdlib.h>


///nu e facut ultimul subpunct
int litera(char c)
{
    if((c>='a' && c<='z')|| (c>='A' && c<='Z'))return 1;
    return 0;
}
void citire(char *nume,char **s)
{
    FILE *f;
    f=fopen(nume,"r");
    if(f==NULL)
        return ;
    (*s)=(char *)malloc(2*sizeof(char));
    int lung=2;
    char c;
    c=fgetc(f);
    (*s)[lung-1]='\0';
    (*s)[lung-2]=c;

    while((c=fgetc(f))!=EOF)
    {
        lung++;
        char *aux;
        aux=realloc((*s),lung*sizeof(char));

        if(aux==NULL)return ;
        (*s)=aux;
        (*s)[lung-1]='\0';
        (*s)[lung-2]=c;
    }


   // printf("%s",(*s));
    fclose(f);
}


void cuvinte(char *s,char ***cuv,int *nr)
{
    char *p;
    (*nr)=0;
    (*cuv)=NULL;
    p=strtok(s," ,.?!\n");
    while(p)
    {
        (*nr)++;
        char **aux;
        aux=realloc((*cuv),(*nr)*sizeof(char *));
        if(aux==NULL)
            return ;
        (*cuv)=aux;
        int lung=strlen(p);
        (*cuv)[(*nr)-1]=malloc((lung+1)*sizeof(char));
        strcpy((*cuv)[(*nr)-1],p);

        p=strtok(NULL," ,.?!\n");
    }
}

void afisare(char **cuv,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("%s ",cuv[i]);
        if((i+1)%3==0)printf("\n");
    }
}

int main()
{
    char *s,**cuv;
     int n;
    citire("text.in",&s);
    cuvinte(s,&cuv,&n);
    afisare(cuv,n);
    return 0;
}
