#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;
ifstream fin("catun.in");
ofstream fout("catun.out");


int n,m,k;
const int inf=100000;
vector < pair <int,int> > *L;
vector <int> d,t,fort;
void citire()
{
    fin>>n>>m>>k;
    d.resize(n+1,inf);
    t.resize(n+1);
    fort.resize(k);
    L=new vector < pair <int,int> > [n+1];

    for(int i=0;i<k;i++)
        fin>>fort[i];

    int x,y,c;
    for(int i=1;i<=m;i++)
    {
        fin>>x>>y>>c;
        L[x].push_back({c,y});
        L[y].push_back({c,x});
    }

    for(int i=1;i<=n;i++)
        t[i]=i;
}

void Dijkstra()
{
    set <pair<int,int> > Q;
    for(int i=0;i<k;i++)
    {
        d[fort[i]]=0;

    }
    for(int i=1;i<=n;i++)
        Q.insert({d[i],i});
    vector <int> viz(n+1,0);
    int nr_selectate=0;
    int x,c;
    while(!Q.empty())
    {
        do
        {
            x=Q.begin()->second;
            c=Q.begin()->first;
            Q.erase(Q.begin());
        }
        while(viz[x]);
        viz[x]=1;
        nr_selectate++;
        if(nr_selectate==n)break;

        for(auto y : L[x] )
            if(!viz[y.second] && (y.first+d[x])<d[y.second] )
        {
            d[y.second]=y.first+d[x];
            t[y.second]=t[x];
            Q.insert({d[y.second],y.second});
        }
           else if(!viz[y.second] && (y.first+d[x])==d[y.second] && t[y.second]>t[x])
           {
               t[y.second]=t[x];
           }
    }
}


int main()
{
    citire();
    Dijkstra();
    for(int i=1;i<=n;i++)
        if(t[i]==i)cout<<0<<' ';
        else cout<<t[i]<<' ';
    return 0;
}
