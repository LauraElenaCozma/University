#include <iostream>
#include <fstream>
#include <vector>
#include <climits>


using namespace std;
ifstream fin("f.in");

void read (vector <int> &a , int &lengthA , vector <int> &b , int &lengthB)
{
    fin>>lengthA;
    a.resize(lengthA);
    for(int i=0 ; i<lengthA ; i++)
        fin>>a[i];

    fin>>lengthB;
    b.resize(lengthB);
    for(int i=0 ; i<lengthB ; i++)
        fin>>b[i];
}


float medianOfTwoSortedArraysOfDifferentLenght(vector <int> a , int lengthA , vector <int> b , int lengthB )
{
    int left = 0;
    int right = lengthA; //we are searching which position we want to cut.
    int maxLeftA , maxLeftB , minRightA , minRightB;
    while(left <= right)
    {
        int partitionA = (left + right) / 2;  //number of elements on the left side of first array
        int partitionB = (lengthA + lengthB + 1) / 2 - partitionA; //number of elements on the left side of second array

        if(partitionA == 0)
            maxLeftA = INT_MIN;
        else maxLeftA = a[partitionA - 1];

        if(partitionA == lengthA)
            minRightA = INT_MAX;
        else minRightA = a[partitionA];

        if(partitionB == 0)
            maxLeftB = INT_MIN;
        else maxLeftB = b[partitionB - 1];

        if(partitionB == lengthB)
            minRightB = INT_MAX;
        else minRightB = b[partitionB];

        if(maxLeftA <= minRightB)
            if(maxLeftB <= minRightA)
        {
            //we have partitioned arrays at correct place
            if((lengthA + lengthB) % 2)
                return max(maxLeftA , maxLeftB);
            else return (max(maxLeftA , maxLeftB) + min(minRightA , minRightB)) / 2.0;
        }
             else left = partitionA + 1; //partition needs more elements. we go to the right
        else right = partitionA - 1;   //we do the recursion on the left side. PartitionA needs less elements
    }





}

int main()
{


    vector <int> a , b;
    int lengthA , lengthB;

    read(a , lengthA , b , lengthB);

    if(lengthA < lengthB)
        cout<<medianOfTwoSortedArraysOfDifferentLenght(a , lengthA , b , lengthB );
    else cout<<medianOfTwoSortedArraysOfDifferentLenght(b , lengthB , a , lengthA );

    fin.close();
    return 0;
}

/*
Examples:
6
3 5 7 9 11 16
4
23 26 31 35
13.5


5
1 3 8 9 15
6
7 11 18 19 21 25
11

4
2 3 5 8
6
10 12 14 16 18 20
11

4
2 3 5 8
6
10 12 14 16 18 20
11
*/
