#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <list>
using namespace std;
ifstream fin("graf.in");

list < pair <int,int> > sol;

void citire(int &n,deque <pair<int,int> > &s)
{
    fin>>n;

    int x;
    for(int i=1;i<=n;i++)
    {
        fin>>x;
        if(x==1)s.push_back({x,i});
        else s.push_front({x,i});

    }
}



bool construire_arbore(int n,deque <pair<int,int> > s)
{


    int suma=0;

    for(int i=0;i<n;i++)
        suma+=s[i].first;

    if(suma!=2*(n-1))return false;

    while(s.size() && s[0].first!=0)
    {
        sol.push_back({s[s.size()-1].second,s[0].second});

        s[0].first--;
        s.pop_back();
        if(s[0].first)
        {
            if(s[0].first==1){s.push_back(s[0]) ; s.pop_front();}
        }
        else s.pop_front();
    }

    return true;

    /*for(int i=1;i<=n;i++)
        cout<<s[i].first<<' '<<s[i].second<<'\n';*/
}
int main()
{
    deque <pair<int,int> > s;
    int n;
    citire(n,s);
    if(construire_arbore(n,s))
    {
        cout<<"E secventa de grade\n";
        for(auto x :sol)
            cout<<x.first<<' '<<x.second<<'\n';

    }
    else cout<<"Nu e secventa de grade";
    return 0;
}
