#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;
ifstream fin("data.in");
//let m be the total number of elements
//n arrays are given and k
//we want to select n elements, each from a vector, in order to have the sum of elements equal to k

int allocateMatrix(int **&a , int n , int m)
{
     a = new(nothrow) int*[n];

     if(a == NULL)
     {
         cout<<"Allocation Failure\n";
         return -1;
     }
     for(int i = 0 ; i < n ; i++)
     {
         a[i] = new(nothrow) int[m];
         if(a[i] == NULL)
         {
             cout<<"Allocation Failure\n";
             return -1;
         }
     }
     return 1;

}

int read(int **&a , int &n , int &k)
{
    fin>>n>>k;
    if(allocateMatrix(a , n , 100) == -1) return -1;

    fin.get();
   /* for(int i = 0 ; i < n ; i++)
    {
        fin>>a[i][0];
        for(int j = 1 ; j <= a[i][0] ; j++)
             fin>>a[i][j];
    }*/
    for(int i = 0 ; i < n ; i++)
    {
        char s[1000];
        fin.getline(s , 1000);
        char * p;
        p = strtok(s , " ");
        int k = 0;
        while(p)
        {
            k++;
            a[i][k] = atoi(p);
            p = strtok(NULL , " ");
        }
        a[i][0] = k;
    }

    for(int i = 0 ; i < n ; i++)
       {
           for(int j = 1 ; j <= a[i][0] ; j++)
            cout<<a[i][j]<<' ';
           cout<<'\n';
       }
    cout<<'\n';
    return 1;
}

int sumOfElements(int **a , int n , int k , int **&s)
{
    if(allocateMatrix(s , n , k + 1) == -1) return -1;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j <= k ; j++)
            s[i][j] = 0;

    for(int i = 1 ; i <= a[0][0] ; i++)
        s[0][a[0][i]] = a[0][i];

    for(int i = 1 ; i < n ; i++)
    {
        for(int p = 1 ; p <= a[i][0] ; p++)
        {
            for(int j = 1 ; j <= k ; j++) //we go through all the elements from a[i]
                if(s[i - 1][j] != 0)
                {
                    int sum = j + a[i][p];
                    if(sum <= k)
                        s[i][sum] = a[i][p];
                }

        }

    }
    return 1;
}

void printElementsOfSum(int **s , int n , int sum , int index , int position)
{
    if(index >= 0 && sum != 0)
    {
        printElementsOfSum(s , n , sum - s[index][position] , index - 1 , sum - s[index][position]);
        cout<<s[index][position]<<' ';
    }
}
int main()
{
    int **a , n , k , **s;
    if(read(a , n , k) == -1)
    {
        cout<<"Allocation Failure\n";
        return -1;
    }

    if(sumOfElements(a , n , k , s) == -1)
    {
        cout<<"Allocation Failure\n";
        return -1;
    }
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 1 ; j <= k ; j++)
            cout<<s[i][j]<<' ';
        cout<<'\n';
    }
    if(s[n - 1][k] != 0)
        printElementsOfSum(s , n , k , n - 1 , k);
    else cout<<0;

    for(int i = 0 ; i < n ; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}
