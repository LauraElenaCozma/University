#include <iostream>
#include <fstream>
#include <list>
#include <vector>
using namespace std;
ifstream fin("graf.in");

list <int> *L;

void citire(int &n,int &m)
{
    fin>>n>>m;

    L=new list <int> [n+1];
    int x,y;
    for(int i=1;i<=m;i++)
    {
        fin>>x>>y;
        L[x].push_back(y);
        L[y].push_back(x);
    }
}

vector <int> viz(1000,0);
vector <pair <int,int> > drum;
int ok;
void ciclu_eulerian(int st,int m)
{
   // cout<<st<<'\n';
    if(!ok && drum.size()!=m)
    {
        for(list<int>::iterator i=L[st].begin();i!=L[st].end();i++)
            if(!ok && (*i)>=0)
            {
                drum.push_back({st,(*i)});
                (*i)=-(*i);

                for(list<int>::iterator j=L[-(*i)].begin();j!=L[-(*i)].end();j++)
                    if((*j)==st){(*j)=-(*j); break;}

                ciclu_eulerian(-(*i),m);
                (*i)=-(*i);
                for(list<int>::iterator j=L[(*i)].begin();j!=L[(*i)].end();j++)
                    if(-(*j)==st){(*j)=-(*j); break;}
                drum.pop_back();
            }
    }
    else
    {   drum.push_back(drum[0]);
        for(auto e: drum)
            cout<<e.first<<' ';
            cout<<'\n';
        ok=1;
    }
}
int main()
{
    int n,m;
    citire(n,m);
    ciclu_eulerian(1,m);
    return 0;
}
