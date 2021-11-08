#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
using namespace std;
ifstream fin("data.in");
void read(vector <int> &v , int &n)
{
    fin>>n;
    v.resize(n + 2);//v[0]=v[n+1]=int max

    v[0] = v[n + 1] = INT_MAX;
    for(int i = 1 ; i <= n ; i++)
        fin>>v[i];
}

void findMinPoint(int left , int right , vector <int> v , int n)
{
    if(left < right)
    {
        int m = (left + right) / 2;
        if(v[m - 1] >= v[m] && v[m] <= v[m + 1])//found min point
        {
            cout<<"Minimum point:"<<v[m];
            return ;
        }
        else if(v[m - 1] >= v[m] && v[m] >= v[m + 1])
            findMinPoint(m + 1 , right , v , n);
        else findMinPoint(left , m - 1 , v , n);
    }
    else if(left == right)
    {
        cout<<"Minimum point:"<<v[left];
            return ;
    }
}
int main()
{
    vector <int> v;
    int n;
    read(v, n);
    findMinPoint(1 , n , v , n);
    return 0;
}
