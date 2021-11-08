#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("f.in");

int nrOfMax;
int maxPath;
void printPath(vector <pair <int,int> > v , int n , vector <int> pred , int index)
{
    if(pred[index] != -1)
    {
        printPath(v , n , pred , pred[index]);
        cout<<v[index].first<<' '<<v[index].second<<'\n';
    }
    else cout<<v[index].first<<' '<<v[index].second<<'\n';
}
void dinamica(vector <pair <int,int> > v , int n)
{
    vector <int> len;
    vector <int> pred;
    len.resize(n);
    pred.resize(n);

    len[0] = 1;
    pred[0] = -1;

    for(int i = 1 ; i < n ; i++)
    {
        int maxL = -1;
        for(int j = 0 ; j < i ; j++)
            if(v[i].first == v[j].second && len[j] > maxL)
        {
            maxL = len[j];
            pred[i] = j;
        }
        if(maxL != -1)
            len[i] = maxL + 1;
        else {
            len[i] = 1;
            pred[i] = -1;
        }
    }
    int indexP;  //where the max length path ends
    for(int i = 0 ; i < n ; i++)
    {
            if(maxPath < len[i])
            {
                maxPath = len[i];
                indexP = i;
                nrOfMax = 1;
            }
            else if(maxPath == len[i])
                nrOfMax ++;
    }
    printPath(v , n , pred , indexP);

    cout<<nrOfMax;
}
int main()
{
    vector <pair <int , int> > v;
    int n;

    fin>>n;
    v.resize(n);

    for(int i = 0 ; i < n ; i++)
    {
        fin>>v[i].first>>v[i].second;
    }
    dinamica(v , n);
    return 0;
}
