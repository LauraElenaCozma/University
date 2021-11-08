#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("citire.in");
struct Punct
{
    float x,y,z;
};

bool pct_distincte(Punct a,Punct b)
{
    if(a.x==b.x && a.y==b.y && a.z==b.z)
        return false;
    return true;
}

void citire_pct(Punct &a)
{
    fin>>a.x>>a.y>>a.z;
}

int main()
{
    Punct A1,A2,A3;
    citire_pct(A1);
    citire_pct(A2);
    citire_pct(A3);

    if(!pct_distincte(A1,A2))
    {
        cout<<"a) Punctele sunt coliniare.\n";
        cout<<"b) A1=1*A2+0*A3.";
    }

    else
    {
        float a;
        if(A1.x!=A2.x)
             a=(float)(A3.x-A1.x)/(A2.x-A1.x);
        else if(A1.y!=A2.y) a=(float)(A3.y-A1.y)/(A2.y-A1.y);
             else a=(float)(A3.z-A1.z)/(A2.z-A1.z);


        if((A3.x-A1.x)==a*(A2.x-A1.x) && (A3.y-A1.y)==a*(A2.y-A1.y) && (A3.z-A1.z)==a*(A2.z-A1.z))
        {
            cout<<"a) Punctele sunt coliniare.\n";
            cout<<"b) A3="<<1-a<<"*A1+"<<a<<"*A2.";
        }
        else cout<<"a) Punctele nu sunt coliniare.";

    }
    return 0;
}
