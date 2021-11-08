#include <iostream>
#include <fstream>
#include <algorithm>
#include <climits>
using namespace std;
const int NMAX = 5000;
ifstream fin("data.in");
int n , k;
int v[NMAX + 5] , d[NMAX+5][NMAX+5];
//d[i][j] = total weight if we have a total of j cuts and the last is on i position

void read()
{
	fin >> n >> k;
	for (int i = 0 ; i < n ; i++)
		fin >> v[i];
    ///have to partition k into k sequences
    ///so we have k - 1 cuts
    k--;
}
int pond(int first , int last)
{
    return (v[first] - v[last]) * (v[first] - v[last]);
}
void dynamicProgramming()
{
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < k ; j++)
            d[i][j] = INT_MAX;

    //already know the result if we make only a cut
    for(int i = 0 ; i < n ; i++)
    {
        //cut after i position
        d[i][0] = pond(0 , i) + pond(i + 1 , n - 1);
    }

    for(int cut = 1 ; cut < k ; cut++)
    {
        for(int i = cut ; i < n ; i++)
        {
            //we start i from cut because if we have to do the second cut(for example; here the second cut is cut = 1) we should have one cut before
            //so another cut is made after the first element(best case). we do our cut after the second element(minimum)
            int minPond = INT_MAX;

            for(int j = 0 ; j < i ; j++)
            {
                //compute the value of a new pond if we had a cut after j and another one after i
                int newPond = d[j][cut - 1] - pond(j + 1 , n - 1) + pond(j + 1 , i) + pond(i + 1 , n - 1);
                if(newPond < minPond)
                    minPond = newPond;

            }
            if(minPond != INT_MAX)
                d[i][cut] = minPond;
        }
    }

    int minFinalPond = INT_MAX;
    for(int i = 0 ; i < n ; i++)
    {
        if(d[i][k - 1] < minFinalPond)
            minFinalPond = d[i][k - 1];
    }

    cout<<minFinalPond;
}

int main()
{
    read();
    dynamicProgramming();
    return 0;
}
