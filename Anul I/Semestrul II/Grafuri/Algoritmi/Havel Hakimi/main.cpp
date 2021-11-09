#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream fin("graf.in");

void interclasare(vector <int>& v,int m,int poz)
{
    vector <int> aux;
    int i1=poz,i2=m;
    while(i1<m && i2<v.size())
    {
        if(v[i1]>=v[i2]){aux.push_back(v[i1]); i1++;}
        else {aux.push_back(v[i2]); i2++;}
    }

    while(i1<m)
    {
        aux.push_back(v[i1]);
        i1++;
    }

    while(i2<v.size())
    {
        aux.push_back(v[i2]);
        i2++;
    }

    int k=0;
    for(int i=poz;i<v.size();i++,k++)
          v[i]=aux[k];

}
bool grafica(vector <int> s , int n)
{
    int sum=0;
    int nr_zero=0;
    for(auto i : s)
    {
        sum+=i;
        if(i<0 || i>n-1)return false;
        if(i==0)nr_zero++;
    }
    if(sum%2)return false;

    sort(s.begin(),s.end(),greater<int>());

    int poz=0;   //lasam zerourile facute pe parcuns in fata

    while(nr_zero!=s.size())
    {
        for( auto i: s)
            cout<<i<<' ';
        cout<<'\n';
        int maxi=s[poz];
        s[poz]=0;
        nr_zero++;
        if(maxi>s.size()-nr_zero)return false;

        for(int i=poz+1;i<=poz+maxi;i++)
        {
            s[i]--;
            if(s[i]<0)return false;
            if(s[i]==0)nr_zero++;
        }

        interclasare(s,poz+maxi+1,poz+1);

        poz++;

    }

    return true;

}

int main()
{
    vector <int> s;
    int n;
    fin>>n;
    s.resize(n);
    for(int i=0;i<n;i++)
        fin>>s[i];

    if(grafica(s,n))cout<<"E grafica";
    else cout<<"Nu e grafica";
    return 0;
}
