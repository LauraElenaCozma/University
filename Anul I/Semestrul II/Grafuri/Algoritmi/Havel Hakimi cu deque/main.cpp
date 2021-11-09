#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <list>
using namespace std;
ifstream fin("graf.in");

list < int > *sol;

void citire(int &n,deque <pair<int,int> > &s)
{
    fin>>n;
    s.resize(n+1,{0,0});
    sol=new list <int> [n+1];
    for(int i=1;i<=n;i++)
    {
        fin>>s[i].first;
        s[i].second=i;
    }
}

void interclasare(int p,int n,deque <pair<int,int> > &s)//interclasam de la 1 la p si de la p+1 la n
{
    int i=1,j=p+1;
    deque <pair<int,int> > aux;
    while(i<=p && j<=n)
    {
        if(s[i].first>=s[j].first){aux.push_back(s[i]); i++;}
        else {aux.push_back(s[j]); j++;}

    }

    while(i<=p)
        {aux.push_back(s[i]); i++;}
    while(j<=n)
        {aux.push_back(s[j]); j++;}

    for(int i=1;i<=n;i++)
        s[i]=aux[i-1];
}

bool havel_hakimi(int n,deque <pair<int,int> > s)
{
    sort(s.begin()+1,s.end(), greater<pair<int,int> >());

    int suma=0;

    for(int i=1;i<=n;i++)
    {
        if(s[i].first<0 || s[i].first>n)return false;
        suma+=s[i].first;

    }

    if(suma%2)return false;

    while(s[1].first!=0)
    {

        for(int i=2;i<=s[1].first+1;i++)
        {
            s[i].first--;
            sol[s[1].second].push_back(s[i].second);
            sol[s[i].second].push_back(s[1].second);
            if(s[i].first==-1) return false;
        }

        int p=s[1].first;
        s.pop_front();

        interclasare(p,s.size()-1,s);  //-1 adica fara elementul de pe pozitia 0

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
    if(havel_hakimi(n,s))
    {
        cout<<"E secventa de grade\n";
        for(int i=1;i<=n;i++)
        {
            cout<<i<<" : ";
            for(int x : sol[i])
                cout<<x<<' ';
            cout<<'\n';
        }
    }
    else cout<<"Nu e secventa de grade";
    return 0;
}
