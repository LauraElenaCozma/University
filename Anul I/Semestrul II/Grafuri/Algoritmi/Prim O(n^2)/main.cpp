#include <iostream>
#include <climits>
#include <fstream>
#include <list>
#include <vector>
using namespace std;

ifstream fin("apcm.in");

void citire(list <pair <int,int> > *&L,int &n,int &m)
{
    fin>>n>>m;
    L=new list<pair<int,int> > [n+1];

    int x,y,c;
    for(int i=0;i<m;i++)
    {
        fin>>x>>y>>c;
        L[x].push_back({c,y});
        L[y].push_back({c,x});
    }
}

void Prim(list <pair <int,int> > *L,int n,int m, vector <pair <int,int> > &E)
{
    const int inf=10000;
    vector <int> d(n+1,inf);
    vector <int> t(n+1,0);
    vector <int> viz(n+1,0);

    d[1]=0;

    for(int i=1;i<=n;i++)        ///O(n)
    {
        int mini=INT_MAX;
        int vmin=-1;
        for(int j=1;j<=n;j++)    ///O(n)
            if(!viz[j] && d[j]<mini)
            {
                mini=d[j];
                vmin=j;
            }
        viz[vmin]=1;
        E.push_back({vmin,t[vmin]});

        for(auto e : L[vmin])
            if(!viz[e.second] && e.first<d[e.second])
        {
            d[e.second]=e.first;
            t[e.second]=vmin;
        }
    }

    E.erase(E.begin());

}
int main()
{
    int n,m;
    list <pair <int,int> > *L;
    vector <pair <int,int> > E;
    citire(L,n,m);
    Prim(L,n,m,E);
    for(auto e : E)
        cout<<e.first<<' '<<e.second<<'\n';
    return 0;
}
