#include <iostream>

using namespace std;


void interclasare(int v[],int p,int q)
{
    int m=(p+q)/2;
    int i=p,j=m+1,z[1001],k=0;
    while(i<=m && j<=q)
    {
        if(v[i]<=v[j])z[++k]=v[i++];
        else z[++k]=v[j++];
    }
    while(i<=m)z[++k]=v[i++];
    while(j<=q)z[++k]=v[j++];
    k=1;
    for(i=p;i<=q;i++)
        v[i]=z[k++];
}


void mergeSort(int v[],int p,int q)
{
    if(p<q)
    {
        int m=(p+q)/2;
        mergeSort(v,p,m);
        mergeSort(v,m+1,q);
        interclasare(v,p,q);
    }
}


void citire(int v[],int &n)
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>v[i];
}

void afisare(int v[],int n)
{
    for(int i=1;i<=n;i++)
        cout<<v[i]<<' ';
}
int main()
{
    int v[501],n;
    citire(v,n);
    mergeSort(v,1,n);
    afisare(v,n);
    return 0;
}
