#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
ifstream fin("graf.in");
int time=0;

void citire( int&n , int &m , vector <vector <int> > &E)
{
    fin>>n>>m;
    E.resize(n+1);

    int x,y;
    for(int i=1;i<=m;i++)
    {
        fin>>x>>y;
        E[x].push_back(y);
        E[y].push_back(x);
    }

}

vector <bool> c(10000,false);
vector<pair <int,int> > much;

int critic(int x,vector <int>& low, vector <int>& d ,vector <int>& tata,vector <vector <int> > E)
{
    time++;
    low[x]=d[x]=time;

    int nr_copii=0;
    for(auto y : E[x])
    {

        if(!d[y])
        {
            tata[y]=x;

            critic(y,low,d,tata,E);

            if(low[x]>low[y])
                low[x]=low[y]; //cobor pe muchia xy ca sa ajung la nivelul in care pot sa ajung din y

            if(low[y]>=d[x])   //din y pot sa ajung maxim pana la nivelul lui x
                c[x]=true;

            if(low[y] >d[x])    //comp conexa data de y e mai jos decat cea data de x
            much.push_back({x,y});

            nr_copii++;

        }

        else if(tata[x]!=y)
            {
                if(low[x]>d[y])   //ne intoarcem de la x la y prin muchia de intoarcere xy la nivelul d[y]
                    low[x]=d[y];
            }

    }

    return nr_copii;

}

int main()
{
    int n,m;
    vector <vector<int> > E;
    citire(n,m,E);
    vector <int> low(n+1,0);
    vector <int> d(n+1,0);
    vector <int> tata(n+1,0);

    int s;
    cin>>s;
    if(critic(s,low,d,tata,E) > 1)   //are mai mult de un fiu
        c[s]=true;
    else c[s]=false;   ///de ce trebuie pe else???


    for(int i=1;i<=n;i++)
        cout<<c[i]<<' ';
    cout<<'\n';

    for(auto e: much)
        cout<<e.first<<' '<<e.second<<'\n';

    return 0;
}
