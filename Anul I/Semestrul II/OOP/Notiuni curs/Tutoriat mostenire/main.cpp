#include <iostream>

using namespace std;
///1
/*
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
}
*/

///2
/*8
class base {
int arr[10];
};
class b1: public base { };
class b2: public base { };
class derived: public b1, public b2 {};
int main(void)
{
cout<<sizeof(derived);
return 0;
}*/

///3
/*
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
}
*/

///4
/*
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
Derived (int i):x(i) { }
void print() { cout << x ;}
};
int main()
{
Derived d(10);
d.print();
}
*/

///5
/*
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
}
*/

///6
/*
class cls1
{ protected: int x;
public: cls1(){ x = 13; } };
class cls2: public cls1
{ int y;
public: cls2(){ y = 15; }
int f(cls2 ob) { return (ob.x+ob.y); } };
int main()
{ cls2 ob; cout<<ob.f(ob);
return 0;
}
*/

///7
/*
class cls1
{ protected: int x;
public: cls1(){cout<<"C1\n"; x = 13; }
cls1(const cls1& ob) {cout<<"copy1\n";}};
class cls2: public cls1
{ int y;
public: cls2(){ cout<<"C2\n";y = 15; }
cls2(const cls2& ob) :cls1(ob){cout<<"copy2\n";}
int f(cls2 ob) { return (ob.x+ob.y); } };
int main()
{ cls2 ob; cout<<ob.f(ob);
return 0;
}*/

///8
/*
class cls1
{ protected: int x;
public: cls1(int i=10) { x=i; }
int get_x() { return x;} };
class cls2: cls1
{ public: cls2(int i):cls1(i) {} };
int main()
{ cls2 d(37);
cout<<d.get_x();
return 0;
}*/

///10
/*
class B {
static int x;
int i;
public: B() {
x++;
i = 1;
}
~B() {
x--;
}
static int get_x() { return x; }
int get_i() { return i; }
};
int B::x;
class D: public B {
public: D() { x++; }
~D() { x--; }
};
int f(B *q) {
return (q->get_i()) + 1;
}
int main() {
B *p = new B;
cout << f(p);
delete p;
p = new D;
cout << f(p);
delete p;
cout << D::get_x();
return 0;
}
*/

///11
/*
class A {
protected:
int x;
public:
A(int i = 14) { x = i; }
};
class B: A {
public:
B(B &b) {
x = b.x;
}
void afisare() {
cout << x;
}
};
int main() {
B b1, b2(b1);
b2.afisare();
return 0;
}*/

///12
/*
class A
{ protected: int x;
public: A(int i=14) { x=i; } };
class B: A
{ public: B():A(2){}
B(B& b) { x=b.x-14; }
void afisare() { cout<<x; } };
int main()
{ B b1, b2(b1);
b2.afisare();
return 0;
}*/

///13
/*
class B
{ protected: static int x;
int i;
public: B() { x++; i=1; }
~B() { x--; }
static int get_x() { return x; }
int get_i() { return i; } };
int B::x;
class D: public B
{ public: D() { x++; i++;}
~D() { x--; i--;}
int f1(B o){return 5+get_i();} };
int f(B *q)
{ return (q->get_x())+1; }
int main()
{ B *p=new B[10];
cout<<f(p);
delete[] p;
p=new D;
cout<< p->f1(p);
delete p;
cout<<D::get_x();
return 0;
}*/

///14
class A
{ int x;
public: A(int i):x(i){}
int get_x(){ return x; } };
class B: public A
{ int y;
public: B(int i,int j):y(i),A(j){}
int get_y(){ return y; } };
class C: protected B
{ int z;
public: C(int i,int j,int k):z(i),B(j,k){}
int get_z(){ return z; } };
int main() {
C c(1, 2, 3);
cout << c.get_x() + c.get_y() + c.get_z();
return 0;
}
