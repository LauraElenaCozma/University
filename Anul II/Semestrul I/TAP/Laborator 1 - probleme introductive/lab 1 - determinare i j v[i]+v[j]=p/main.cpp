#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream fin("citire.in");
//verificam daca exista i si j ai v[i]+v[j]=p, p dat

/*
int main()
{
    vector <int> v;
    int n,p;
    fin>>n>>p;

    v.resize(n);
    for(int i=0;i<n;i++)
        fin>>v[i];

    sort(v.begin(),v.end());

    int i=0,j=n-1;
    while(i<j)
    {
        if(v[i]+v[j]==p){cout<<v[i]<<' '<<v[j]<<'\n'; i++;j--;}
        else if(v[i]+v[j]>p) j--;
        else i++;
    }
    return 0;
}
*/

///varianta cu v[i]+v[j]+v[k]=0

int main()
{
    vector <int> v;
    int n;
    fin>>n;

    v.resize(n);
    for(int i=0;i<n;i++)
        fin>>v[i];

    sort(v.begin(),v.end());

    int j,k;
    for(int i=0;i<n-2;i++)
    {
        j=i+1;
        k=n-1;

        while(j<k)
        {
            if(v[j]+v[k]==-v[i]){cout<<v[i]<<' '<<v[j]<<' '<<v[k]<<'\n'; j++;k--;}
            else if(v[j]+v[k]>-v[i]) k--;
            else j++;
        }
    }

    return 0;
}
