#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("f.in");
int main()
{
    vector <int> v;
    int s;

    fin>>s;
    v.resize(3);
    for(int i = 0 ; i < 3 ; i++)
        fin>>v[i];

    vector <int> sum(s + 1, -1);
    sum[0] = 0;
    for(int i = 1 ; i < =n ; i++)
    {
        int maxi = -1;
        for(int j = 0 ; j <= 2 ; j++)
        {
            if(sum[i - v[j]] > maxi)
            {
                maxi = sum[i - v[j]];
            }
        }

        if(maxi != -1)
            v[i] = maxi + 1;
    }

    for(int i = 1 ; i <= s ; i++)
        cout<<sum[i]<<'\n';
    return 0;
}
