#include <iostream>

using namespace std;
class D;
class B
{
    int x;
public:
    virtual afis() { cout<<"Baza ";}
    B(int x1)
    {
        x=x1;
        afis();
    }
};


class D: public B
{
    int y;
public:
    afis() { cout<<"Derivata ";}
    D(int x,int y1) : B(x)
    {
        y=y1;
        afis();
    }
};
int main()
{
   // B a(3);
    D b(4,5);
    //B * point=new D(5,8);
    return 0;
}
