#include <iostream>
#include <fstream>


using namespace std;
ifstream fin("f.in");

struct nod
{
    int x;
    int y;
    nod *next;
};

void adaugInCoada(nod *&prim,nod *&ult, int x,int y)
{
    nod *p;
    p=new nod;
    p->x=x;
    p->y=y;
    if(prim==NULL)
    {
        prim=ult=p;
        p->next=NULL;
    }
    else
    {
        ult->next=p;
        p->next=NULL;
        ult=p;
    }
}


int eliminDinCoada(nod *&prim)
{
    if(prim==NULL)return -1;
    else
    {
        nod *p;
        p=prim;
        prim=prim->next;
        int valoarex,valoarey;
        valoarex=p->x;
        valoarey=p->y;
        delete p;
    }
}


int citire(int a[][101],int &n)
{
    fin>>n;
    int i,j;

    for(i=0;i<n;i++)
       for(j=0;j<n;j++)
           fin>>a[i][j];

    fin.close();
}

int interior(int x,int y,int n)
{
    return (x>=0 && x<n && y>=0 && y<n);
}

void colorare(int a[][101],int n,int x,int y,int nr,nod *&prim,nod *&ult)
{
    //coloram cu culoarea nr componenta ce contine coord x si y
    a[x][y]=nr;

    prim=ult=NULL;
    adaugInCoada(prim,ult,x,y);

    int dx[]={-1,0,1,0};
    int dy[]={0,1,0,-1};

    while(prim!=NULL)
    {
        x=prim->x;
        y=prim->y;
        eliminDinCoada(prim);

        int i;
        for(i=0;i<=3;i++)
        {
            int xv=x+dx[i];
            int yv=y+dy[i];

            if(interior(xv,yv,n) && a[xv][yv]==1)
            {
                adaugInCoada(prim,ult,xv,yv);
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
          cout<<a[i][j]<<' ';
        cout<<'\n';
    }
}


int main()
{
   int a[101][101],n;
   nod *prim,*ult;

   citire(a,n);

    int nr=2;
    int i,j;
    for(i=0;i<n;i++)
       for(j=0;j<n;j++)
         if(a[i][j]==1)
         {
             colorare(a,n,i,j,nr,prim,ult);
             nr++;

         }

    afisare(a,n);
}

