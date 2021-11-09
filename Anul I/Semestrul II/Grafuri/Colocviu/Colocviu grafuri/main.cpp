#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <list>
using namespace std;
ifstream fin("graf.in");

vector <pair <int, pair <int,int> > > E1,E2;
list < int > *L;
int n,m,k,Pondere_totala;
vector <pair <int,int> > APCM;

int bf(int x)
{
    queue <int> Q;
    Q.push(x);
    vector <int> viz(n+1,0);

    while(!Q.empty())
    {
        x=Q.front();
        Q.pop();

        for(auto y : L[x])
            if(!viz[y])
            {
                viz[y]=1;
                Q.push(y);
            }

    }

    for(int i=1;i<=n;i++)
        if(!viz[i])return 0;  //graful nu e conex
    return 1;
}


int Find(int x,vector <int> &t)
{
    if(t[x]==x)return x;
    else t[x]=Find(t[x],t);
    return t[x];
}

void Union(int x,int y,vector <int> &t,vector <int> &h)
{
    int rx=Find(x,t);
    int ry=Find(y,t);

    if(h[rx]>h[ry])
        t[ry]=rx;
    else if(h[ry]>h[rx])
            t[rx]=ry;
         else
         {
             t[rx]=ry;
             h[ry]++;
         }
}


void kruskal()
{
    vector <int> t(n+1);
    vector <int> h(n+1,0);
    for(int i=1;i<=n;i++)
        t[i]=i;
    bool exista_arbore=1;
    bool verificare_arbore=1; //presupunem initial ca G e arbore
    int nr_selectate=0;

    for(int i=0;i<m-k && exista_arbore;i++)
    {
        int x=E1[i].second.first;
        int y=E1[i].second.second;
        int c=E1[i].first;

        if(Find(x,t)!=Find(y,t))
        {
            Union(x,y,t,h);
            APCM.push_back({x,y});
            nr_selectate++;
            Pondere_totala+=c;
        }
        else {exista_arbore=0; verificare_arbore=0;}  //muchiile care trebuie neaparat selectate formeaza un ciclu
    }

    sort(E2.begin(),E2.end());
    for(int i=0;i<k && exista_arbore;i++)
    {
        int x=E2[i].second.first;
        int y=E2[i].second.second;
        int c=E2[i].first;

        if(Find(x,t)!=Find(y,t))
        {
            Union(x,y,t,h);
            APCM.push_back({x,y});
            nr_selectate++;
            Pondere_totala+=c;
        }
        else verificare_arbore=0;

        if(nr_selectate==n-1)break;
    }

    if(nr_selectate!=n-1)exista_arbore=0;
    //daca am selectat mai putin de n-1 muchii atunci nu s a putut forma un arbore, deci exista arbore=0
    //conditia de G=arbore poate fi verificata in O(1) cu if(exista_arbore && m==n-1) - daca s-a putut forma un arbore cu toate muchiile existente atunci toate muchiile formau un arbore
    if(exista_arbore)
    {
        cout<<"Muchiile:\n";
        for(auto x : APCM)
            cout<<"("<<x.first<<','<<x.second<<") ; ";
        cout<<"\nCost total: "<<Pondere_totala;
    }
    else cout<<"Nu exista arbore";
}

void citire()
{
    fin>>n>>m>>k;

    if(m<n-1) cout<<"a)NU\nb)Nu exista arbore!"; //nu poate exista un arbore daca graful are mai putine muchii decat trebuie
    else
    {
        int s=0;
        //in acest caz m-n+1>=0
        int x,y,c;
        for(int i=1;i<=m-k;i++)
        {
            fin>>x>>y>>c;
            E1.push_back({c,{x,y}});
            s+=c;
            //in vectorul E1 avem retinute primele m-k muchii
        }

        for(int i=m-k+1;i<=m;i++)
        {
            fin>>x>>y>>c;
            E2.push_back({c,{x,y}});
            s+=c;
            //in vectorul E2 avem retinute restul muchiilor
        }

        L=new list <int> [n+1];
        for(auto x : E1)
        {
            L[x.second.first].push_back(x.second.second);
            L[x.second.second].push_back(x.second.first);
        }

        for(auto x : E2)
        {
            L[x.second.first].push_back(x.second.second);
            L[x.second.second].push_back(x.second.first);
        }

        if(!bf(1)) //daca nu e conex
        {
            cout<<"a)NU\nb)Nu exista arbore!";
        }
        else
        {
            //daca e conex
            if(m==n-1)
            {
                //daca e deja arbore nu mai trebuie sa aplicam kruskal
                cout<<"a)DA\n";
                for(auto x : E1)
                    cout<<"("<<x.second.first<<','<<x.second.second<<") ;";
                for(auto x : E2)
                    cout<<"("<<x.second.first<<','<<x.second.second<<") ;";
                cout<<"\nCost:"<<s;
            }
            else
            {
                 cout<<"a)NU\n";
                 if(m-k>n-1) //trebuie sa selectam mai multe muchii decat n-1. Acest caz are complexitatea O(m+n), deoarece trebuie neaparat sa verificam daca graful initial e arbore
                    cout<<"b)Nu exista arbore!\n";
                 else kruskal();
            }

        }
    }

}


int main()
{
    citire();
    return 0;
}


/*
8 11 8
1 3 5
1 5 4
2 4 10
2 7 4
3 7 5
3 5 2
3 8 4
4 7 3
5 6 2
5 8 1
6 8 3



8 10 8
1 3 5
1 5 4
2 4 10
2 7 4
3 5 2
3 8 4
4 7 3
5 6 2
5 8 1
6 8 3

*/
