#include <iostream>
#include <fstream>
#include <climits>
using namespace std;
ifstream fin("firma.in");
ofstream fout("firma.out");

int a[102][102];
const int inf=INT_MAX/2;

void citire(int &n,int&m)
{
    fin>>n>>m;

    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
        if(j==0 || i==j)a[i][j]=0;
        else a[i][j]=inf;
    int x,y,L;
    for(int i=1;i<=m;i++)
    {
        fin>>x>>y>>L;
        a[x][y]=L;
        a[y][x]=L;
    }

}

void roy_warshall(int n)
{
    for(int k=1;k<=n;k++)
       {
           for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(a[i][k]+a[k][j]<a[i][j])
                    a[i][j]=a[i][k]+a[k][j];
       }

    int minim=inf;
    int firma=0;
    for(int i=1;i<=n;i++)
    {
        int s=0;
        for(int j=1;j<=n;j++)
            s+=a[i][j];
        a[i][0]=s;
        if(s<minim)
        {
            minim=s;
            firma=i;
        }
    }

    cout<<firma;

}
int main()
{
    int n,m;
    citire(n,m);
    roy_warshall(n);
    return 0;
}
