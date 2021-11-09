#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("graf.in");

int n,m,s,t;
int F[100][100],I[100][100],C[100][100],marginire=1;
vector <int > *Lin,*Lout;


void citire()
{
    fin>>n>>s>>t>>m;
    Lin=new vector<int> [n+1];
    Lout=new vector<int> [n+1];
    int x,y,c,f;
    for(int i=1;i<=m;i++)
    {
        fin>>x>>y>>c>>f;
        C[x][y]=c;
        F[x][y]=f;

        I[x][y]=c-f;
        I[y][x]=f;

        if(F[x][y]<0 || F[x][y]>C[x][y])marginire=0;

        Lin[y].push_back(x);
        Lout[x].push_back(y);

    }
}


bool conservare()
{
    for(int i=1;i<=n;i++)
        if(i!=s && i!=t)
    {
        int s_intrare=0,s_iesire=0;
        for(int x : Lin[i]) s_intrare+=F[x][i];
        for(int x : Lout[i]) s_iesire+=F[i][x];
        if(s_intrare!=s_iesire)return false;
    }
    return true;
}

int main()
{
    citire();
    if(marginire && conservare()) cout<<"Este flux";
    else cout<<"Nu este flux";
    return 0;
}
