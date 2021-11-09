#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
using namespace std;
ifstream fin("retea2.in");
ofstream fout("retea2.out");

double distanta(pair <int,int> x, pair <int,int> y)
{
    return sqrt((x.first-y.first)*(x.first-y.first) + (x.second-y.second)*(x.second-y.second));
}

void citire(vector <pair <double , pair < int , int > > > &E,int &n,int &m,int &e)
{

    fin>>n>>m>>e;

    vector <pair <int,int> > coord;
    coord.resize(n+m+1);

    for(int i=1;i<=n+m;i++)       //primele n sunt coordonatele centralelor, urmatoarele sunt coordonatele locuintelor
        fin>>coord[i].first>>coord[i].second;


    E.resize(e);

    for(int i=0;i<e;i++)
    {
        fin>>E[i].second.first>>E[i].second.second;

        E[i].first=distanta(coord[E[i].second.first],coord[E[i].second.second]);

    }

}

void initializare(vector <int> &t,vector <int> &h,int n,int m)
{

    for(int i=1;i<=n;i++)
    {
        t[i]=1;  //toate centralele se leaga in mod imaginar de 1
        h[i]=0;
    }

    h[1]=1;

    for(int i=n+1;i<=m+n;i++)
    {
        t[i]=i;
        h[i]=0;
    }
}




int Find(int x,vector <int> t)
{
    while(t[x]!=x)
        x=t[x];
    return x;
}

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


void Kruskal(vector <pair <double , pair < int , int > > > E,int n,int m ,int e, list <pair <int,int > > &K)
{

    sort(E.begin(),E.end());

    vector <int> t;  //vector de tati
    vector <int> h;  //vector cu inaltimi
    t.resize(n+m+1);
    h.resize(n+m+1);
    initializare(t,h,n,m);

    double S=0;
    for(int i=0;i<e;i++)
    {
        int x=E[i].second.first;
        int y=E[i].second.second;
        double c=E[i].first;

        if(Find(x,t)!=Find(y,t))
        {
            K.push_back({x,y});
            Union(x,y,t,h);
            S+=c;
        }

        if(K.size()==n+m-1)break;
    }
    cout<<S<<'\n';

}


int main()
{
    vector <pair <double , pair < int , int > > > E ;
    list < pair <int,int> > K;
    int n,m,e;
    citire(E,n,m,e);

    Kruskal(E,n,m,e,K);

    for(auto a: K)
        cout<<a.first<<' '<<a.second<<'\n';
    return 0;
}
