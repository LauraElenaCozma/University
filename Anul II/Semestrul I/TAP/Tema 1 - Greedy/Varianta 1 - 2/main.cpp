#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
ifstream fin("read.txt");

int cmp(pair < int, pair <int,int> > x, pair < int, pair <int,int> > y)
{
    return (x.second.second<y.second.second);
}
int main()
{
    vector < pair < int, pair <int,int> > > v; //primul element din al doilea pair e durata li si al doilea e timpul limita di

    int n;
    fin>>n;

    v.resize(n);
    for(int i=0;i<n;i++)
        {
            v[i].first=i+1;
            fin>>v[i].second.first>>v[i].second.second;
        }

    //sortam crescator dupa timpul limita di
    sort(v.begin(),v.end(),cmp);

    vector <int> p;   //tine intarzierea activitatii de pe pozitia i din vectorul v sortat
    p.resize(n);

    int hour=0 , maxlate=0;  //hour e ora la care am ajuns cu planificatul la pasul i

    cout<<"Propunere de planificare optima: \n";
    for(int i=0;i<n;i++)
    {
        cout<<v[i].first<<": "<<hour<<' '<<hour+v[i].second.first<<' ';
        hour+=v[i].second.first;
        if(hour <= v[i].second.second) p[i] = 0; //ora planificarii nu a depasit termenul limita
        else p[i] = hour - v[i].second.second;
        cout<<p[i]<<'\n';
        if(p[i] > maxlate) maxlate = p[i];
    }
    cout<<"Intarziere: ";
    cout<<maxlate;
    return 0;
}
