#include <iostream>

using namespace std;
int inserare(int &n,int x,int v[])
{
    int p;
    if(v[1]>x)p=1;
    else if(x>v[n])p=n+1;
    else {for(int i=1;i<=n;i++)
        if(x<v[i]){p=i;break;}}
    for(int i=n;i>=p;i--)
          v[i+1]=v[i];
    n++;
    v[p]=x;
}
int main()
{
    int n,v[100],x,k=0;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        if(k==0)v[++k]=x;
        else inserare(k,x,v);
    }
    for(int i=1;i<=n;i++)cout<<v[i]<<' ';
    return 0;
}
