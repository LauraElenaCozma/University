#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

ifstream fin("f.in");

bool cmp(pair < int , pair <int , int> > x , pair < int , pair <int , int> > y)
{
    //sortam descrescator dupa timp, si in caz de egalitate descrescator dupa profit
    return (x.second.second>y.second.second || (x.second.second==y.second.second && x.second.first>y.second.first) ) ;
}


class compare
{
public:

    bool operator() (pair < int , pair <int , int> > x, pair < int , pair <int , int> > y)
    {
        //aici sortam descrescator dupa profit. comparatia trebuie facuta invers pt priority queue
        return (x.second.first<y.second.first);
    }
};

int main()
{
    vector < pair < int , pair <int , int> > > v;
    vector <int> sol; //tine minte in ordine indicii solutiei
    int profit = 0;   //tine profitul maxim la finalul problemei
    int n;

    fin>>n;

    v.resize(n);

    for( int i=0 ; i<n ; i++)
    {
        v[i].first=i+1;
        fin>>v[i].second.first>>v[i].second.second;  //second.first e p[i] si second.second e t[i]
    }

    sort(v.begin(),v.end(),cmp) ; //sortam descrescator dupa deadline si in caz de egalitate descrescator dupa profit

    int hour=v[0].second.second; //ora maxima pana la care putem planifica. Vom parcurge pe rand fiecare ora si vedem ce putem planifica la ora respectiva
    int index=0;
    priority_queue < pair < int , pair <int , int> > , vector <pair < int , pair <int , int> > >, compare > pq;


    while(hour > 0 && index < n)
    {
        while(v[index].second.second==hour && index<n)
        {
            //adaugam in pq activitatile care au deadline ul = hour. mai pot exista in pq si activitatile care  au deadline > hour, deci inca mai pot fi planificate
            pq.push(v[index]);
            index++;
        }

        if(!pq.empty())
        {
            //daca avem activitati in pq si se incadreaza in termen, le punem in planificare
            sol.push_back(pq.top().first);
            profit+=pq.top().second.first;
            pq.pop();
        }

        hour--;
    }
    cout<<profit<<'\n';
    for(int x : sol)
        cout<<x<<' ';
    return 0;
}
