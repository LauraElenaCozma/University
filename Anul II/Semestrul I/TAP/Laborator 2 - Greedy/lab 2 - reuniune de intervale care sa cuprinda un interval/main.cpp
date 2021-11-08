#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream fin("f.in");

bool cmp(pair <int,int> x,pair <int,int> y)
{
    return (x.first<y.first);
}

int main()
{
    vector <pair <int,int> > v,sol;
    int n;
    pair <int,int> p,maxim;
    fin>>p.first>>p.second>>n;
    v.resize(n);
    for(int i=0;i<n;i++)
        fin>>v[i].first>>v[i].second;
    sort(v.begin(),v.end(),cmp);

    maxim.first=v[0].first;
    maxim.second=v[0].second;
    while(p.first<p.second)
    {

        for(int i=0;i<n;i++)
           if(v[i].first<=p.first && v[i].second>maxim.second)
               maxim=v[i];
        p.first=maxim.second;
        sol.push_back(maxim);
    }

    for(int i=0;i<sol.size();i++)
    cout<<"("<<sol[i].first<<','<<sol[i].second<<") ";
    return 0;
}
