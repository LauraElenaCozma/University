#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
ifstream fin("grafpond.in");
const int inf=0;
void citire(int a[][100],int &n,int &m,int P[][100])
{
    int x,y,c;
    fin>>n>>m;

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(i==j)a[i][j]=0;
            else a[i][j]=inf;
            P[i][j]=0;
        }


    for(int i=1;i<=n;i++)
    {
        fin>>x>>y>>c;
        a[x][y]=c;
        a[y][x]=c;
        P[x][y]=x;
        P[y][x]=y;
    }
}

void roy_warshall(int a[][100],int n,int P[][100])
{
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
               if(a[i][j]>a[i][k]+a[k][j])
                {
                    a[i][j]=a[i][k]+a[k][j];
                    P[i][j]=P[k][j];
                }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
                cout<<a[i][j]<<' ';
            cout<<'\n';
        }

        cout<<'\n'<<'\n';

    }

}

int main()
{
    int a[100][100],P[100][100],n,m;
    citire(a,n,m,P);
    roy_warshall(a,n,P);

    /*for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            cout<<a[i][j]<<' ';
        cout<<'\n';
    }*/


    return 0;
}
