#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
ifstream fin("graf.in");
int n,m,ok=1;
vector <int> gr;
vector <vector <int> > E;
vector <int> TS;


void citire()
{
    fin>>n>>m;
    int x,y;

    gr.resize(n+1,0);
    E.resize(n+1);
    for(int i=1;i<=m;i++)
    {
        fin>>x>>y;
        E[x].push_back(y);
        gr[y]++;
    }
}

void top_sort()
{
    queue <int> Q;

    for(int i=1;i<=n;i++)
        if(gr[i]==0)Q.push(i);
    int x;
    while(! Q.empty())
    {
        x=Q.front();
        TS.push_back(x);
        Q.pop();

        for(auto e : E[x])
        {
            gr[e]--;
            if(!gr[e]) Q.push(e);
        }
    }

    if(TS.size()!=n)ok=0;
}

vector <int> rez_ciclu;
int gasit=0;
void ciclu(int x,vector <int> viz,int nrviz)
{
    if(!gasit)
    {
        viz[x]=nrviz;
        rez_ciclu.push_back(x);

        for(auto e: E[x])
            if(!viz[e] && !gasit)
                ciclu(e,viz,nrviz+1);

            else if(viz[x]-viz[e]>=2 && !gasit)   //putem sa gasim ciclul, dar dupa for ul continua desi l-am gasit
            {
                gasit=1;
                rez_ciclu.push_back(e);

                for(int i=0;i<rez_ciclu.size();i++)
                    cout<<rez_ciclu[i]<<' ';
            }
        viz[x]=0;
        rez_ciclu.pop_back();
    }

}




int main()
{
    citire();
    top_sort();

    if(ok)cout<<"REALIZABIL\n";
    else
    {
        for(int i=1;i<=n;i++)
            if(gr[i])
        {
            vector <int> viz(n+1,0);
            ciclu(i,viz,1);
        }
    }
    return 0;
}
