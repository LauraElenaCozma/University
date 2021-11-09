#include <iostream>
#include <fstream>
#include <list>
#include <vector>
using namespace std;
ifstream fin("graf.in");

vector <int> viz;
int ok=0;
void df(int x,list <int> *L,int nr)
{
    if(!ok)
    {
        viz[x]=nr;
        for(auto e : L[x])
            if(!viz[e] && !ok)
                df(e,L,nr+1);
            else if(!ok && viz[x]-viz[e]>=2)
                      ok=viz[x]-viz[e]+1;
        viz[x]=0;
    }

}
int main()
{
    int n,m;
    list < int > *L;
    fin>>n;
    L=new list <int> [n+1];

    int x,y;
    for(int i=1;i<=n;i++)
    {
        fin>>x>>y;
        L[x].push_back(y);
        L[y].push_back(x);
    }
    viz.resize(n+1,0);
    df(1,L,1);
    cout<<ok;

    return 0;
}
