#include <iostream>

using namespace std;
void sortare(int n,int v[])
{
    for(int i=n;i>1;i--)
    {
        int p=i;
        for(int j=1;j<i;j++)
            if(v[j]>v[p])p=j;
        v[0]=v[i];
        v[i]=v[p];
        v[p]=v[0];
    }
}
int main()
{
    int n,v[100];
    cin>>n;
    for(int i=1;i<=n;i++)cin>>v[i];
    sortare(n,v);
    for(int i=1;i<=n;i++)cout<<v[i]<<' ';
    return 0;
}
