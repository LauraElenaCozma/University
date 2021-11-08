#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("data.in");
/*
a (biggestSizeSquare) - print the coordinates of the top left edge and the size of a square of all 0s of maximum size contained by the matrix a
b (sizeGreaterThanK) - print the number of squares of all 0s of size >= k contained by the matrix a
*/

int allocateMatrix(int **&a , int n , int m)
{
     a = new(nothrow) int*[n];

     if(a == NULL)
     {
         printf("Allocation Failure\n");
         return -1;
     }
     for(int i = 0 ; i < n ; i++)
     {
         a[i] = new(nothrow) int[m];
         if(a[i] == NULL)
         {
             printf("Allocation Failure\n");
             return -1;
         }
     }
     return 1;

}
int read(int **&a , int &n , int &m , int &k)
{
    fin>>n>>m;
    if(allocateMatrix(a , n , m) == -1) return -1;

    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < m ; j++)
            fin>>a[i][j];

    fin>>k;
    for(int i = 0 ; i < n ; i++)
       {
           for(int j = 0 ; j < m ; j++)
            cout<<a[i][j]<<' ';
           cout<<'\n';
       }
    return 1;
}

int squareSubMatrix(int **a , int n , int m , int **&s)
{
    if(allocateMatrix(s , n , m) == -1) return -1;

    for(int i = 0 ; i < m ; i++)
        if(a[n - 1][i] == 0)
             s[n - 1][i] = 1;//we can form a matrix of dimension = 1 with that element
        else s[n - 1][i] = 0;

    for(int i = 0 ; i < n ; i++)
        if(a[i][m - 1] == 0)
             s[i][m - 1] = 1;
        else s[i][m - 1] = 0;

    for(int i = n - 2 ; i >= 0 ; i--)
        for(int j = m - 2 ; j >=0 ; j--)
        {
            if(a[i][j] == 1)
                s[i][j] = 0; //we can't form a submatrix of 0s because the first element is 1
            else
                s[i][j] = min(s[i][j + 1] , min(s[i + 1][j] , s[i + 1][j + 1])) + 1;
        }
        cout<<'\n';
        for(int i = 0 ; i < n ; i++)
       {
           for(int j = 0 ; j < m ; j++)
            cout<<s[i][j]<<' ';
           cout<<'\n';
       }
    return 1;
}

void biggestSizeSquare(int **s , int n , int m , int &sz , int &col , int &row)
{
    sz = 1;
    row = n - 1;
    col = n - 1;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < m ; j++)
            if(s[i][j] > sz)
            {
                sz = s[i][j];
                row = i + 1;//we started counting from 0
                col = j + 1;
            }
}

void sizeGreaterThanK(int **s , int n , int m , int k , int &noOfSquares)
{
    noOfSquares = 0;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < m ; j++)
            if(s[i][j] >=k)
                noOfSquares += s[i][j] - k + 1;
}
int main()
{
    int **a , n , m , k , **s;
    int maxSize , col , row;
    int noOfSquares;
    if(read(a , n , m , k) == -1)
    {
        cout<<"Allocation Failure\n";
        return -1;
    }
    if(squareSubMatrix(a , n , m , s) == -1)
    {
        cout<<"Allocation Failure\n";
        return -1;
    }

    biggestSizeSquare(s , n , m , maxSize , col , row);
    cout<<"Max size of a square formed by 0s is "<<maxSize<<" and the top left edge is ( "<<row<<" , "<<col<<")\n";

    sizeGreaterThanK(s , n , m , k , noOfSquares);

    cout<<"The number of squares of size >= k  is "<<noOfSquares<<'\n';

    for(int i = 0 ; i < n ; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}
