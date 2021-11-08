#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;

ifstream fin("f.in");
///nu stiu daca complexitatea e o(n) sau mai mare
int main()
{
    int n,x,y,m;

    fin>>n>>m; //m==n-1
    vector <int> degree(n+1,0);
    vector <int> visited(n+1,0);
    vector <int> sel,unsel;
    vector < list <int> > L;
    L.resize(n+1);
    for(int i=0;i<n-1;i++)
    {
        fin>>x>>y;
        L[x].push_back(y);
        L[y].push_back(x);
        degree[x]++;
        degree[y]++;
    }

    int nsel=0; //the number of selected vertices

    int qsel=0 , qunsel=0;
    for(int i=1;i<= n;i++)
    {
        if(degree[i]==1) //it's a leaf
    {
        visited[i]=2;     //2=visited and put in selected
        sel.push_back(i); //we know that the leaves are selected
        nsel++;
        qsel++;
    }
    }

    int psel=0 , punsel=0;
    while(nsel!=n)
    {
        while(psel<qsel && nsel!=n)
        {

            for(int e : L[sel[psel]])
            {
                if(!visited[e])
                {
                    visited[e]=1;    //1=visited and put in unselected
                    unsel.push_back(e);
                    qunsel++;         //the index of the last unselected element
                    nsel++;
                }

                if(nsel==n)break;
            }
            psel++;
        }

        while(punsel<qunsel && nsel!=n)
        {

            for(int e : L[unsel[punsel]])
            {
                if(!visited[e])
                {
                    int ok=0;       //verificam sa nu aiba vecini vizitati
                    for(int f : L[e])
                        if(visited[f]==2)//selected
                            ok=1;

                    if(!ok)
                    {
                        visited[e]=2;
                        sel.push_back(e);
                        qsel++;         //the index of the last unselected element
                        nsel++;
                    }
                }

                if(nsel==n)break;
            }
            punsel++;
        }



    }

    for(int x : sel)
        cout<<x<<' ';


    return 0;
}
