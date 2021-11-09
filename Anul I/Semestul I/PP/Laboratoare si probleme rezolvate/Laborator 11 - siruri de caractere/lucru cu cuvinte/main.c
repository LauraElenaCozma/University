#include <stdio.h>
#include <stdlib.h>

int linii_vide(char *fisier)
{
    FILE *f;
    f=fopen(fisier,"r");

    if(f==NULL)
    {
        printf("Eroare");
        return 0;
    }
  /*  char *cuv,linie[1001];
    cuv=(char *)malloc(1000*sizeof(char));
    fscanf(f,"%s",cuv);
    cuv=realloc(cuv,strlen(cuv)*sizeof(char));*/
    int k=0,nrl=0;
    char linie[1001];
    while(fgets(linie,1001,f)!=NULL)
    {
        nrl++;
        if(strlen(linie)==1){k++;printf("%d ",nrl);}
    }
    fclose(f);
    return k;


}

void rima(char *fisier,int ***a,int *n)
{
    (*a)=NULL;
    (*n)=0;
    FILE *f;
    f=fopen(fisier,"r");

    if(f==NULL)
    {
        printf("Eroare");
        return 0;
    }
    char *cuv,s[1000];
    cuv=(char *)malloc(1000*sizeof(char));
    fscanf(f,"%s",cuv);
    cuv=realloc(cuv,strlen(cuv)*sizeof(char));

    while(fscanf(f,"%s",s)==1)
    {
        int lungs=strlen(s);
        int lungcuv=strlen(cuv);
        if(s[lungs-1]==cuv[lungcuv-1] && s[lungs-2]==cuv[lungcuv-2])
        {
            (*n)++;
            char **aux;
            aux=(char **)realloc((*a),(*n)*sizeof(char *));

            if(aux==NULL)
                return 0;
            (*a)=aux;

            char  *auxs;
            auxs=(char *)malloc(strlen(s)+1);

            if(auxs==NULL)
                return 0;

            (*a)[(*n)-1]=auxs;
            strcpy((*a)[(*n)-1],s);
        }
    }
    fclose(f);
}


int cmpSiruri(const void *a,const void *b)
{
    char *va=*(char **)a;
    char *vb=*(char **)b;
    if(strlen(va)<strlen(vb))return 1;
    else if(strlen(va)==strlen(vb))return 0;
    return -1;
}

void sortare(int **a,int n)
{
    qsort(a,n,sizeof(char *),cmpSiruri);
}
int main()
{

    printf("%d\n",linii_vide("f.in"));
    int i,n;
    char **a;
    rima("f.in",&a,&n);
    sortare(a,n);
    for(i=0;i<n;i++)
        printf("%s\n",a[i]);
    return 0;
}
