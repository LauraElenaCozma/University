#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");

void read(int &n,vector <int> &v)
{
    fin>>n;
    v.resize(n);
    for(int i=0;i<n;i++)
        fin>>v[i];
}
int merge_function(int st,int m,int dr,vector <int> &v)
{
    int i=st;
    int j=m+1;
    int nr_inv=0;

    vector <int> aux;

    while( i<=m && j<=dr)
    {
        if(v[i] > 2 * v[j])
        {
            nr_inv += (m - i + 1);  //the i th element forms a signifiant inversion and also all the elements from i+1 to middle => middle - i + 1 elements

            j++;
        }
        else i++;

    }
    i=st;
    j=m+1;

    while( i<=m && j<=dr)
    {
        if(v[i] <= v[j])
        {
            aux.push_back(v[i++]);
        }
        else
        {
            aux.push_back(v[j++]);
        }

    }

    while(i<=m)
        aux.push_back(v[i++]);
    while(j<=dr)
        aux.push_back(v[j++]);

    int index=st;
    for(int x : aux)
    {
        v[index]=x;
        index++;
    }
    return nr_inv;
}


int divide(int st,int dr, vector <int> &v)
{
    int nr_inv = 0;
    if(dr-st==1)
    {

        if(v[st]>2*v[dr])
        {
            swap(v[st],v[dr]);
            return 1;
        }
        else if(v[st]>v[dr])
            swap(v[st],v[dr]);

        return 0;
    }

    if(st==dr)
        return 0; //there is only one element and no inversions

    if(st < dr && dr-st!=1)
    {
        int mij=(st+dr)/2;
        nr_inv+=divide(st,mij,v);
        nr_inv+=divide(mij+1,dr,v);
        nr_inv+=merge_function(st,mij,dr,v); //merge finds the inversions with one element in one side the one in the other side


    }

    return nr_inv;


}
int main()
{
    int n;
    vector <int> v;
    read(n,v);
    cout<<divide(0,n-1,v);
    return 0;
}
