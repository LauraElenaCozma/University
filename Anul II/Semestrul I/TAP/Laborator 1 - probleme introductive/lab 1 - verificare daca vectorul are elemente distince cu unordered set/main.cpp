#include <iostream>
#include <fstream>
#include <unordered_set>
#include <algorithm>
using namespace std;
ifstream fin("f.in");

int distincte_n()
{
    int n;
    vector <int> v;
    fin>>n;
    v.resize(n);
    for(int i=0;i<n;i++)
        fin>>v[i];

    unordered_set <int> S;
    for(int i=0;i<n;i++)
        S.insert(v[i]);
    if(S.size()!=n)cout<<"Nu\n";
    else cout<<"Da\n";
    return 0;
}

int distincte_nlogn()
{
    int n;
    vector <int> v;
    fin>>n;
    v.resize(n);
    for(int i=0;i<n;i++)
        fin>>v[i];

    sort(v.begin(),v.end());
    for(int i=0;i<n;i++)
    if(v[i]==v[i+1]) {cout<<"Nu"; return 0;}
    cout<<"Da";
    return 0;
}
int main()
{
    distincte_n();
    distincte_nlogn();
}
