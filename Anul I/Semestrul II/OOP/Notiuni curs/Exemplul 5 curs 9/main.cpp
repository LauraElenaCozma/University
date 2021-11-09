#include <iostream>

using namespace std;

class Pet{public: virtual ~Pet(){}};

class Dog: public Pet{
public:
    void latra(){}
};

class Cat: public Pet{};


int main()
{
    Pet *b=new Cat;
    Dog* d1=dynamic_cast<Dog *>(b);
    Cat* d2=dynamic_cast<Cat*>(b);
    cout<<"d1= "<<d1<<endl;
    cout<<"d2= "<<d2<<endl;
    cout<<"b= "<<b<<endl;
    return 0;
}
