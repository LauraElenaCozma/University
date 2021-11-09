#include <iostream>
#include <climits>
#include <fstream>
#include <list>
#include <vector>
#include <set>

using namespace std;
#define inf INT_MAX/2
ifstream fin("grafpond.in");

void citire(list <pair <int,int> > * &L,int &n,int &m,vector <int> &c,int &st)
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

    int k,val;
    fin>>k;
    c.resize(n+1);
    for(int i=1;i<=n;i++)
        c[i]=0;
    for(int i=0;i<k;i++)
    {
        fin>>val;
        c[val]=1;
    }



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


void afis_drum(vector <int> t,int vf)
{
    if(t[vf]!=0)
    {
        afis_drum(t,t[vf]);
        cout<<vf<<' ';
    }else cout<<vf<<' ';
}

void Dijkstra(list <pair <int,int> > L[100],int &n,int &m,int &st,vector <int> &t,vector <int> &d,vector <int> c)
{

    set <pair <int,int> > Q;
    initializare(t,d,n,st);

    for(int i=1;i<=n;i++)
        Q.insert({d[i],i});
    vector <int > s(n+1,0);

    int nrsel=0;
    int x;
    while(nrsel!=n)
    {

        do
        {
            x=Q.begin()->second;
            Q.erase(Q.begin());

        }
        while(s[x]==1);

        if(c[x])break;

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


    cout<<"Distanta este: "<<d[x]<<"\nIar drumul este: ";
    afis_drum(t,x);

}

int main()
{
    list <pair <int,int> > *L;
    int n,m,st;
    vector <int> t;
    vector <int> d;
    vector <int> c;
    citire(L,n,m,c,st);

    Dijkstra(L,n,m,st,t,d,c);
    return 0;
}
