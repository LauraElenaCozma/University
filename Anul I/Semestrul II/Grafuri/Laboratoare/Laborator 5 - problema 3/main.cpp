#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;
ifstream fin("graf.in");
int n,m,s,t;
const int inf=100000;
vector < pair <int,int> > *L;
vector <int> d,tata;
/*

Pentru fiecare arc al unei reţele de comunicaţie acestui graf se cunoaşte o pondere pozitivă
subunitară reprezentând probabilitatea ca legătura corespunzătoare să nu se defecteze (de
forma 1/2p = 2-p
). Aceste probabilităţi sunt independente, deci siguranţa unui drum este
egală cu produsul probabilităţilor asociate arcelor care îl compun. Arătaţi că problema
determinării unui drum de siguranţă maximă de la un vârf de start s la un vârf destinaţie t
(accesibil din s) se poate reduce la o problemă de determinare a unui drum minim între s şi t
(pentru un graf cu ponderile modificate). Pornind de la acest fapt, implementaţi un algoritm
bazat pe algoritmul lui Dijkstra pentru determinarea unui drum de siguranţă maximă între
două vârfuri s şi t citite de la tastatură pentru o reţea orientată dată în fişierul retea.in prin
următoarele informații:
- n, m – numărul de vârfuri, respectiv arce
- m linii conţinând triplete de numere naturale i j p cu semnificaţia: (i,j) este arc
în reţea cu probabilitatea să nu se defecteze egală cu 2-p
 O(m log(n)).



*/
void citire()
{
    fin>>n>>m;
    d.resize(n+1,inf);
    tata.resize(n+1,0);

    L=new vector < pair <int,int> > [n+1];
    int x,y,c;
    for(int i=1;i<=m;i++)
    {
        fin>>x>>y>>c;
        L[x].push_back({c,y});
    }
    fin>>s>>t;
}

void Dijkstra()
{
    d[s]=0;
    set <pair<int,int> > Q;
    Q.insert({0,s});
    vector <int> viz(n+1,0);

    int x,c;
    while(!Q.empty())
    {
        do
        {
            x=Q.begin()->second;
            c=Q.begin()->first;
            Q.erase(Q.begin());
        }
        while(viz[x]);
        viz[x]=1;

        if(x==t)break;

        for(auto y : L[x] )
            if(!viz[y.second] && y.first+d[x]<d[y.second] )
        {
            d[y.second]=y.first+d[x];
            tata[y.second]=x;
            Q.insert({d[y.second],y.second});
        }

    }
}


void afis_drum(int x)
{
    if(tata[x]!=0)
        afis_drum(tata[x]);
    cout<<x<<' ';
}
int main()
{
    citire();
    Dijkstra();
    cout<<d[t]<<'\n';
    afis_drum(t);
    return 0;
}
