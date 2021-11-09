#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("darb.in");
ofstream fout("darb.out");

list <int> * L;
int n;

void citire()
{
    fin>>n;
    L=new list <int> [n+1];

    int x,y;
    for(int i=1;i<n;i++)
    {
        fin>>x>>y;
        L[x].push_back(y);
        L[y].push_back(x);
    }

}

int bf(int x,vector <long long> &viz)
{
    queue <int> Q;
    Q.push(x);

    viz[x]=1;
    while(!Q.empty())
    {
        x=Q.front();
        Q.pop();

        for(auto y : L[x])
            if(viz[y]==-1)
        {
            viz[y]=viz[x]+1;
            Q.push(y);
        }
    }

    return x;
}
int main()
{

    citire();

    vector <long long> viz1(n+1,-1);
    int x=bf(1,viz1);
    vector <long long> viz2(n+1,-1);
    x=bf(x,viz2);
    fout<<viz2[x];
    return 0;
}
