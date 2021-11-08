#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("f.in");

void divide(vector <int> v , int n , int left , int right , int &pos)
{
    //pos is the position of the first even element
    if(left < right)
    {
        int m = (left + right) / 2;
        if(v[m] % 2 == 1) //v[m] is odd
        {
            if(v[m] % 2 == v[m + 1] % 2)
            {
                if(v[m] % 2 == v[m - 1] % 2)
                    divide(v , n , m + 1 , right , pos);
            }
            else //odd odd even
            {
                cout<<"odd odd even";
                pos = m + 1;
                return ;
            }
        }
        else
        {
            if(v[m] % 2 == v[m + 1] % 2)
            {
                if(v[m] % 2 == v[m - 1] % 2)
                    divide(v , n , left , m - 1 , pos);
                else
                {
                    //odd even even
                    cout<<"odd even even";
                    pos = m;
                    return ;
                }
            }
        }
    }
}

int main()
{
    vector <int> v;
    int n;
    fin>>n;
    v.resize(n + 2);
    for(int i = 1 ; i <= n ; i++)
        fin>>v[i];
    v[0] = 1; // add 2 aux number at the end and at the beginning of the vector not to have different cases in divide
    v[n + 1] = 0;
    int pos;
    divide(v , n , 1 , n , pos);
    cout<<pos;
    cout<<"Impare:"<<pos<<"\nPare:"<<n - pos + 1;
    return 0;
}
