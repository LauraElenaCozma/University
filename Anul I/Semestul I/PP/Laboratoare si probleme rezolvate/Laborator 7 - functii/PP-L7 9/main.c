#include <stdio.h>
#include <stdlib.h>

void citire(int **v,int *n,char * numeFisier)
{
    FILE * fin=fopen(numeFisier,"r");

    if(fin==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }

    int i;
    fscanf(fin,"%d",n);

    (*v)=(int *)malloc((*n)*sizeof(int));
    for(i=0;i<(*n);i++)
        fscanf(fin,"%d",(*v)+i);
}


void afisare(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",*(v+i));
    printf("\n");
}


void schimbaSemn(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        v[i]=-v[i];
}

int valpoz(int *v,int n,int **w,int *m)
{
    (*w)=NULL;
    (*m)=0;

    int *aux;
    int i;
    for(i=0;i<n;i++)
        if(*(v+i)>0)
    {
        (*m)++;
        aux=(int *)realloc(*w,(*m)*sizeof(int));

        if(aux!=NULL)
        {
            (*w)=aux;
            *(*w+((*m)-1))=*(v+i);
        }
        else return ;
    }

}


void valneg(int *v,int n,int **w,int *m)
{
    schimbaSemn(v,n);
    valpoz(v,n,w,m);
}
int main()
{
    int *v,n,*w,m;
    citire(&v,&n,"f.in");
    valpoz(v,n,&w,&m);
    afisare(w,m);

    valneg(v,n,&w,&m);
    schimbaSemn(w,m);
    afisare(w,m);
    return 0;
}
