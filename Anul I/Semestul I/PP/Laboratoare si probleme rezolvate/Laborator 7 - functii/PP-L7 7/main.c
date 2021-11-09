#include <stdio.h>
#include <stdlib.h>

void minim_coloana(int **a,int n,int i)
{
    int mini=a[0][i];
    int j;
    for(j=1;j<n;j++)
        if(mini>a[j][i])
           mini=a[j][i];
    a[n][i]=mini;
}

void maxim_coloana(int **a,int n,int i)
{
    int maxi=a[0][i];
    int j;
    for(j=1;j<n;j++)
        if(maxi<a[j][i])
           maxi=a[j][i];
    a[n+1][i]=maxi;
}


void citire(int ***a,int *n,char *numeFisier)
{
    FILE *fin;

    fin=fopen(numeFisier,"r");
    fscanf(fin,"%d",n);

    if(fin==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }


    (*a)=(int **)malloc((*n+2)*sizeof(int *));

    int i,j;
    for(i=0;i<((*n)+2);i++)
        {
            (*a)[i]=malloc((*n)*sizeof(int));
            for(j=0;j<*n;j++)
                fscanf(fin,"%d",&(*a)[i][j]);

        }
    fclose(fin);
}


void afisare(int **a,int n)
{
     int i,j;
     for(i=0;i<n+2;i++)
     {
         for(j=0;j<n;j++)
            printf("%d ",a[i][j]);
        printf("\n");
     }

}

int minim_linie(int **a,int n,int i)
{
    int mini=a[i][0];
    int j;
    for(j=1;j<n;j++)
        if(mini>a[i][j])
           mini=a[i][j];
    return mini;
}

int maxim_linie(int **a,int n,int i)
{
    int maxi=a[i][0];
    int j;
    for(j=1;j<n;j++)
        if(maxi<a[i][j])
           maxi=a[i][j];
    return maxi;
}




void sa(int **a,int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        maxim_coloana(a,n,i);
        minim_coloana(a,n,i);
    }
    for(i=0;i<n;i++)
    {   int maxlin=maxim_linie(a,n,i);
        int minlin=minim_linie(a,n,i);
        //printf("\nmin=%d  max%d   \n",minlin,maxlin);
        for(j=0;j<n;j++)
            if((a[i][j]==maxlin && a[i][j]==a[n][j])|| (a[i][j]==minlin && a[i][j]==a[n+1][j]))
                printf("%d ",a[i][j]);
    }
}

int main()
{
    int **a,n;
    citire(&a,&n,"matrice.txt");
    sa(a,n);
    //afisare(a,n);

    return 0;
}
