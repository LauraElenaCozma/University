#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
ifstream fin("intervale.in");
struct interval
{
    double start , fin , index;
};

void read(int &n , vector <interval> &v)
{
    fin>>n;
    v.resize(n);

    for(int i = 0 ; i < n ; i++)
    {
        v[i].index = i + 1;
        fin>>v[i].start>>v[i].fin;
    }
}

int n;
vector <interval> v;


int pivot(int st , int dr)
{
    int p = st , q = dr;
    interval x = v[p];

    while(p < q)
    {
        while(p < q && v[q].fin > x.fin)
            q --;
        v[p] = v[q];

        while(p < q && v[p].fin < x.fin)
            p ++;
        v[q] = v[p];
    }
    v[p] = x;
    return p;
}

void quickSort(int st , int dr)
{
    if(st < dr)
    {
        int p = pivot(st , dr);
        quickSort(st , p);
        quickSort(p + 1 , dr);
    }
}

void print()
{
    for(int i = 0 ; i < n ; i++)
        cout<<v[i].start<<' '<<v[i].fin<<'\n';

}

int intersect(interval a , interval b)
{
    return !(a.fin < b.start || b.fin <a.start);
}
void greedy()
{
    quickSort(0 , n - 1);
    interval lastInterv = v[0];
    for(int i = 1 ; i < n ; i++)
    {
        if(intersect(lastInterv , v[i])) //if the 2 intervals does intersect
        {
            //eliminate the one that finishes later
            cout<<v[i].index<<'\n';
        }
        else lastInterv = v[i];
    }
}
int main()
{

    read(n , v);
    greedy();
    print();
    return 0;
}
