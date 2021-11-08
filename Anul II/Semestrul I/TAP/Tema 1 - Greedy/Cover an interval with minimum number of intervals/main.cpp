#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
ifstream fin("data.in");
class Interval
{
public:
    int st;
    int fin;
};

int cmp(Interval i1 , Interval i2)
{
    //order in ascending order
    return (i1.st < i2.st);
}

void coverInterval(vector <Interval> v , int n , Interval a)
{
    sort(v.begin() , v.end() , cmp);

    if(v[0].st > a.st)
    {
        cout<<"1 - Impossible to compute a cover\n";
        //because the interval between a.st and v[0].st - 1 cannot be covered
        return ; //finished program. stop
    }
    int ok = 0;
    int stIndex = 0;
    vector <Interval> sol; //will keep the intervals of the solution
    do
    {
        //search for an interval vi.st <= a <= vi.fin such that vi.fin is maximum
        int maximum = -1;
        int newIntervalAdded;
        while(stIndex < n)
        {
            if(v[stIndex].st <= a.st && v[stIndex].fin >= a.st)
            {
                if(v[stIndex].fin > maximum)
                {
                    maximum = v[stIndex].fin;
                    newIntervalAdded = stIndex;
                }
            }
            stIndex ++;
        }

        if(maximum == -1)
        {
            int len = sol.size();
        for(int i = 0 ; i < len ; i++)
            cout<<sol[i].st<<' '<<sol[i].fin<<'\n';
            cout<<"2 - Impossible to compute a cover  "<<a.st<<' '<<a.fin<<'\n';
            //because there are some portions left uncovered
            return ; //finished program. stop
        }
        else
        {
            sol.push_back(v[newIntervalAdded]);
            a.st = v[newIntervalAdded].fin + 1;

            if(a.st >= a.fin)ok = 1; //finished to cover the interval
        }
    }
    while(!ok);

    if(ok == 1)
    {
        int len = sol.size();
        for(int i = 0 ; i < len ; i++)
            cout<<sol[i].st<<' '<<sol[i].fin<<'\n';
    }
}
int main()
{
    vector <Interval> v;
    Interval a;
    fin>>a.st>>a.fin;
    int n;
    fin>>n;
    v.resize(n);
    for(int i = 0 ; i < n ; i++)
        fin>>v[i].st>>v[i].fin;
    coverInterval(v , n , a);
    fin.close();
    return 0;
}
