#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void afis(int **a,int m,int n)
{
    if(m!=0)
    {
        afis(a,m-1,n);
        if(n!=0)
        {
            afis(a,m,n-1);
            printf("%d ",a[m-1][n-1]);
        }


    }
}

void citire(int ***a,int *m,int *n)
{
    scanf("%d%d",m,n);
    int i,j;
    (*a)=(int **)malloc((*m)*sizeof(int *));
    for(i=0;i<*m;i++)
    {
        (*a)[i]=(int *)malloc((*n)*sizeof(int));
        for(j=0;j<*n;j++)
           scanf("%d",&(*a)[i][j]);

    }
}

int nr_lit_mici(char *s)
{
    if(s[0]=='\0')
         return 0;
    else
    {
        if(s[0]>='a' && s[0]<='z')
            return 1+nr_lit_mici(s+1);
        else return nr_lit_mici(s+1);
    }

}


int main()
{
    int **a,m,n;
    //citire(&a,&m,&n);
    //afis(a,m,n);
    char *s="AligaToRUl  Uff";
    printf("%d",s);
    //printf(" %d",nr_lit_mici(s));
    return 0;
}
