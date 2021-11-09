#include <iostream>

using namespace std;

///1
class Base1 {
public:
Base1()
{ cout << " Base1's constructor called"<<endl; }
Base1(int i)
{
    cout << " Base1's constructor "<<endl;
}
};
class Derived1 : virtual public Base1 {
public:
Derived1()
{ cout << "Derived1's constructor called"<<endl; }

Derived1(int i)
{ cout << "Derived1's constructor"<<endl; }
};
class Derived2: virtual public Base1 {
public:
Derived2()
{ cout << "Derived's constructor called"<<endl; }
Derived2(int i)
{ cout << "Derived's constructor"<<endl; }

};
class MM:public Derived1, public Derived2
{public:
    MM() :Derived2(), Derived1(){cout<<"MM fara\n";}
    MM(int i) { cout<<"MM cu\n";}

};
int main()
{
MM m(4);
return 0;
}
