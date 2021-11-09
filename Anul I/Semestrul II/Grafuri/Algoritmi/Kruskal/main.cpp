#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
ifstream fin("graf.in");

void citire(vector <pair <int , pair < int , int > >> &E,int &n,int &m)
{

    fin>>n>>m;

    E.resize(m);

    for(int i=0;i<m;i++)
        fin>>E[i].first>>E[i].second.first>>E[i].second.second;

}

void initializare(vector <int> &t,vector <int> &h,int n)
{

    for(int i=1;i<=n;i++)
    {
        t[i]=i;
        h[i]=0;
    }
}



int Find(int x,vector <int> t) //path compression
{
    if(t[x]==x)return x;
    else t[x]=Find(t[x],t);  //gasim reprezentantul lui x
    return t[x];
}


/*int Find(int x,vector <int> t)
{
    while(t[x]!=x)
        x=t[x];
    return x;
}*/

void Union(int x,int y,vector <int> &t, vector <int> &h)
{
    int a=Find(x,t);
    int b=Find(y,t);


    if(h[a]>h[b])
        t[b]=a;
    else if(h[a]<h[b])
        t[a]=b;
    else
    {
        t[a]=b;
        h[b]++;
    }

}


void Kruskal(vector <pair <int , pair < int , int > >> E,int n,int m , list <pair <int,int >> &K)
{

    sort(E.begin(),E.end());

    vector <int> t;  //vector de tati
    vector <int> h;  //vector cu inaltimi
    t.resize(n+1);
    h.resize(n+1);
    initializare(t,h,n);

    int S=0;
    for(int i=0;i<m;i++)
    {
        int x=E[i].second.first;
        int y=E[i].second.second;
        int c=E[i].first;

        if(Find(x,t)!=Find(y,t))
        {
            K.push_back({x,y});
            Union(x,y,t,h);
            S+=c;
        }

        if(K.size()==n-1)break;
    }
    cout<<S<<'\n';

}


int main()
{
    vector <pair <int , pair < int , int > >> E ;
    list < pair <int,int> > K;
    int n,m;
    citire(E,n,m);

    Kruskal(E,n,m,K);

    for(auto a: K)
        cout<<a.first<<' '<<a.second<<'\n';
    return 0;
}
