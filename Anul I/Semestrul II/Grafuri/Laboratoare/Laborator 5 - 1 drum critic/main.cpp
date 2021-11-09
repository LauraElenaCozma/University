#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <climits>
using namespace std;
ifstream fin("activitati.in");
#define inf INT_MAX/2

void citire(int &n , int &m , list <pair <int,int> > *&L,vector <int> &gr_int,vector <int> &durata)
{
    fin>>n;
    durata.resize(n+1);
    durata[0]=0;

    gr_int.resize(n+2);

    vector <int> gr_ext(n+1,0);

    for(int i=1;i<=n;i++)
    {
        fin>>durata[i];
        gr_int[i]=0;
    }


    gr_int[n+1]=0;

    fin>>m;

    L=new list <pair <int ,int > > [n+3];

    int x,y;
    for(int i=1;i<=m;i++)
    {
        fin>>x>>y;
        L[x].push_back({-durata[x],y});  //punem durata cu - pentru a calcula drumul minim in loc de cel maxim

        gr_int[y]++;
        gr_ext[x]++;
    }
    for(int i=1;i<=n;i++)
        if(!gr_ext[i])
        {
            L[i].push_back({-durata[i],n+1});
            gr_int[n+1]++;
        }



}


void top_sort(int n , int m  , list <pair <int,int> >*L , vector <int> &result,vector <int> gr)
{
    for(int i=1;i<=n;i++)
        if(gr[i]==0)result.push_back(i);

    int p=0;
    while(result.size()!=n+1)
    {
        int ult=result.size();
        while(p!=ult)
        {
            int x=result[p];
            for( auto y : L[x])
            {
                gr[y.second]--;
                if(gr[y.second]==0)result.push_back(y.second);
            }
            p++;
        }
    }

}


void initializare(int n,int m,vector <int> &d,vector <int> &t,vector <int> gr)
{
    d.resize(n+2);
    t.resize(n+2);

    for(int i=1;i<=n+1;i++)
    {
        if(!gr[i])d[i]=0;
        else d[i]=inf;
        t[i]=0;
    }
}


void afis_drum(vector <int> t,int poz)
{
    if(t[poz]!=0)
        afis_drum(t,t[poz]);
    cout<<poz<<' ';
}

void DAG(int n , int m , list <pair <int,int> >*L, vector <int> gr , vector <int> durata)
{
    vector <int> d,t,result;

    initializare(n,m,d,t,gr);

    top_sort(n,m,L,result,gr);

    for(int i=0;i<result.size();i++)
    {
        int x=result[i];

        for(pair <int,int> y : L[x])

            if(d[y.second]>d[x]+y.first)
        {
            d[y.second]=d[x]+y.first;
            t[y.second]=x;
        }
    }

    //TIMP MAXIM DE ASTEPTARE : distanta din nodul final cu semn schimbat
    cout<<"Timp de asteptare: "<<-d[n+1]<<"\nDrum critic: ";
    afis_drum(t,t[n+1]);

    //subpunct b
    cout<<'\n';
    for(int i=1;i<=n;i++)
        cout<<i<<" : "<<-d[i]<<' '<<durata[i]-d[i]<<'\n';//minus deoarece distantele mele sunt negative. d[i]=durata pana incepe evenimentul i. durata[i]=cat dureaza evenimentul i


}
int main()
{
    list < pair <int,int> > *L;
    vector <int> result,gr,durata;
    int n,m;

    citire(n,m,L,gr,durata);

    DAG(n,m,L,gr,durata);
    fin.close();
    return 0;
}
