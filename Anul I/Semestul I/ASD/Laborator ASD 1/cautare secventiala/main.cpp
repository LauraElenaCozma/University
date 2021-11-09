#include <iostream>

using namespace std;

int cautare(int v[],int n,int x)
{
    for(int i=1;i<=n;i++)
        if(v[i]==x)return 1;
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
