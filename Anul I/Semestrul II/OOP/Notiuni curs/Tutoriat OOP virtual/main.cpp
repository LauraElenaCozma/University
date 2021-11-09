#include <iostream>

using namespace std;
///1
/*
class Test1
{
int x;
public:
void show() { }
};
class Test2
{
int x;
public:
virtual void show() { }
};
int main(void)
{
cout<<sizeof(Test1)<<endl;
cout<<sizeof(Test2)<<endl;
return 0;
}

*/

///2
/*
class P
{
public:
virtual void show() = 0;
};
class Q : public P {
int x;
void show() {}
};
int main(void)
{
Q q;
return 0;
}
*/

///3
/*
class A
{
public:
virtual void fun() {cout << "A" << endl ;}
};
class B: public A
{
public:
virtual void fun() {cout << "B" << endl;}
};
class C: public B
{
public:
virtual void fun() {cout << "C" << endl;}
};
int main()
{
A *a = new C;
A *b = new B;
a->fun();
b->fun();
return 0;
}*/


///4
/*
template <int N>
class A {
int arr[N];
public:
virtual void fun() { cout << "A::fun()"; }
};
class B : public A<2> {
public:
void fun() { cout << "B::fun()"; }
};
class C : public B { };
int main() {
A<2> *a = new C;
a->fun();
return 0;
}
*/

///5
/*
class B
{ protected: int x;
public: B() { x=78; } };
class D1: virtual public B
{ public: D1() { x=15; } };
class D2: virtual public B
{ public: D2() { x=37; } };
class C: public D2, public D1
{ public: int get_x() { return x; } };
int main()
{ C ob;
 cout<<ob.get_x();
 return 0;
}
*/

///6
/*
class A {
 public:
 int x;
 A(int i = 0) { x = i; }
 virtual A minus() { return (1 - x); }
};
class B: public A {
public: B(int i = 0) { x = i; }
 void afisare() { cout << x; }
};
int main() {
 A *p1 = new B(18);
 *p1 = p1->minus();
 p1->afisare();
 return 0;
}
*/

///7
/*
class A
{ protected:
 int x;
public:
 A(int i = -16){x = i;}
 virtual A f(A a){return x + a.x;}
 void afisare() {cout << x;} };
class B : public A
{ public:
 B(int i = 3) : A(i){}
 A f(A a) {return x + a.x + 1;} };
int main()
{ A *p1 = new B, *p2 = new A, *p3 = new A (p1 -> f(*p2));
 p3 -> afisare();
 return 0;
}*/

///8
/*
class A
{ public:
 int x;
 A(int i = 0) {x = i;}
 virtual A minus() {cout << x;}};
class B : public A
{ public:
 B (int i = 0) {x = i;}
 void afisare(){cout << x;}};
int main()
{ A *p1 = new A(18);
 *p1 = p1 -> minus();
 dynamic_cast<B*>(p1) -> afisare();
 return 0;}

*/
///9

class A {
public: int x;
 A(int i = 13) {cout<<"a\n"; x = i; }
};
class B: virtual public A {
public:
 B(int i = 15) {cout<<"b\n"; x = i; }
};
class C: virtual public A {
public: C(int i = 17) { cout<<"c\n";x = i; }
};
class D:public A {
public: D(int i = 19) {
 cout<<"d\n";x = i;
}
};
class E : public B, public C, public D {
public: int y;
 E(int i, int j) : D(i), B(j) { cout<<"e\n";
 y = x + i + j;
 }
 E(E &e) { y = -e.y; }
};
int main() {
 E e1(-9,3);//, e2 = e1;
 cout << e1.y;
 return 0;
}

