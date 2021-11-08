#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream fin("f.in");

int main()
{
    vector <int> v;
    vector <pair <int,int> > p;
    int n,c;//c=suma pe care trebuie sa o platim

    fin>>n>>c;
    v.resize(n);
    for(int i=0;i<n;i++)
        fin>>v[i];

    sort(v.begin(),v.end());

    int i=n-1;
    while(c!=0)
    {
        if(c/v[i]!=0)
        {
            p.push_back(make_pair(v[i],c/v[i]));
            c=c%v[i];
        }

        i--;
    }
    int nr_ban=0;
    for(int i=0;i<p.size();i++)
        {
            cout<<"("<<p[i].first<<','<<p[i].second<<") ";
            nr_ban+=p[i].second;
        }

    cout<<"\nNumarul bancnotelor este "<<nr_ban<<'.';
    return 0;
}
