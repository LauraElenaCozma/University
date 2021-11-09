#include <iostream>

using namespace std;
//presupunem ca vectorul este deja ordonat

int cautare(int v[],int n,int x)
{
    int st=1,dr=n;
    while(st<=dr)
    {
        int m=(st+dr)/2;
        if(v[m]==x)return 1;
        else if(x<v[m])dr=m-1;
             else st=m+1;
    }
    return 0;
}
int main()
{
    int v[101],n,x;
    cin>>n>>x;
    for(int i=1;i<=n;i++)
        cin>>v[i];
    if(cautare(v,n,x))cout<<"DA";
    else cout<<"NU";
    return 0;
}
