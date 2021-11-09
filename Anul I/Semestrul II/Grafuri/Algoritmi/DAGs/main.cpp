#include <iostream>
#include <fstream>
#include <list>
#include <vector>
using namespace std;
ifstream fin("graf.in");
#define inf 100000

void citire(list <pair<int, int > > L[],int &n,int &m,vector <int> &gr,int &st)
{
    fin>>n>>m;

    gr.resize(n+1);

    for(int i=1;i<=n;i++)
        gr[i]=0;

    int x,y,c;
    for(int i=1;i<=m;i++)
        {
            fin>>x>>y>>c;
            L[x].push_back({y,c});
            gr[y]++;
        }

    fin>>st;


}


void Top_Sort(list <pair <int, int > > L[],int n,vector <int> &gr,vector <int> &ts)
{
    for(int i=1;i<=n;i++)
        if(!gr[i])ts.push_back(i);

    int p=0;
    while(ts.size()!=n)
    {
        int ult=ts.size();
        while(p!=ult)
        {
            for(pair <int,int> x : L[ts[p]])
            {
                gr[x.first]--;
                if(!gr[x.first])ts.push_back(x.first);
            }
            p++;
        }
    }

}


void initializare(vector <int> &t, vector <int> &d,int n,int st)
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

void DAG(list <pair <int,int> > L[],int n,vector <int> &gr,int st,vector <int> &d,vector <int> &t)
{
    vector <int> ts;
    initializare(t,d,n,st);

    Top_Sort(L,n,gr,ts);

    for(int i=0;i<n;i++)
    {
        int x=ts[i];
        for(pair<int,int> y : L[x])
        {
            int nod=y.first;
            int cost=y.second;

            if(d[nod]>d[x]+cost)
            {
                d[nod]=d[x]+cost;
                t[nod]=x;
            }
        }
    }

}


int main()
{
    list <pair<int, int > > L[100];
    vector <int> gr,d,t;
    int n,m,st;

    citire(L,n,m,gr,st);

    /*for(int i=1;i<=n;i++)
    {
        cout<<"\n"<<i<<": ";
        for(int x : L[i])
            cout<<x<<' ';
    }*/

    DAG(L,n,gr,st,d,t);

    for(int i=1;i<=n;i++)
        cout<<d[i]<<' ';
    return 0;
}
