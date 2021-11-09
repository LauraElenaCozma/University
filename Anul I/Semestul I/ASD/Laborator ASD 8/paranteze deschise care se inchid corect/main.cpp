#include <iostream>

using namespace std;
int paranteze(char c[])
{
    cin>>c;
    int k=0,i;
    for(i=0;c[i];c++)
    {
        if(c[i]=='(')k++;
        else k--;
        if(k<0)return 0;
    }
    if(k!=0)return 0;
    return 1;

}
int main()
{
    char c[101];
    if(paranteze(c))cout<<"Corect";
    else cout<<"Incorect";
    return 0;
}
