#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <fstream>
using namespace std;
ifstream fin("apm.in");
ofstream fout("apm.out");
list <pair <int , int> > *L;
vector <pair<int,int> > A;
priority_queue < pair <int,int> >  Q;


void citire(int &n,int &m)
{
    fin>>n>>m;
    int x,y,c;

    L=new list <pair <int,int> > [n+1];

    for(int i=0;i<m;i++)
    {
        fin>>x>>y>>c;
        L[x].push_back({-c,y});
        L[y].push_back({-c,x});
    }
}

void Prim(int start,int n,int m)
{
    const int inf=10000;
    vector <int> viz(n+1,0);
    vector <int> t(n+1,0);
    vector <int> d(n+1,inf);

    d[start]=0;

    Q.push({0,start});

    int x,y,c,S=0,nrs=0;

    while(!Q.empty() && nrs!=n)
    {
        do
        {
            x=Q.top().second;
            c=Q.top().first;
            Q.pop();
        }
        while(viz[x]);

        nrs++;
        viz[x]=1;
        S-=c;  //am introdus in lista costurile cu semn schimbat(pentru a se face ordinea corecta in priority queue), iar acum trebuie sa le adunam in loc sa le scadem

        A.push_back(make_pair(x,t[x]));

        for(auto e : L[x])
        {
            y=e.second;
            int cost=e.first;

            if(!viz[y] && d[y]>-cost)
            {
                d[y]=-cost;
                t[y]=x;

                Q.push(e);
            }
        }

    }

    A.erase(A.begin());
    fout<<S<<'\n'<<A.size()<<'\n';

    for(auto e: A)
        fout<<e.first<<' '<<e.second<<'\n';

}

int main()
{
    int n,m;
    citire(n,m);
    Prim(1,n,m);
    fin.close();
    return 0;
}
