#include <iostream>
#include <climits>
#include <fstream>
#include <list>
#include <vector>
#include <set>

using namespace std;
#define inf INT_MAX/2
ifstream fin("graf.in");

void citire(list <pair <int,int> > * &L,int &n,int &m,int &st)
{
    fin>>n>>m;
    L=new list<pair<int,int> >[n+1];
    int x,y,p;
    for(int i=0;i<m;i++)
    {
        fin>>x>>y>>p;
        L[x].push_back({p,y});
        L[y].push_back({p,x});
    }

    fin>>st;
}

void initializare(vector <int> &t,vector <int> &d, int n,int st)
{
    t.resize(n+1);
    d.resize(n+1);
    for(int i=1;i<=n;i++)
    {
        t[i]=0;
        d[i]=inf;

    }

    d[st]=0;

}

void Dijkstra(list <pair <int,int> > *L,int n,int m,int st,vector <int> &t,vector <int> &d)
{

    set <pair <int,int> > Q;
    initializare(t,d,n,st);

    for(int i=1;i<=n;i++)
        Q.insert({d[i],i});
    vector <int > s(n+1,0);

    int nrsel=0;
    while(nrsel!=n)
    {
        int x;
        do
        {
            x=Q.begin()->second;
            Q.erase(Q.begin());

        }
        while(s[x]==1);
        s[x]++;
        nrsel++;

        for(pair <int,int> pr: L[x])
        {
            int y=pr.second;
            int p=pr.first;

            if(d[y]>d[x]+p)
            {
                d[y]=d[x]+p;
                t[y]=x;
                Q.insert({d[y],y});
            }
        }
    }


    for(int i=1;i<=n;i++)
    {
        cout<<d[i]<<' ';
    }
    cout<<'\n';
    for(int i=1;i<=n;i++)
    {
        cout<<t[i]<<' ';
    }
}

int main()
{
    list <pair <int,int> > *L;
    int n,m,st;
    vector <int> t;
    vector <int> d;
    citire(L,n,m,st);

    Dijkstra(L,n,m,st,t,d);
    return 0;
}
