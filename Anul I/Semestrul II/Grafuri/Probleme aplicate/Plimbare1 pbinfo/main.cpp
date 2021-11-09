#include <iostream>
#include <fstream>
#include <set>
#include <list>
#include <vector>
using namespace std;
ifstream fin("plimbare1.in");
void citire(list <pair <int, int > > *&L,int &n,int &m)
{
    fin>>n>>m;

    L=new list <pair <int, int > > [n+1];

    int nr,x,y,c;
    for(int i=1;i<=m;i++)
    {
        fin>>nr;
        if(nr==1)
        {
            fin>>x>>y;
            c=0;
        }
        else fin>>x>>y>>c;

        L[x].push_back({c,y});
        L[y].push_back({c,x});
    }
}

void prim(list <pair <int, int > > *L,int n,int m,int st)
{
    vector <int> d(n+1,100000);
    vector <int> viz(n+1,0);
    vector <int> t(n+1,0);

    set <pair <int,int> > Q;

    Q.insert({0,st});
    d[st]=0;
    int nr_selectate=0,s=0,x,c;
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
        s+=c;

        for(auto y : L[x])
            if(!viz[y.second] && d[y.second]>y.first)
        {
            d[y.second]=y.first;
            t[y.second]=x;
            Q.insert(y);
        }

        if(nr_selectate==n)break;

    }

    cout<<s;

}
int main()
{
    list <pair <int, int > > *L;
    int n,m;
    citire(L,n,m);
    prim(L,n,m,1);
    return 0;
}
