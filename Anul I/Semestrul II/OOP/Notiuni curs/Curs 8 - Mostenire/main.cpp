/*#include <iostream>
using namespace std;

class X {
  int i;
public:
  X() { i = 1; }
  int set(int ii) { cout<<"a "<<i<<'\n';i = ii; cout<<"a "<<i<<'\n';return i;}
  int read() const { return i; }
  int permute() { i = i * 47; cout<<"a "<<i<<'\n'; return i;}
};

class Y : public X {
  int i; // Different from X's i
public:
  Y() { i = 0; }
  int set(int ii) {
    i = ii;
    cout<<"b "<<' '<<i<<'\n';
    return i;
  //  X::set(ii); // Same-name function call
  }
  int change() {
          cout<<"B "<<i<<'\n';
          i = X::set(8); // Different name call
          cout<<"B "<<i<<'\n';
          return i;
  }

};

int main() {

  Y D;
   D.change();
         // X function interface comes through:

}
*/

/*
#include <iostream>
using namespace std;

class Pet {
public:
  void eat() const { cout<<'a'; }
  void speak() const { cout<<2; }
  void sleep() const { cout<<3.0; }
  void sleep(int) const { cout<<4.0; }
};

class Goldfish : Pet { // Private inheritance
public:
  Pet::eat; // Name publicizes member
  Pet::sleep; // Both overloaded members exposed
};

int main() {
  Goldfish bob;
  bob.eat();
  bob.sleep();
  bob.sleep(1);
//! bob.speak();// Error: private member function
}
*/

/*
#include <iostream>
#include <string>
using namespace std;

class Base {
public:
  int f() const {
    cout << "Base::f()\n";
    return 1;
  }
 // int f(string) const { return 1; }
  void g() {}
};

class Derived1 : public Base {
public:
  void g() const {}
};

class Derived2 : public Base {
public:
  // Redefinition:
  int f() const {
    cout << "Derived2::f()\n";
    return 2;
  }
};

class Derived3 : public Base {
public:
  // Change return type:
  void f() const { cout << "Derived3::f()\n"; }};

class Derived4 : public Base {
public:
  // Change argument list:
  int f(int) const {
    cout << "Derived4::f()\n";
    return 4;
  }};

int main() {
  string s("hello");
 Derived1 d1;
 // int x = d1.f();
//  d1.f(s);
  Derived2 d2;
  int x = d2.Base::f();
  //x = d2.f(s); // string version hidden
 // Derived3 d3;
//  d3.f(); // return int version hidden
  Derived4 d4;
 //  x = d4.f(4); // f() version hidden
 // cout<<"-- "<< d4.f(1);
}
*/
/*
#include <iostream>
using namespace std;

class base {
   public:
       int i;
};

// derived1 inherits base.
class derived1 : public base {
  public:
      int j;
};

// derived2 inherits base.
class derived2 : public base {
   public:
       int k;
};

/* derived3 inherits both derived1 and derived2.
This means that there are two copies of base
in derived3! *//*
class derived3 : public derived1, public derived2 {
public:
    int sum;
};

int main()
{
derived3 ob;
ob.derived1::i = 10; // this is ambiguous, which i???
ob.j = 20;
ob.k = 30;
// i ambiguous here, too
ob.sum = ob.derived1::i + ob.j + ob.k;
// also ambiguous, which i?
cout << ob.derived1::i << " ";
cout << ob.j << " " << ob.k << " ";
cout << ob.sum;
return 0;
}
*/


//XII. Spuneþi de câte ori se apeleazã destructorul clasei cls în programul de mai jos. Justificaþi.
/*#include <iostream>
using namespace std;

class cls
{              int x;
  public: cls(int i=0) { x=i; }
               cls(cls& ob) { x=ob.x; }
          ~cls(){cout<<"destr\n";}
};

cls& f(cls &c)  { return c; }

int main()
{   cls r;
    cls s=r;
    f(f(f(s)));
    return 0;
}
*/

///exercitii poo tutoriat
///1 base 1, base 2, derived
/*
#include<iostream>
using namespace std;
class Base1 {
public:
Base1()
{ cout << " Base1's constructor called"<<endl; }
};
class Base2 {
public:
Base2()
{ cout << "Base2's constructor called"<<endl; }
};
class Derived: public Base1, public Base2 {
public:
Derived()
{ cout << "Derived's constructor called"<<endl; }
};
int main()
{
Derived d;
return 0;
}*/


///2 -80
/*#include<iostream>
using namespace std;
class base {
int arr[10];
};
class b1: public base { };
class b2: public base { };
class derived: public b1, public b2 {};
int main(void)
{
cout<<sizeof(derived);
//getchar();
return 0;
}*/

///3 Inside Q
/*#include<iostream>
using namespace std;
class P {
public:
void print()
{ cout <<" Inside P::"; }
};
class Q : public P
{ public:
void print()
{ cout <<" Inside Q"; }
};
class R: public Q {
};
int main(void)
{
R r;
r.print();
return 0;
}*/


///4 -e.c.
/*#include <iostream>
using namespace std;
class A
{
public:
void print() { cout << "A::print()"; }
};
class B : private A
{
public:
void print() { cout << "B::print()"; }
};
class C : public B
{
public:
void print() { A::print(); }
};
int main()
{
C b;
b.print();
}*/

///5 - e.c
/*#include<iostream>
using namespace std;
class Base
{
public:
int fun() { cout << "Base::fun() called";}
int fun(int i) { cout << "Base::fun(int i) called"; }
};
class Derived: public Base
{
public:
int fun(char x) { cout << "Derived::fun(char ) called";}
};
int main()
{
Derived d;
d.fun();
return 0;
}*/

///6 !!!!!!!! eroare de compilare. lista de initializare se foloseste pt variabile strict din clasa curenta
/*#include<iostream>
using namespace std;
class Base
{
protected:
int x;
public:
Base (int i){ x = i;}
};
class Derived : public Base
{
public:
Derived (int i):c(i) { }
void print() { cout << x ;}
};
int main()
{
Derived d(10);
d.print();
}*/


///7 - e.c.
/*#include<iostream>
using namespace std;
class B1 {public: int x;};
class B2 {public: int y;};
class B3 {public: int z;};
class B4 {public: int t;};
class D: public B1, private B2, protected B3, B4 {public: int u;};
int main(){
 D d;
 cout<<d.u;
 cout<<d.x;
 cout<<d.y;
 cout<<d.z;
 cout<<d.t;
 return 0;
}*/

///8 -14
/*#include<iostream>
using namespace std;
class B
{
protected:
 int a;
public:
 B() { a=7; }
};
class D: public B
{
public:
 int b;
 D() { b=a+7; }
};
int main() {
 D d;
 cout<< d.b;
 return 0;
}*/
