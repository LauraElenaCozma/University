#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("date.in");
class Graf
{
    private:
        int **G;
        int nr_noduri;
        int *viz;
        void InitializareZero();
    public:
        Graf()
        {
            G=NULL;
            viz=NULL;
            nr_noduri=0;
        }

        ~Graf()
        {
            if(viz!=NULL)
                delete[] viz;

            if(G!=NULL)
            {
               for(int i=0;i<nr_noduri;i++)
                   delete[] G[i];
               delete[] G;
            }

        }

        friend istream& operator>>(istream& f,Graf &A);
        friend ostream& operator<<(ostream& f,const Graf A);

         Graf operator+(Graf A);

        void DFS(int x);
        void BFS(int x);
        int ComponenteConexeAdancime();
        void ComponenteConexeLatime();
        void VerificareConex();

        void MatriceaExistenteiDrumurilor();


};


istream& operator>>(istream& f,Graf &A)
{
    f>>A.nr_noduri;

    A.G=new int *[A.nr_noduri];

    int i,j;
    for(i=0;i<A.nr_noduri;i++)
    {
        A.G[i]=new int[A.nr_noduri];
        for(j=0;j<A.nr_noduri;j++)
           f>>A.G[i][j];
    }

    return f;
}

ostream& operator<<(ostream& f,const Graf A)
{
    f<<'\n';
    int i,j;
    for(i=0;i<A.nr_noduri;i++)
    {
        for(j=0;j<A.nr_noduri;j++)
           f<<A.G[i][j]<<' ';
        f<<'\n';
    }
    return f;

}


void Graf::InitializareZero()
{
    viz=new int[nr_noduri];
    for(int i=0;i<nr_noduri;i++)
        viz[i]=0;
}



void Graf::DFS(int x)
{

   //initializare cu 0
    viz[x]=1;
    cout<<x<<' ';
    for(int i=0;i<nr_noduri;i++)
        if(G[x][i] && !viz[i])
            DFS(i);
}


void Graf::BFS(int x)
{
    int c[10000];
    int p=0,u=0;
    viz[x]=1;
    c[p]=x;
    while(p<=u)
    {
        x=c[p++];
        cout<<x<<' ';
        for(int i=0;i<nr_noduri;i++)
            if(!viz[i] && G[x][i])
        {
            c[++u]=i;
            viz[i]=1;
        }
    }
}

int Graf::ComponenteConexeAdancime()
{
    int nr=0;
    cout<<"Parcurgere in Adancime:\n";
    InitializareZero();
    for(int i=0;i<nr_noduri;i++)
        if(!viz[i])
    {
        nr++;
        DFS(i);
        cout<<'\n';
    }
    return nr;
}


void Graf::ComponenteConexeLatime()
{
    {
    cout<<"Parcurgere in Latime:\n";
    InitializareZero();
    for(int i=0;i<nr_noduri;i++)
        if(!viz[i])
    {
        BFS(i);
        cout<<'\n';
    }
    }
}


void Graf::VerificareConex()
{
    int nr=ComponenteConexeAdancime();
    if(nr!=1)
        cout<<"Graful nu e conex\n";
    else cout<<"Graful e conex\n";
}


Graf Graf::operator+(Graf A)
{
    Graf S;

    //am alocat spatiu pentru matrice
    S.G=new int*[nr_noduri];
    for(int i=0;i<nr_noduri;i++)
        S.G[i]=new int[nr_noduri];

    for(int i=0;i<nr_noduri;i++)
        for(int j=0;j<nr_noduri;j++)
            if(A.G[i][j] + G[i][j] >= 1)S.G[i][j]=1;
            else S.G[i][j]=0;
    S.nr_noduri=nr_noduri;

    return S;
}

void Graf::MatriceaExistenteiDrumurilor()
{
    int d[100][100];
    for(int i=0;i<nr_noduri;i++)
        for(int j=0;j<nr_noduri;j++)
            d[i][j]=G[i][j];
    for(int i=0;i<nr_noduri;i++)
        for(int j=0;j<nr_noduri;j++)
            for(int k=0;k<nr_noduri;k++)
              if(i!=k && k!=j && G[i][k] && G[k][j])
                d[i][j]=1;
    for(int i=0;i<nr_noduri;i++)
    {
        for(int j=0;j<nr_noduri;j++)
            cout<<d[i][j]<<' ';
        cout<<'\n';
    }


}
int main()
{
  /*  Graf gf;
    fin>>gf;
    int nr;
    gf.ComponenteConexeAdancime();
    gf.ComponenteConexeLatime();
    gf.VerificareConex();*/

    Graf A,C;
    fin>>A;
    A.MatriceaExistenteiDrumurilor();

   // C=A+B;


 //   cout<<C;
    return 0;
}
