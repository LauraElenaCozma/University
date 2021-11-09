#include <stdio.h>
#include <stdlib.h>

int cmpIntregi(const void *a,const void *b)
{
    int va=*(int *)a;
    int vb=*(int *)b;
    if(va<vb)return -1;
    if(va>vb)return 1;
    return 0;
}

void replaceSiruri(void *a,void *b)
{
    /*char *s=(char **)a;
    char *t=(char *)b;
    memcpy(s,t,sizeof(char *));*/
    char *va=*(char **)a;
    char *vb=*(char **)b;
    printf("%s , %s\n",va,vb);
    free(va);
    va=NULL;
    printf("%s , %s\n",va,vb);
    va=malloc(strlen(vb)+1);
    strcpy(va,vb);
    printf("%s , %s\n",va,vb);
    char *s=(char **)a;
    memcpy(s,&va,sizeof(char *));

}

void replaceInteger(void *a,void *b)
{
    int va=(int *)a;
    int vb=(int *)b;
    memcpy(va,vb,sizeof(int));
}

void inlocuire(void *x,void *y,void *v,int n,int dim,int (*cmp)(const void *,const void *),void replace(void *,void *))
{
    char *p=v;
    int i;
    for(i=0;i<n;i++)
        if(cmp(p+dim*i,x)==0)
        {
           // printf("%d ",i);
            replace(p+i*dim,y);
        }


}

void afisare(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
    printf("\n");
}

int cmpSiruri(const void *a,const void *b)
{
    return strcmp(*(char **)a,(char *)b);
}

int main()
{
    int v[]={3,7,1,7,4,2,7,4,7};
    int x=7;
    int y=10;
    inlocuire(&x,&y,v,9,sizeof(int),cmpIntregi,replaceInteger);
    afisare(v,9);
    char *w[100]={"laura","nu","simte","matematica","laura","laura"};
    char *x1="laura";
    char *y1="finante";
    inlocuire(x1,&y1,w,6,sizeof(char*),cmpSiruri,replaceSiruri);
    int i;
    w[0]="ania";
    for(i=0;i<6;i++)
        printf("%s ",w[i]);
    printf("\n");

    return 0;
}
