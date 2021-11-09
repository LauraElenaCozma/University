#include <stdio.h>
#include <stdlib.h>

void citire(int **v,int *n)
{
    scanf("%d",n);


    (*v)=(int *)malloc((*n)*sizeof(int));
    int i;
    for(i=0;i<*n;i++)
    {
        scanf("%d",&(*v)[i]);
    }
}

int caut(int *v,int n,int x)
{
    int i;
    for(i=0;i<n;i++)
        if(v[i]==x)return 1;
    return 0;
}

void distinct(int *v,int n,int **w,int *m)
{
    (*m)=1;
    (*w)=malloc(sizeof(int));
    (*w)[0]=v[0];
    int i;
    for(i=1;i<n;i++)
    {
        int ok=caut((*w),(*m),v[i]);
        if(!ok)
        {
            int *aux;
            (*m)++;
            aux=realloc(*w,(*m+1)*sizeof(int));
            if(aux==NULL)
            {
                printf("Nu exista suficient spatiu");
                return ;
            }
            (*w)=aux;
            (*w)[(*m)-1]=v[i];
        }
    }

}
void afisare(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d  ",v[i]);
    printf("\n");
}


void reuniune(int **v,int *n,int *w,int m)
{

    int i;
    int *aux;
    for(i=0;i<m;i++)
    {
        int ok=caut((*v),(*n),w[i]);
        if(!ok)
        {
            (*n)++;
            aux=realloc(*v,(*n)*sizeof(int));

            if(aux==NULL)
            {
                printf("Nu exista suficient spatiu");
                return ;
            }

            (*v)=aux;
            (*v)[(*n)-1]=w[i];
        }
    }
    aux=(*v);
    int nr=*n;
    afisare(aux,nr);

}



int main()
{
    int *v,n,*w,m,*t,nr;
    citire(&v,&n);
    citire(&w,&m);
    distinct(v,n,&t,&nr);
    reuniune(&t,&nr,w,m);
    free(v);
    return 0;
}
