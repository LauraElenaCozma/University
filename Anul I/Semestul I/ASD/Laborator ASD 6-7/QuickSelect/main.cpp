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


int pivot(int v[],int st,int dr)
{
    //asezam v[p] pe pozitia corespunzatoare daca vectorul ar fi sortat
    int p=st,q=dr;
    int x=v[p];
    while(p<q)
    {
        while(p<q && x<=v[q])q--;
        v[p]=v[q];
        while(p<q && x>=v[p])p++;
        v[q]=v[p];
    }
    v[p]=x;
    return p;
}

int QuickSelect(int v[],int n,int k)
{
    int st=1,dr=n;
    while(st<=dr)
    {
        int p=pivot(v,st,dr);
        if(p==k)return v[p];
        else if(p>k)dr=p-1;
             else st=p+1;
    }
}

int main()
{
    int v[100],n,k;
    cin>>k;
    citire(v,n);
    cout<<QuickSelect(v,n,k);
    return 0;
}
