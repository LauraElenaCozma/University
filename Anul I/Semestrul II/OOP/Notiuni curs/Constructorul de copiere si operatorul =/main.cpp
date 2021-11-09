#include <iostream>

using namespace std;

class A
{
    int x;
    public:

    A()
    {
        x=0;
    }
    A(const A& ob);
    const A& operator = (const A& other);


     void setx(int nr);

     friend A returneaza(A ob)
     {
         cout<<"ret ";
         return ob;
     }
     void afisare();
};

A::A(const A& other)
{
    cout<<"Constructor de copiere\n";
    this->x=other.x;
}

const A& A::operator = (const A& other)
{
    cout<<"Operator =\n";
    this->x=other.x;
    return (*this);
}

void A::setx(int nr)
{
    x=nr;
}

void A::afisare()
{
    cout<<x<<'\n';
}

int main()
{
    A ob1,ob2;
    ob1.setx(32);
    ob2=ob1;
    ob1.afisare();
    ob2.afisare();
    A ob3=ob1,ob4;
    ob4=returneaza(ob1);
    ob3.afisare();
    return 0;
}
