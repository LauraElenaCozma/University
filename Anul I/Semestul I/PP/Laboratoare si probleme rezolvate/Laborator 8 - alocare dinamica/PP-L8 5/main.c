#include <stdio.h>
#include <stdlib.h>


void citire(int **v,int *n,char *numeFisier)
{
    FILE *fin;

    fin=fopen(numeFisier,"r");

    if(fin==NULL)
    {
        printf("Eroare la deschiderea fisierului\n");
        return ;
    }

    fscanf(fin,"%d",n);

    (*v)=(int *)malloc((*n)*sizeof(int));
    int i;
    for(i=0;i<(*n);i++)
        fscanf(fin,"%d",((*v)+i));
    fclose(fin);
}


void creare(int **v,int *n,int **neg,int *nrneg,int **poz,int *nrpoz,char *numeFisier)
{
    citire(v,n,numeFisier);

    int i;
     (*nrneg)=0;
     (*nrpoz)=0;
    (*neg)=NULL;
    (*poz)=NULL;
    for(i=0;i<(*n);i++)
        if((*v)[i]<0)
    {
        int *aux;
        (*nrneg)++;
        aux=realloc(*neg,(*nrneg)*sizeof(int));

        if(aux!=NULL)
        {
            (*neg)=aux;
            (*neg)[(*nrneg)-1]=(*v)[i];
        }
    }
       else if((*v)[i]>0)
    {
        int *aux;
        (*nrpoz)++;
        aux=realloc(*poz,(*nrpoz)*sizeof(int));

        if(aux!=NULL)
        {
            (*poz)=aux;
            (*poz)[(*nrpoz)-1]=(*v)[i];
        }
    }
}


void afisare(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
    printf("\n");
}
int main()
{
    int *v,n,*poz,*neg,nrpoz,nrneg;
    creare(&v,&n,&neg,&nrneg,&poz,&nrpoz,"f.in");
    afisare(poz,nrpoz);
    afisare(neg,nrneg);
    return 0;
}
