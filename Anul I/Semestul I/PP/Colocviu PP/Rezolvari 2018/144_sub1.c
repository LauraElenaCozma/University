#include <stdio.h>
#include <stdlib.h>

void citire(char*numeFisier,long long int **v,int *n)
{
    //functie care citeste nr din fisier
    FILE *f=fopen(numeFisier,"r");
    if(f==NULL)return ;

    (*v)=NULL;
    (*n)=0;
    long long int x;
    while(fscanf(f,"%lld",&x)==1)
    {
        (*n)++;
        long long int *aux;
        aux=(long long int *)realloc((*v),(*n)*sizeof(long long int));

        if(aux==NULL)return;

        (*v)=aux;

        (*v)[(*n)-1]=x;

    }

    fclose(f);
}


int nrcif(long long int x)
{
    //calculeaza nr de cifre a unui nr
    int nr=0;
    while(x!=0)
    {
        nr++;
        x/=10;
    }
    return nr;
}

int pozitiv(long long int x,int p)
{   //un nr are p cifre si e strict pozitiv
    if(x>0)
    {
        int nr=nrcif(x);
        if(nr==p)return 1;
    }
    return 0;
}
void creare(long long int *v,int n,long long int **w,int *m,int(*crit)(long long int ,int ))
{

    int i;
    (*w)=NULL;
    (*m)=0;
    int p;
    printf("p=");
    scanf("%d",&p);
    for(i=0;i<n;i++)
        if(crit(v[i],p)==1)
    {
        (*m)++;
        long long int *aux;
        aux=(long long int *)realloc((*w),(*m)*sizeof(long long int));

        if(aux==NULL)return ;

        (*w)=aux;
        (*w)[(*m)-1]=v[i];
    }

}

void afisare(char *numeFisier,long long int *v,int n)
{
    FILE *f;
    f=fopen(numeFisier,"a");
    //fisierul e deschis cu "a" pentru ca adaugam in continuare
    if(f==NULL)return ;

    if(n==0)fprintf(f,"\nNu exista numere care sa respecte criteriul");
    else
    {
    int i;
    for(i=0;i<n;i++)
        fprintf(f,"%lld ",v[i]);
    fprintf(f,"\n");
    }


    fclose(f);
}

int main()
{
    int n,m,p;
    long long int *v,*w;

    citire("numere.txt",&v,&n);
    creare(v,n,&w,&m,pozitiv);
    afisare("numere.txt",w,m);

    free(v);
    free(w);
    return 0;
}
