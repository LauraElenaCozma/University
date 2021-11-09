#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <climits>
using namespace std;
#define INF INT_MAX/2


struct edge
{
    int nod;
    int cost;
};

class CompareEdge
{
public:
    bool operator()(const edge & a,const edge & b)
    {
        return a.cost>b.cost;
    }
};
class Graf
{
    vector < vector <edge> > G;//un graf G reprezintat sub forma unor liste de adiacenta
    int n;//nr noduri

public:
    Graf()
    {
        n=0;
    }
    void citire();
    void afisare();
    void Dijkstra(int s,int *d);

};

void Graf::citire()
{
    ifstream fin("date.in");
    fin>>n;

    G.resize(n+1);  //nu folosim pozitia 0
    int nr_much,x,y,c;
    fin>>nr_much;

    for(int i=1;i<=nr_much;i++)
    {
        fin>>x>>y>>c;

        edge e;
        e.nod=y;
        e.cost=c;
        G[x].push_back(e);
    }

    fin.close();
}


void Graf::afisare()
{
    for(int i=1;i<=n;i++)
    {
        cout<<'\n';
        cout<<i<<" : ";
        for(edge e: G[i])
            cout<<e.nod<<' ';
    }
}

void Graf::Dijkstra(int s,int *d)
{
    d=new int[n+1];

    for(int i=1;i<=n;i++)
        d[i]=INF;

    d[s]=0;

    priority_queue <edge,vector < edge> , CompareEdge> Q;

    edge e;
    e.nod=s;
    e.cost=0;

    Q.push(e);

    while(!Q.empty())
    {
        edge x=Q.top();

        Q.pop();

        for(edge e: G[x.nod])
        {
            if(d[e.nod]>e.cost+d[x.nod])
            {
                d[e.nod]=e.cost+d[x.nod];
                edge aux;
                aux.nod=e.nod;
                aux.cost=d[e.nod];
                Q.push(aux);
            }
        }
    }
    cout<<'\n';
    for(int i=1;i<=n;i++)
        if(d[i]==INF)cout<<"INF ";
        else cout<<d[i]<<' ';
}
int main()
{
    Graf gf;
    gf.citire();
    gf.afisare();
    int *d;
    gf.Dijkstra(1,d);

    delete[] d;
    return 0;
}
