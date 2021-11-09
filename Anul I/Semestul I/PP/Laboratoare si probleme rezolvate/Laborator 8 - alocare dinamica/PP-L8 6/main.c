#include <stdio.h>
#include <stdlib.h>

void afisare(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
    printf("\n");
}


void citire(int **v,int *n,int *maxi)
{
    scanf("%d",n);
    int i;

    *v=(int *)malloc((*n)*sizeof(int));

    scanf("%d",&((*v)[0]));
    *maxi=*(*v);
    //printf("\nm1=%d",*maxi);
    for(i=1;i<*n;i++)
       {
           scanf("%d",&((*v)[i]));
           if((*v)[i]>(*maxi))(*maxi)=(*v)[i];
       }

}

void creare(int **v,int *n,int **w,int *m)
{
    int maxi,i;
    citire(v,n,&maxi);
    printf(" maximul este %d \n",maxi);
    int *aux;
    *w=NULL;
    aux=NULL;
    (*m)=0;

    for(i=0;i<*n;i++)
        if((*v)[i]==maxi)
    {

        (*m)++;

        aux=(int *)realloc(*w,(*m)*sizeof(int));

        if(aux==NULL)
        {
            printf("\nNu exista suficient spatiu in memorie %d",i);
            free(*w);
            return ;
        }
        else
        {
            (*w)=aux;
            (*w)[(*m)-1]=i;
            printf("bine!\n");
        }
    }
}

int main()
{
    int n,maxi,*v,m,*w;
    creare(&v,&n,&w,&m);
    //printf("%d\n",n);
    afisare(w,m);
    return 0;
}
