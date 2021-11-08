#include <iostream>

using namespace std;


int main()
{
    int n;
    cin>>n;
    if(n & (n-1) )cout<<"nu";
    else cout<<"da";
    return 0;
}
