#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("arbore.in");


vector <int> t;
int n;
void citire()
{
    fin>>n;

    t.resize(n+1);
    for(int i=1;i<=n;i++)
        fin>>t[i];
}

void rad_nod(int x)
{
    if(t[x]!=0)
        rad_nod(t[x]);
    cout<<x<<' ';
}

void nod_rad(int x)
{
    cout<<x<<' ';
    if(t[x]!=0)
        nod_rad(t[x]);

}


int main()
{
    citire();
    rad_nod(4);
    cout<<'\n';
    nod_rad(4);

    return 0;
}
