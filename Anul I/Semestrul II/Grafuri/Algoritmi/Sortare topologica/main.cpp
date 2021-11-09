#include <iostream>
#include <list>
#include <fstream>
#include <queue>
using namespace std;
ifstream fin("graf.in");
void citire(list < int > *& L, int &n , int &m,vector <int> &gr)
{
    int x,y;

    fin>>n;
    L=new list < int > [n+1];
    gr.resize(n+1);
    for(int i=1;i<=n;i++)
        gr[i]=0;
    fin>>m;
    for(int i=1;i<=m;i++)
    {
        fin>>x>>y;
        L[x].push_back(y);
        gr[y]++;
    }
}


void top_sort(list <int> * L,int n,vector <int> gr)
{
    queue <int> Q;
    vector <int> TS;

    for(int i=1;i<=n;i++)
        if(gr[i]==0)Q.push(i);

    while(!Q.empty())
    {
        int x=Q.front();
        TS.push_back(x);
        Q.pop();
        for(auto e : L[x])
        {
            gr[e]--;
            if(gr[e]==0)Q.push(e);
        }
    }


    if(TS.size()==n)
    {
        for(int i : TS)
            cout<<i<<' ';
    }
    else cout<<"Nu se poate face sortare topologica";

}
int main()
{
    list < int > *L;
    vector <int> gr;
    int n,m;

    citire(L,n,m,gr);
   /* for(int i=1;i<=n;i++)
    {
        cout<<i<<": ";
        for(auto e: L[i])
            cout<<e<<' ';
        cout<<'\n';
    }*/
    top_sort(L,n,gr);
    return 0;
}
