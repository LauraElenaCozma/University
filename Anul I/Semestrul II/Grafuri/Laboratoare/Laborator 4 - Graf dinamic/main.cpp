#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <fstream>
using namespace std;
ifstream fin("grafpond.in");
ofstream fout("apm.out");
list <pair <int , int> > *L;
list <pair<int,int> > *A;
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

int S;

void Prim(int start,int n,int m)
{
    const int inf=10000;
    vector <int> viz(n+1,0);
    vector <int> t(n+1,0);
    vector <int> d(n+1,inf);

    A=new list <pair <int,int> > [n+1];
    d[start]=0;

    Q.push({0,start});

    int x,y,c,nrs=0;

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

        A[x].push_back(make_pair(t[x],-c));
        A[t[x]].push_back(make_pair(x,-c));

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

    A[1].erase(A[1].begin());
    cout<<"Muchiile apcm in G sunt: \n";

    for(int i=1;i<=n;i++)
        for(auto e: A[i])
          cout<<i<<' '<<e.first<<' '<<e.second<<'\n';
    cout<<"Cost "<<S<<'\n';

}

vector <int> v(1000,0);
vector <pair< int, pair<int,int> > > sol;
pair <int, pair<int,int> > p({INT_MIN,make_pair(0,0)});
vector <pair <int, pair<int,int> > > drum;
void dfs(int start,int end,int cost)
{
    v[start]=1;



    if(start==end)
        {
            for(auto e: drum)
                cout<<e.second.first<<' '<<e.second.second<<'\n';
            for(auto e: drum)
                if(e.first>p.first)
                     p=e;
            cout<<p.first<<' '<<p.second.first<<' '<<p.second.second<<'\n';
            if(p.first<cost)cout<<"mai rau";
            else cout<<"mai bun cu noul cost "<<S+cost-p.first;

        }
    else
    {
        for(auto e : A[start])
        if(!v[e.first])
        {
            drum.push_back({e.second,make_pair(start,e.first) });
            dfs(e.first,end,cost);
            drum.pop_back();
        }



    }


}

int main()
{
    int n,m;
    citire(n,m);
    Prim(1,n,m);
    dfs(2,1,8);

    fin.close();
    return 0;
}
