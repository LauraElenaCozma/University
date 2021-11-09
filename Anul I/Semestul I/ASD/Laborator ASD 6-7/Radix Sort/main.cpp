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

int cifra(int n,int k)
{
    //extrage cifra de rang k
    int c;
    while(n!=0 && k!=0)
    {
        c=n%10;
        n/=10;
        k--;
    }
    if(k!=0)c=0;
    return c;
}

void adaugInMatrice(int a[][101],int x,int c)
{
    a[c][0]++;
    a[c][a[c][0]]=x;
}

void initializareZero(int a[][101])
{
    for(int i=0;i<=9;i++)
        a[i][0]=0;
}

void copiereInVector(int x[],int a[][101])
{
    int k=0;
    for(int i=0;i<=9;i++)
        for(int j=1;j<=a[i][0];j++)
            x[++k]=a[i][j];
}

void afisMat(int a[][101])
{
    for(int i=0;i<=9;i++)
    {for(int j=1;j<=a[i][0];j++)
         cout<<a[i][j]<<' ';
    cout<<'\n';
    }
}


void afisare(int v[],int n)
{
    int i;
    for(i=1;i<=n;i++)
        cout<<v[i]<<' ';
    cout<<'\n';
}

void RadixSort(int v[],int n,int a[][101])
{
    initializareZero(a);
    int k=1;
    while(a[0][0]!=n)
    {
        initializareZero(a);
        for(int i=1;i<=n;i++)
        {
            int c=cifra(v[i],k);
            adaugInMatrice(a,v[i],c);
        }
        k++;
        copiereInVector(v,a);

    }
}



int main()
{
    int v[101],n,a[11][101];
    citire(v,n);
    RadixSort(v,n,a);
    afisare(v,n);
    fin.close();
    return 0;
}
