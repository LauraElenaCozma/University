#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
    ///20 pct!!!
ifstream fin("zapada.in");
ofstream fout("zapada.out");

vector <pair <int,pair <int,int> > > L,L_neselectat;


int nr_str,n,m;
vector <int> t,h,selectat;

void citire()
{
    fin>>n>>m;

    int x,y,cost;

    for(int i=1;i<=m;i++)
    {
        fin>>x>>y>>cost;
        L.push_back({cost,{x,y}});  //ultima componenta e vizitat= daca muchia a fost selectata deja in apcm e 1

    }
    t.resize(n+1);

    for(int i=1;i<=n;i++)
        t[i]=i;
    h.resize(n+1,0);
    selectat.resize(m+1);


}

int find(int x)
{
    while(x!=t[x])
        x=t[x];
    return x;
}

void Union(int x,int y)
{
    int rx=find(x);
    int ry=find(y);

    if(h[rx]>h[ry])
        t[ry]=rx;

    else if(h[rx]<h[ry])
        t[rx]=ry;
        else
        {
            t[rx]=ry;
            h[ry]++;
        }
}

void kruskal()
{
    double cost_apcm=0;
    int x,nr_sel=0;
    fin>>nr_str;
    for(int i=1;i<=nr_str;i++)
    {
        fin>>x;
        x--;//eu am pus in vector de la 0 la m-1
        selectat[x]=1;

        if(find(L[x].second.first)!=find(L[x].second.second))
            {
                cout<<L[x].second.first<<' '<<L[x].second.second<<' '<<L[x].first<<'\n';
                Union(L[x].second.first,L[x].second.second);
                nr_sel++;
            }

        cost_apcm+=L[x].first;
    }
    for(int i=0;i<m;i++)
        if(!selectat[i]) L_neselectat.push_back(L[i]);
    sort(L_neselectat.begin(),L_neselectat.end());
    cout<<'\n';
    for(int i=0;i<L_neselectat.size();i++)
    {
        if(nr_sel==n-1)break;
        if(find(L_neselectat[i].second.first)!=find(L_neselectat[i].second.second))
            {
                cout<<L_neselectat[i].second.first<<' '<<L_neselectat[i].second.second<<' '<<L_neselectat[i].first<<'\n';
                Union(L_neselectat[i].second.first,L_neselectat[i].second.second);
                nr_sel++;
                cost_apcm+=L_neselectat[i].first;
            }




    }


    cout<<cost_apcm;
}

int main()
{

    citire();
    kruskal();
    return 0;
}

/*
25 75
1 8 14
1 23 2
1 24 13
2 6 3
2 7 2
2 10 9
2 13 9
2 15 5
3 5 6
3 6 3
3 10 11
3 16 11
3 17 5
4 6 12
4 14 13
4 15 2
4 16 11
4 19 10
4 21 10
4 24 8
5 6 3
5 15 1
5 19 8
5 22 2
5 25 14
6 8 11
6 14 11
6 20 12
6 21 9
6 24 1
7 8 8
7 16 3
7 17 12
7 19 9
7 22 8
7 23 7
8 11 12
8 16 15
8 19 15
9 17 3
9 19 11
9 24 9
10 15 11
10 23 13
11 12 7
11 15 13
11 17 8
11 18 1
11 19 7
11 24 14
12 13 10
12 15 1
12 18 14
13 16 9
13 21 5
14 16 10
14 21 14
14 24 4
15 18 5
15 20 3
15 23 8
16 18 6
16 21 6
16 22 7
16 25 12
17 18 8
17 19 5
17 21 13
18 21 14
18 23 9
19 22 8
19 25 7
20 21 14
20 24 6
21 22 8
10
56 1 10 11 14 73 65 46 43 44

*/
