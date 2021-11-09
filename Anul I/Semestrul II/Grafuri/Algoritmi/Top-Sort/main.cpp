#include <iostream>
#include <fstream>
#include <list>
#include <vector>
using namespace std;
ifstream fin("graf.in");
ifstream in("sortaret.in");
ofstream out("sortaret.out");


void citire(list < int > *&L,int &n,int &m,vector <int> &gr)
{
    in>>n>>m;
    L=new list <int> [n+1];
    gr.resize(n+1);

    for(int i=1;i<=n;i++)
        gr[i]=0;

    int x,y;
    for(int i=1;i<=m;i++)
        {
            in>>x>>y;
            L[x].push_back(y);
            gr[y]++;
        }


}


void Top_Sort(list <int > *L,int n,vector <int> &gr,vector <int> &ts)
{
    for(int i=1;i<=n;i++)
        if(!gr[i])ts.push_back(i);

    int p=0;
    while(ts.size()!=n)
    {
        int ult=ts.size();
        while(p!=ult)
        {
            for(int x : L[ts[p]])
            {
                gr[x]--;
                if(!gr[x])ts.push_back(x);
            }
            p++;
        }
    }

}


int main()
{
    list < int > *L;
    vector <int> gr,ts;
    int n,m;

    citire(L,n,m,gr);

    /*for(int i=1;i<=n;i++)
    {
        cout<<"\n"<<i<<": ";
        for(int x : L[i])
            cout<<x<<' ';
    }*/

    Top_Sort(L,n,gr,ts);
    for(int i=0;i<n;i++)
        out<<ts[i]<<' ';

    fin.close();
    in.close();
    out.close();
    return 0;
}
