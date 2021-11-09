#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;
ifstream fin("bellmanford.in");
ofstream fout("bellmanford.out");
int n,m;
vector <pair <int,pair<int, int> > > L;
vector <int> d,t;

const int inf = INT_MAX/2;

void citire()
{
    fin>>n>>m;

    int x,y,c;
    for(int i=0;i<m;i++)
    {
        fin>>x>>y>>c;
        L.push_back({c,{x,y}});
    }
}

void bellman_ford(int st)
{
    d.resize(n+1);
    t.resize(n+1);

    for(int i=1;i<=n;i++)
    {
        d[i]=inf;
        t[i]=0;
    }

    d[st]=0;
    int x,y,c;
    for(int i=1;i<=n;i++)
    {
        for(auto e : L)
        {
            c=e.first;
            x=e.second.first;
            y=e.second.second;

            if(d[y]>d[x]+c)
            {
                d[y]=d[x]+c;
                t[y]=x;
            }
        }

    }

    int ok=1;
    for(auto e : L)
    {
        c=e.first;
        x=e.second.first;
        y=e.second.second;

        if(d[y]>d[x]+c)
        {
            fout<<"Ciclu negativ!";
            ok=0;
            break;
        }
    }
    if(ok)
    {
        for(int i=2;i<=n;i++)
            fout<<d[i]<<' ';
    }

}
int main()
{
    citire();
    bellman_ford(1);
    return 0;
}
