#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <fstream>
#include <climits>
using namespace std;
ifstream fin("parc.in");
ofstream fout("parc.out");

list <pair <int,int> > * L;
int nr_p;
vector <int> P;

const int inf=INT_MAX/2;
void citire(int &n,int &m,int &C)
{
    fin>>n>>m>>C;

    P.resize(n+1,0);
    L=new list <pair <int , int> > [n+1];
    int x,y,cost;

    for(int i=1;i<=m;i++)
    {
        fin>>x>>y>>cost;
        L[x].push_back({cost,y});
        L[y].push_back({cost,x});
    }

    fin>>nr_p;
    for(int i=1;i<=nr_p;i++)
    {
        fin>>x;
        P[x]=1;
    }


}


void dijkstra(int n,int C)   //aflam drumul minim din C pana la toate celelalte intersectii, dar ne oprim cand am vizitat toate portile
{
    vector <int> viz(n+1,0);
    vector <int> d(n+1,inf);
    d[C]=0;
    set <pair <int,int> > Q;

    Q.insert({d[C],C});
    int  nrsel=0,x,cost;
    while(!Q.empty())
    {
        do
        {
            x=Q.begin()->second;
            cost=Q.begin()->first;
            Q.erase(Q.begin());
        }
        while(viz[x]);

        viz[x]=1;
        if(P[x]) nrsel++;
        if(nrsel==nr_p)break;

        for(auto y : L[x])
            if(d[y.second]>cost+y.first)
        {
            d[y.second]=cost+y.first;
            Q.insert({d[y.second],y.second});
        }
    }
    int minim=inf;
    int poarta_apropiata=0;

    for(int i=1;i<=n;i++)
        if(P[i])
        {
            if(d[i]<minim)
            {
                minim=d[i];
                poarta_apropiata=i;
            }
        }

    cout<<poarta_apropiata;
}

int main()
{
    int n,m,C;
    citire(n,m,C);
    dijkstra(n,C);
    fin.close();
    fout.close();
    return 0;
}
