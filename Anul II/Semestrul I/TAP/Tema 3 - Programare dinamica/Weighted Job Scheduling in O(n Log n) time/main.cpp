#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
ifstream fin("data.in");
struct Job
{
    int st, fin, profit;
    bool vis; //to be easier when we print the solution
};
struct Solution
{
    int ant , pres;
};
void read(vector <Job> &v , int &n)
{
    fin>>n;
    v.resize(n);

    for(int i = 0 ; i < n ; i++)
    {
        fin>>v[i].st>>v[i].fin>>v[i].profit;
        v[i].vis = 0;
    }
}

bool cmp(Job a , Job b)
{
    return (a.fin < b.fin);
}


int binarySearch(vector <Job> v , int index)
{
    int start = 0 , finish = index - 1;

    while(start <= finish)
    {
        int mid = (start + finish) / 2;
        if(v[mid].fin <= v[index].st)
        {
            if(v[mid + 1].fin <= v[index].st)
                start = mid + 1;
            else return mid;
        }
        else finish = mid - 1;

    }
    return -1;
}
void printPath(vector <Job> &v , vector <Solution> sol , int position)
{
    if((sol[position].pres != position && sol[position].ant == -1) || (sol[position].pres == position && sol[position].ant != -1))
    {
        if(sol[position].ant != -1)
        {
            printPath(v , sol , sol[position].ant);
            if(!v[sol[position].ant].vis)
                cout<<v[sol[position].ant].st<<' '<<v[sol[position].ant].fin<<' '<<v[sol[position].ant].profit<<'\n';
            v[sol[position].ant].vis = 1;
        }
        else
            printPath(v , sol , sol[position].pres);
        if(!v[sol[position].pres].vis)
        {
            cout<<v[sol[position].pres].st<<' '<<v[sol[position].pres].fin<<' '<<v[sol[position].pres].profit<<'\n';
            v[sol[position].pres].vis = 1;
        }
    }


}
void maximizeProfit(vector <Job> v , int n)
{
    sort(v.begin() , v.end() , cmp);

    vector <int> opt;
    vector <Solution> sol;
    opt.resize(n);
    sol.resize(n);

    opt[0] = v[0].profit;
    sol[0].ant = -1;
    sol[0].pres = 0;

    for(int i = 1 ; i < n ; i++)
    {
        int newMaxProfit = v[i].profit;
        int index = binarySearch(v , i);
        if(index != -1)
            newMaxProfit += opt[index];

        if(newMaxProfit > opt[i - 1])
        {
            opt[i] = newMaxProfit;
            sol[i].pres = i;
            if(index != -1)sol[i].ant = sol[index].pres;
            else sol[i].ant = -1;
        }
        else
        {
            opt[i] = opt[i - 1];
            sol[i].pres = sol[i - 1].pres;
            sol[i].ant = -1;
        }
    }

    cout<<opt[n - 1]<<'\n';
    printPath(v , sol , n - 1);
}
int main()
{
    vector <Job> v;
    int n;
    read(v , n);
    maximizeProfit(v , n);
    return 0;
}
