#include <iostream>
#include <fstream>
#include <queue>
#include <list>
#include <vector>
using namespace std;
ifstream fin("graf.in");

priority_queue < pair <int,int> > Q;
list <pair <int ,int > > L[1000];
vector <pair <int , pair <int,int> > > A;


void citire(int &n,int &m)
{
    fin>>n>>m;

    int x,y,c;
    for(int i=0;i<m;i++)
    {
        fin>>x>>y>>c;
        L[x].push_back({-c,y});
        L[y].push_back({-c,x});  //priority queue le sorteaza descrescator si eu vreau sa le tin minte crescator
    }

}




void Prim(int start,int n,int m)
{
    const int inf=10000;
    vector <int> viz(n+1,0);
    vector <int> d(n+1,inf);
    vector <int> t(n+1,0);
    Q.push({0,start});
    int nrs=0;
    int x,y;

    while(!Q.empty())
    {
        do
        {
        x=Q.top().second;
        y=Q.top().first;
        Q.pop();
        }
        while(viz[x]);

        nrs++;
        viz[x]=1;

        A.push_back(make_pair(-y,make_pair(x,t[x])));
        for(auto vec : L[x])
        {
            if(!viz[vec.second] && -vec.first<d[vec.second])
            {
                d[vec.second]=-vec.first;
                t[vec.second]=x;

                Q.push(vec);
            }
        }

        if(nrs==n)break;
    }
    A.erase(A.begin());
    for(auto e: A)
        cout<<e.second.first<<' '<<e.second.second<<' '<<e.first<<'\n';

}

int main()
{
    int n,m;
    citire(n,m);
    Prim(1,n,m);
    return 0;
}
