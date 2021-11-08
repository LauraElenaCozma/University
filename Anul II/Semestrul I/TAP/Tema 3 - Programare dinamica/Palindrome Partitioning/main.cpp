#include <iostream>
#include <string>
#include <climits>

using namespace std;


string printStringBetweenIJ(string s , int i , int j)
{
    string newS;
    for(int k = i ; k <= j ; k++)
        newS += s[k];
    return newS;
}

void printPartitions(string s , int i , int prev[])
{
    if(i != -1)
    {
        printPartitions(s , prev[i] , prev);
        cout<<printStringBetweenIJ(s , prev[i] + 1 , i)<<' ';
    }
    //else cout<<printStringBetweenIJ(s , 0 , i)<<' ';
}
void minPalindromePartitioning(string s)
{
    int n = s.size();

    int c[n];      //the minimum number of cuts made between index 0 and i
    bool p[n][n];  //true if s[i...j] is a palindrome
    int prev[n];   //prev[i] = where the last cut was make between i and j
    prev[0] = -1;  //to know when we should stop
    for(int i = 0 ; i < n ; i++)
    {
        p[i][i] = true; //"a" is a palindrome, like every single string formed by only a letter
    }

    for(int L = 2 ; L <= n ; L++)
    {
        //we take the strings of length 2, after that of length 3 and so on

        for(int i = 0 ; i < n - L + 1 ; i++)
        {
            int j = i + L - 1;  //compute j

            if(L == 2)
                if(s[i] == s[j])p[i][j] = true;
                else p[i][j] = false;
            else
            {
                if(s[i] == s[j] && p[i + 1][j - 1] == true) p[i][j] = true;//is a palindrome is the string except the first and last letter is a palindrome and if the first and the last letters are equal
                else p[i][j] = false;
            }

        }
    }

    for(int i = 0 ; i < n ; i++)
    {
        if(p[0][i] == true)
            {
                c[i]= 0;//is a palindrome so we do have 0 cuts
                prev[i] = -1;//is a palindrome we don't have cuts
            }
            else
            {
                c[i] = INT_MAX;

                for(int j = 0 ; j < i ; j++)
                {
                    //we try to cut it
                    if (p[j + 1][i] == true && 1 + c[j] < c[i])
                        {   c[i] = 1 + c[j];
                            prev[i] = j;
                        }
                }
            }
    }
    //the total number of palindromes in s
    int totalPal = 0;
    for(int i = 0 ; i < n ; i++)
        for(int j = i ; j < n ; j++)
               if(p[i][j] == true)//the substring from i to j is a palindrome
                totalPal ++;

    for(int i = 0 ; i < n ; i++)
       {

            cout<<prev[i]<<' ' ;
         }cout<<'\n';

    cout<<"The total number of palindromes in string is: "<<totalPal<<'\n';
    //the minimum number of partitions of palindromes of s
    printPartitions(s , n - 1 , prev);
    int minPal = c[n - 1] + 1;//+1 because c is the number of cuts and the number of strings is cuts+1
    cout<<"\nThe minimum number of palindrome partitioning of string is: "<<minPal<<'\n';
}
int main()
{

    minPalindromePartitioning("abcbaabc");

    return 0;
}
