#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
ifstream fin("date.in");
vector <int> t,viz;
vector <int > *E;
vector <int> control;
int n,m;

void citire()
{
    int x,y;
    fin>>n>>m;
    E=new vector <int> [n+1];
    for(int i=1;i<=m;i++)
    {
        fin>>x>>y;
        E[x].push_back(y);
        E[y].push_back(x);
    }
    int nr_pct_control;
    fin>>nr_pct_control;
    control.resize(n+1,0);
    int c;
    for(int i=1;i<=nr_pct_control;i++)
    {
        fin>>c;
        control[c]=1;
    }

}

void afis_drum(int x)
{
    if(x!=0)
        {
         afis_drum(t[x]);
         cout<<x<<' ';
        }
}


void bfs(int st)
{
    queue <int> Q;
    Q.push(st);

    t.resize(n+1,0);
    viz.resize(n+1,-1);
    viz[st]=0;
    int ok=0;
    while(! Q.empty() && !ok)
    {
        int x=Q.front();
        Q.pop();

        for(int y : E[x])
            if(viz[y]==-1)
        {
            Q.push(y);
            viz[y]=viz[x]+1;
            t[y]=x;
            if(control[y]) {ok=y; break;}
        }
    }

    if(ok)
    {   afis_drum(ok);
        cout<<'\n'<<viz[ok];
    }

}


int main()
{
    citire();
    bfs(7);
    return 0;
}
