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
vector <int> comp(1000,0);
vector <int> drum;
int ok=0;
void det_ciclu(int st,int n,int nr)
{

    comp[st]=1;
    if(!ok)
    {

        drum.push_back(st);
        viz[st]=nr;
        for(auto y : L[st])
            if(!viz[y] && !ok)

                    det_ciclu(y,n,nr+1);

            else if(viz[st]-viz[y]>=2 && !ok)
            {
                cout<<y<<' ';
                while(drum.back()!=y)
                {
                    cout<<drum.back()<<' ';
                    drum.pop_back();
                }
                cout<<y<<'\n';
                ok=1;
            }
        drum.pop_back();
        viz[st]=0;


    }

}
int main()
{
    int n,m;
    citire(n,m);
    for(int i=1;i<=n;i++)
        if(!comp[i])
           det_ciclu(i,n,1);
    return 0;
}
