#include <iostream>
#include <fstream>
#include <vector>
#include <climits>


using namespace std;
ifstream fin("f.in");

void read (vector <int> &a , int &lengthA , vector <int> &b , int &lengthB)
{
    fin>>lengthA;
    a.resize(lengthA + 2);
    for(int i=1 ; i<=lengthA ; i++)
        fin>>a[i];

    fin>>lengthB;
    b.resize(lengthB + 2);
    for(int i=1 ; i<=lengthB ; i++)
        fin>>b[i];
}


float medianOfTwoSortedArraysOfDifferentLenght(vector <int> a , int lengthA , vector <int> b , int lengthB , int left , int right)
{

        int partitionA = (left + right) / 2;  //number of elements on the left side of first array
        int partitionB = (lengthA + lengthB + 1) / 2 - partitionA; //number of elements on the left side of second array

        cout<<partitionA<<' '<<partitionB<<' '<<left<<' '<<right<<'\n';
        if(a[partitionA] <= b[partitionB + 1])
            if(b[partitionB] <= a[partitionA + 1]){
            //the partitions are correcly done

                if((lengthA + lengthB) % 2 ){
                    //if the merged vector is odd there is a single median element on the position (lengthA + lengthB + 1)/2
                    return max(a[partitionA] , b[partitionB]); //the biggest element of the left side
                    }
                else return (max(a[partitionA] , b[partitionB]) + min(a[partitionA + 1] , b[partitionB + 1])) / 2.0;
            }
            else return medianOfTwoSortedArraysOfDifferentLenght(a , lengthA , b , lengthB , partitionA + 1 , right); //we do the recursion on the right side. PartitionA needs more elements

        else return medianOfTwoSortedArraysOfDifferentLenght(a , lengthA , b , lengthB , left , partitionA - 1);//we do the recursion on the left side. PartitionA needs less elements

}

int main()
{


    vector <int> a , b;
    int lengthA , lengthB;

    read(a , lengthA , b , lengthB);

    a[0] = INT_MIN;  //if partitionA = 0
    a[lengthA + 1] = INT_MAX;

    b[0] = INT_MIN;  //if partitionB = 0
    b[lengthB + 1] = INT_MAX;


    if(lengthA < lengthB)
        cout<<medianOfTwoSortedArraysOfDifferentLenght(a , lengthA , b , lengthB , 1 , lengthA );
    else cout<<medianOfTwoSortedArraysOfDifferentLenght(b , lengthB , a , lengthA , 1 , lengthB );

    fin.close();
    return 0;
}

/*
Examples:
6
3 5 7 9 11 16
4
23 26 31 35


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
13
*/
