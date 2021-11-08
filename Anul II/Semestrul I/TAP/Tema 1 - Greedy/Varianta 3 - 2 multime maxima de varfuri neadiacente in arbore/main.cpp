#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;

ifstream fin("f.in");

vector < list <int> > L;
vector <int> visited;
vector <int> sel;
vector <int> tata;
int nr;

void df(int vf)
{
    visited[vf]=1;

    for(int e : L[vf])
        if(!visited[e])
            df(e);

    if(sel[vf]==0)
    {
        nr++;
        sel[tata[vf]]=1;
    }
}


int main()
{
    int n,x,y,m;

    fin>>n>>m; //m==n-1


    L.resize(n+1);
    sel.resize(n+1);
    visited.resize(n+1);
    tata.resize(n+1);

    tata[1]=0;

    for(int i=0;i<n-1;i++)
    {
        fin>>x>>y;
        L[x].push_back(y);
        L[y].push_back(x);
        tata[y]=x;
    }

    df(1);
    cout<<nr<<'\n';
    for(int i=1;i<=n;i++)
        if(!sel[i])
            cout<<i<<' ';
    return 0;
}


/*
13 12
1 2
1 3
2 4
2 5
3 6
3 7
5 8
4 9
4 10
4 11
6 12
5 13

*/
