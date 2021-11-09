#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int x,y;
}Coord;

int citire(int a[][101],int *n)
{
    FILE *f;
    f=fopen("f.in","r");

    if(f==NULL)
        {
            printf("Probleme la deschiderea fisierului\n");
            return -1;
        }

    fscanf(f,"%d",n);

    int i,j;

    for(i=0;i<*n;i++)
       for(j=0;j<*n;j++)
           fscanf(f,"%d",&a[i][j]);

    fclose(f);
}

int interior(int x,int y,int n)
{
    return (x>=0 && x<n && y>=0 && y<n);
}

void colorare(int a[][101],int n,int x,int y,int nr)
{
    //coloram cu culoarea nr componenta ce contine coord x si y
    a[x][y]=nr;

    Coord *c;

    c=(int *)malloc(sizeof(Coord));
    int p=0,u=0;
    c[p].x=x;
    c[p].y=y;

    int dx[]={-1,0,1,0};
    int dy[]={0,1,0,-1};

    while(p<=u)
    {
        x=c[p].x;
        y=c[p++].y;

        int i;
        for(i=0;i<=3;i++)
        {
            int xv=x+dx[i];
            int yv=y+dy[i];

            if(interior(xv,yv,n) && a[xv][yv]==1)
            {
                Coord * aux;

                aux=(int *)realloc(c,(u+2)*sizeof(Coord));
                c[++u].x=xv;
                c[u].y=yv;

                a[xv][yv]=nr;
            }
        }


    }
}




void afisare(int a[][101],int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
          printf("%d ",a[i][j]);
        printf("\n");
    }
}

int main()
{
    int a[101][101],n;
    citire(a,&n);

    int nr=2;
    int i,j;
    for(i=0;i<n;i++)
       for(j=0;j<n;j++)
         if(a[i][j]==1)
         {
             colorare(a,n,i,j,nr);
             nr++;

         }

    afisare(a,n);
    return 0;
}

