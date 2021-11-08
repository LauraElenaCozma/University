#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;
ifstream fin("date.in");
ifstream in("cod.in");
void read(string &code , vector <string> &c , int &n)
{
    fin>>n;
    c.resize(n);
    for(int i = 0 ; i < n ; i++)
        fin>>c[i];
    c.push_back("0");
    c.push_back("1");
    n += 2;
    in>>code;
}
void printPath(vector <string> c , int n , vector <int> next , vector <int> strRec , int pos)
{
    if(next[pos] != -1)
    {
        cout<<c[strRec[pos]]<<" + ";
        printPath(c , n , next , strRec , next[pos]);
    }
    else cout<<c[strRec[pos]];
}
void dynamicProgramming(string code , vector <string> c , int n)
{
    vector <int> minPart;
    vector <int> next;
    vector <int> strRec; //the substring used starting i-th position. strRec[i] = index of that substring in c

    int m = code.length();
    minPart.resize(m);
    next.resize(m);
    strRec.resize(m);
    minPart[m - 1] = 1;
    next[m - 1] = -1; //no next element after it
    if(code[m - 1] == '0')
        strRec[m - 1] = n - 2;
    else strRec[m - 1] = n - 1;//it is a binary string. these 2 are the only possibilities

    for(int i = m - 2 ; i >= 0 ; i--)
    {
        int minL = INT_MAX;
        for(int j = 0 ; j < n ; j++)
        {
            int indexF = code.find(c[j] , i);
            if(indexF == i)
            {
                if(minL > minPart[c[j].length() + i])
                {
                    next[i] = c[j].length() + i;
                    strRec[i] = j;
                    minL = minPart[c[j].length() + i];
                }
            }
        }
        if(minL != INT_MAX) //it will be always != -1 because we have 0 and 1 strings
            minPart[i] = minL + 1;
    }

   /* for(int i = 0 ; i < m ; i++)
    {
        cout<<minPart[i]<<' ';
    }
    cout<<'\n';
    cout<<'\n';
    for(int i = 0 ; i < m ; i++)
    {
        cout<<next[i]<<' ';
    }
    cout<<'\n';
    cout<<'\n';
    for(int i = 0 ; i < m ; i++)
    {
        cout<<c[strRec[i]]<<' ';
    }
    cout<<'\n';
    cout<<'\n';*/
    printPath(c, n , next , strRec , 0);
}
int main()
{
    string code;
    vector <string> c;
    int n;
    read(code , c , n);
    dynamicProgramming(code , c , n);
    return 0;
}
