#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;
ifstream fin("graf.in");
vector <int> t,h;
list <pair <int,int> > *L;
vector <pair <int, pair <int,int> > > E;

int n,m,k;
void citire()
{
    fin>>n>>m;
    cout<<n<<' '<<m<<'\n';
    fin>>k;
    L=new list<pair <int,int> >[n+1];
   // E.resize(n+1);
    int x,y,c;
    for(int i=1;i<=m;i++)
    {
        fin>>x>>y>>c;
        cout<<x<<' '<<y<<' '<<c<<'\n';
        pair <int,int> p(x,y);
        E.push_back({c,p});
        L[x].push_back({c,y});
        L[y].push_back({c,x});

    }

}

void initializare()
{
    h.resize(n+1);
    t.resize(n+1);
    for(int i=1;i<=n;i++)
    {
        h[i]=0;
        t[i]=i;
    }
}


/*void union(int x,int y)
{
    int rx=find(x);
    int ry=find(y);

    if()
}*/
int find(int x)
{
    while(x!=t[x])
        x=t[x];
    return x;
}
int main()
{
    citire();
    initializare();
    return 0;
}
