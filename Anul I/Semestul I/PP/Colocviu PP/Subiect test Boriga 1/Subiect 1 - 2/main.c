#include <stdio.h>
#include <stdlib.h>

typedef struct
{

    float temp;
    char *nume;

}Oras;



void citire(Oras **v,int *n,char *numeFisier)
{
    FILE *f;
    f=fopen(numeFisier,"r");

    if(f==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }
    (*n)=-1;

    *v=NULL;

    while(1)
    {

        (*n)++;

        Oras *aux2;
        aux2=realloc((*v),(*n+1)*sizeof(Oras));

        if(aux2==NULL)
            {printf("EROARE");return -1;}


        (*v)=aux2;

        (*v)[(*n)].nume=NULL;
        int lung=1;


        char c;
        c=fgetc(f);    ///ATENTIE in fisier citim pana la ultima linie dupa care ajungem la ultimul nr. ultimul fgetc din while citeste '\n' si mai trebuie sa citim separat eof ca sa detectam finalul fisierului        if(c==EOF)break;
       // printf("-%c- \n",c);
        if(c==EOF)break;
        while(c!=' ')
        {
            lung++;
            char *aux;
            aux=realloc((*v)[(*n)].nume,lung*sizeof(char));

            if(aux!=NULL)
            {
                (*v)[(*n)].nume=aux;
                (*v)[(*n)].nume[lung-2]=c;
                (*v)[(*n)].nume[lung-1]='\0';

            }
            c=fgetc(f);
        }


        fscanf(f,"%f",&(*v)[(*n)].temp);

        c=fgetc(f);   ///ATENTIE

      // printf("--%c- \n",c);
       // printf("%s  %.2f   \n",(*v)[(*n)].nume,(*v)[(*n)].temp);


    }

    fclose(f);
}


void maxim(Oras *v,int n,char *numeFisier)
{
    FILE *f;
    f=fopen(numeFisier,"w");

    if(f==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }
    int i;
    int maxi=v[0].temp;
    for(i=1;i<n;i++)
      if(v[i].temp>maxi)
          maxi=v[i].temp;
    fprintf(f,"%d\n",maxi);
    for(i=0;i<n;i++)
        {
            //printf("%s %.2f",v[i].nume,v[i].temp);
            if(v[i].temp==maxi)
           fprintf(f,"%s ",v[i].nume);
        }
    fclose(f);

}



int cmpTemp(const void *a,const void *b)
{
    Oras va=*(Oras *)a;
    Oras vb=*(Oras *)b;
    int ta=va.temp;
    int tb=vb.temp;
    if(ta<tb)return -1;
    if(ta>tb)return 1;
    char *sa=va.nume;
    char *sb=vb.nume;
    if(strcmp(sa,sb)<0)return -1;
    else if(strcmp(sa,sb)>0)return 1;
    return 0;
}


void sortare(Oras *v,int n)
{
    qsort(v,n,sizeof(Oras),cmpTemp);
}
int main()
{
    Oras *v;
    int n;
    citire(&v,&n,"temperaturi.txt");
    sortare(v,n);
    int i;
    for(i=0;i<n;i++)
        printf("%s  %.2f   \n",v[i].nume,v[i].temp);
    maxim(v,n,"maxime.txt");

    return 0;
}
