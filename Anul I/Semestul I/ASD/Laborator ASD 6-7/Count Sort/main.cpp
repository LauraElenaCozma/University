#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("f.in");

void citire(int v[],int &n)
{
    fin>>n;
    int i;
    for(i=1;i<=n;i++)
        fin>>v[i];
}



void afisare(int f[])
{
    for(int i=0;i<=100;i++)
        for(int j=1;j<=f[i];j++)
            cout<<i<<' ';
}



void initializareZero(int v[])
{
    //initializam primele 100 de pozitii din evctor. presupunem ca toate numerele sunt cuprinse intre 0 si 100
    for(int i=0;i<=100;i++)
        v[i]=0;
}


void countSort(int v[],int n,int f[])
{
    initializareZero(f);
    for(int i=1;i<=n;i++)
        f[v[i]]++;
}


int main()
{
    int v[100],f[101],n;
    citire(v,n);
    countSort(v,n,f);
    afisare(f);
    return 0;
}
