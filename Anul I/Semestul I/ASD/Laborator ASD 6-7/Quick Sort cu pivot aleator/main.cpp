#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;
ifstream fin("f.in");


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
int pivotrandom(int v[],int p,int q)
{
    srand(time(NULL)); //ca sa fie de fiecare data diferit
    int r=p+rand()%(q-p);//cu q-p+1 nu merge. de ce?
    swap(v[p],v[r]);
    return pivot(v,p,q);
}

void quickSort(int v[],int p,int q)
{
    if(p<q)
    {
        int x=pivotrandom(v,p,q);
        quickSort(v,p,x);
        quickSort(v,x+1,q);
    }
}


void citire(int v[],int &n)
{
    fin>>n;
    int i;
    for(i=1;i<=n;i++)
        fin>>v[i];
}


void afisare(int v[],int n)
{
    int i;
    for(i=1;i<=n;i++)
        cout<<v[i]<<' ';
}
int main()
{
    int v[100],n;
    citire(v,n);
    quickSort(v,1,n);
    afisare(v,n);
    return 0;
}
