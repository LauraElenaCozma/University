#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("data.in");

void read(int a[][4] , int &n)
{
    fin>>n;
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
            fin>>a[i][j];
    }
}

void printPermutation(int a[][4] , int noOfPerm , int k)
{
    //k = the index where the permutation begin
    vector <int> aux;
    aux.resize(4);
    int pos = 1;
    for(int i = 0 ; i < 4 ; i++)
    {
        aux[pos] = a[noOfPerm][k];
        k = (k + 1) % 4;
        pos = (pos + 1) % 4;
    }
    for(int i = 0 ; i < 4 ; i++)
        cout<<aux[i];
}

void printPath(int a[][4] , int n , int len[][4] , vector <vector <pair <int , int> > > prev , pair <int , int> coordElement)
{
    if(coordElement.first != -1)
    {
        printPath(a , n , len , prev , prev[coordElement.first][coordElement.second]);
        printPermutation(a , coordElement.first , coordElement.second);
        cout<<'\n';
    }
}
int maxLength = 0;
pair <int , int> coordMax;
void sequenceOfPerm(int a[][4] , int n)
{

    int len[n][4];
    vector <vector <pair <int , int> > > prev;
    prev.resize(n);
    for(int i = 0 ; i < n ; i++)
        prev[i].resize(4);
    for(int i = 0 ; i < 4 ; i++)
    {
        len[0][i] = 1;   //first element in a sequence
        prev[0][i].first = -1;
        prev[0][i].second = -1;
    }

    for(int i = 1 ; i < n ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            int maxL = -1;
            for(int q = 0 ; q < i ; q++)
            {

                for(int r = 0 ; r < 4 ; r++)
                {
                    //a[i][j] current element
                    //a[q][r] previous element
                    //len[q][r] length since that element
                    if(a[i][j] > a[q][r] && a[i][(j + 2) % 4] < a[q][(r + 2) % 4] && len[q][r] > maxL)
                    {
                        maxL = len[q][r];
                        prev[i][j].first = q;  //the coordinates of the previous element
                        prev[i][j].second = r;
                    }
                }
            }
            if(maxL != -1)len[i][j] = maxL + 1;
            else
            {
                len[i][j] = 1;
                prev[i][j].first = -1;
                prev[i][j].second = -1;
            }

            if(len[i][j] > maxLength)
            {
                maxLength = len[i][j];
                coordMax.first = i;
                coordMax.second = j;
            }

        }

    }
    cout<<maxLength<<'\n';

    for(int i = 0 ; i < n; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
           if(len[i][j]== maxLength)
           {
               pair <int, int> coord;
               coord.first = i;
               coord.second = j;
               printPath(a , n , len , prev , coord);
           cout<<"\n";}
    }

   // cout<<coordMax.first<<' '<<coordMax.second<<'\n';
   // printPath(a , n , len , prev , coordMax);
}
int main()
{
    int n , a[100][4];
    read(a ,n);

    sequenceOfPerm(a , n);
    return 0;
}
