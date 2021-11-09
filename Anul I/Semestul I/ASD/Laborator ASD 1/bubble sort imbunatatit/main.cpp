#include <iostream>

using namespace std;
void sort(int n,int v[])
{
    int ok;
    do
    {
        ok=0;
        for(int i=1;i<n;i++)
            if(v[i]>v[i+1])
        {
            swap(v[i],v[i+1]);
            ok=1;
        }
        n--;
    }
    while(ok==1);
}
int main()
{
    int n,v[100];
    cin>>n;
    for(int i=1;i<=n;i++)cin>>v[i];
    sort(n,v);
    for(int i=1;i<=n;i++)cout<<v[i]<<' ';
    return 0;
}
