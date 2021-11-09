#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("graf.in");
ofstream fout("graf.out");

void bfs(int st, vector <int> &viz,vector < vector <int> > E,int n,int m)
{
    queue <int> Q;
    Q.push(st);
    viz[st]=0;

    while(!Q.empty())
    {
        int x=Q.front();
        Q.pop();

        for(auto e : E[x])
            if(viz[e]>viz[x]+1)
        {
            viz[e]=viz[x]+1;
            Q.push(e);
        }
    }

}


int main()
{
    int n,m,x,y,a,b;
    fin>>n>>m>>x>>y;
    vector <int> viz_x(n+1,n+1);
    vector <int> viz_y(n+1,n+1);
    vector <int> viz_dist(n+1,0);

    vector <vector<int> > E(n+1);

    for(int i=1;i<=m;i++)
    {
        fin>>a>>b;
        E[a].push_back(b);
        E[b].push_back(a);
    }

    bfs(x,viz_x,E,n,m);
    bfs(y,viz_y,E,n,m);

    for(int i=1;i<=n;i++)
        if(viz_x[i]+viz_y[i]==viz_x[y])
              viz_dist[viz_x[i]]++;

    int nrvf=0;
    for(int i=1;i<=n;i++)
        if(viz_x[i]+viz_y[i]==viz_x[y] && viz_dist[viz_x[i]]==1)
              nrvf++;

    fout<<nrvf<<'\n';
    for(int i=1;i<=n;i++)
        if(viz_x[i]+viz_y[i]==viz_x[y] && viz_dist[viz_x[i]]==1)
              fout<<i<<' ';
    return 0;
}
