#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
ifstream fin("f.in");
struct point
{
    float x,y;
};

int viraj(point a,point b, point c)
{
    float val = (b.x - a.x)*(c.y-a.y) - (b.y-a.y) * (c.x-a.x);

    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: -1; // clock or counterclock wise
}

bool cmp(point a,point b)
{
    return ((a.x<b.x) || (a.x==b.x && a.y<b.y));
}

void convex_hull(vector <point> &a,int dim)
{
    sort(a.begin(),a.end(),cmp);

    vector <point> inf;
    inf.push_back(a[0]);
    inf.push_back(a[1]);


    int index=1;
    for(int i=2 ; i<dim ; i++)
    {

        inf.push_back(a[i]);
        index++;

        while(inf.size()>2)
        {

            if(viraj(inf[index-2],inf[index],inf[index-1])>=0)
            {

                 point aux=inf[index];
                 inf.pop_back();
                 inf.pop_back();
                 inf.push_back(aux);

                 index--;
            }
            else break;
        }
    }

    vector <point> sup;
    sup.push_back(a[dim-1]);
    sup.push_back(a[dim-2]);
    index=1;  //stie pozitia ultimului element din vector

    for(int i=dim-3 ; i>=0 ; i--)
    {

        sup.push_back(a[i]);
        index++;

        while(sup.size()>2)
        {
            if(viraj(sup[index],sup[index-2],sup[index-1])<=0)
            {
                 point aux=sup[index];
                 sup.pop_back();
                 sup.pop_back();
                 sup.push_back(aux);

                 index--;

            }
            else break;
        }
    }

    vector <point> sol;


    for(point a : inf)
        cout<<a.x<<' '<<a.y<<'\n';
    cout<<'\n';

    for(point a : sup)
        cout<<a.x<<' '<<a.y<<'\n';
    cout<<'\n';

    inf.pop_back();
    sol.insert(sol.end(),inf.begin(),inf.end());
    sol.insert(sol.end(),sup.begin(),sup.end());
    sol.pop_back();

   cout<<"Acoperirea convexa:\n";
    for(point a : sol)
        cout<<a.x<<' '<<a.y<<'\n';
    cout<<'\n';
    cout<<'\n';

    vector <point> I;
    vector <point> J;

    if(sol.size()==3)
    {
        I.insert(I.end(),sol.begin(),sol.end());

        for(int i=0;i<dim;i++)
        {
            int found=0;
            for(int j=0;j<I.size() && !found;j++)
                if(a[i].x==I[j].x && a[i].y==I[j].y)found=1;

            if(!found)
            {
                J.push_back(a[i]);
                break;
            }
        }

    }

    else if(sol.size()==2)
    {
        I.push_back(a[0]);
        I.push_back(a[3]);

        J.push_back(a[1]);
        J.push_back(a[2]);
    }
    else if(sol.size()==4)
    {
        I.push_back(sol[0]);
        I.push_back(sol[2]);
        J.push_back(sol[1]);
        J.push_back(sol[3]);
    }

    for(point a : I)
        cout<<a.x<<' '<<a.y<<'\n';
    cout<<'\n';

    for(point a : J)
        cout<<a.x<<' '<<a.y<<'\n';

}
int main()
{
    vector < point >  a;
    a.resize(4);

    for(int i=0;i<4;i++)
        fin>>a[i].x>>a[i].y;

    convex_hull(a,4);


    return 0;
}

/* triunghi
1 5
2 7
-5 3
4 -7
*/
