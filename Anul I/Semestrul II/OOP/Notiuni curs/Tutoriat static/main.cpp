#include <iostream>
#include <cstring>
using namespace std;
/*class cls1 {
  int x;
public:
  cls1 () {
    x = 13;
  }
  int g() {
      cout<<"in g";
    static int i; i++;
    return (i+x);
  }
   ~cls1() { cout<<"destructor\n";}
};

class cls2 {
  int x;
public:
  cls2() {
    x = 27;
  }
  cls1& f() {
     cls1 ob; return ob;
  }
};

int main() {
  cls2 ob;
  cout << ob.f().g();
  return 0;
}*/

///2
/*
class Point {
private:
int x;
int y;
public:
Point(int i = 0, int j = 0); // Normal Constructor
Point(const Point &t); // Copy Constructor
};
Point::Point(int i, int j) {
x = i;
y = j;
cout << "Normal Constructor called\n";
}
Point::Point(const Point &t) {
y = t.y;
cout << "Copy Constructor called\n";
}
int main()
{
Point *t1, *t2;
t1 = new Point(10, 15);
t2 = new Point(*t1);
Point t3 = *t1;
Point t4;
t4 = t3;
return 0;
}*/

///3
/*
int &fun() {
static int a = 10;
return a;
}
int main() {
int &y = fun();
y = y +30;
cout<<fun();
return 0;
}*/

///4
/*
class Test {
int value;
public:
Test (int v = 0) {value = v;}
int getValue () const { return value; }
};
int main() {
const Test t;
cout << t.getValue();
return 0;
}*/

///5
/*
class X {
private:
static const int a ;
public:
    X() {}
static int getA() { return a; }
};
int main() {
cout <<X::getA()<<endl;

return 0;
}*/

///6
/*
class Test
{
private:
static int count;
public:
 Test& fun();
};
int Test::count = 0;
Test& Test::fun()
{
Test::count++;
cout<<Test::count<<" ";
return *this;
}
int main()
{
Test t;
t.fun().fun().fun().fun();
return 0;
}*/
///7
/*
class String
{
char *p;
int len;
public:
String(const char *a);
};
String::String(const char *a)
{
int length = strlen(a);

p = new char[length +1];
strcpy(p, a);
cout << "Constructor Called " << endl;
}
int main()
{
String s1("Geeks");
const char *name = "forGeeks";
s1 = name;
return 0;
}*/

///8
/*
class Point
{
private:
int x;
int y;
public:
    Point(int x=0,int y=0) : x(x) , y(y) {}
Point(const Point&p) { x = p.x; y = p.y; }
void setX(int i) {x = i;}
void setY(int j) {y = j;}
int getX() {return x;}
int getY() {return y;}
void print() { cout << "x = " << getX() << ", y = " << getY(); }
};

int main()
{
Point p1;
p1.setX(10);
p1.setY(20);
Point p2 = p1;
p2.print();
return 0;
}*/

///9
/*
class Test
{
private:
int x;
static int count;
public:
Test(int i = 0) : x(i) {}

Test(const Test& rhs) : x(rhs.x) { ++count; }
static int getCount() { return count; }
};
int Test::count = 0;
Test fun()
{
return Test();
}
int main()
{
Test a = fun();
cout<< Test::getCount();
return 0;
}*/

///10
/*
class A
{
// data members of A
public:
A () { cout << "\n A's constructor"; /* Initialize data
members  }
A (const A &a) { cout << "\n A's Copy constructor"; /* copy data
members }
A& operator= (const A &a) // Assignemt Operator
{
// Handle self-assignment:
if(this == &a) return *this;
// Copy data members
cout << "\n A's Assignment Operator"; return *this;
}
};
class B
{
A a;
// Other members of B
public:
B(A &a) { this->a = a; cout << "\n B's constructor"; }
};
int main()
{
A a1;
B b(a1);
return 0;
}
*/
///11
/*
class A
{
int id;
static int count;
public:
A()
{
count++;
id = count;
cout << "constructor called " << id << endl;
}
~A()
{
cout << "destructor called " << id << endl;
}
};
int A::count = 0;
int main()
{
A a[2];
return 0;
}*/

///12
/*
class A
{
int aid;
public:
A(int x=0)
{ aid = x; }
void print()
{ cout << "A::aid = " <<aid; }
};
class B
{
int bid;
public:
static A a;
B (int i) { bid = i; }
};
A B::a;
int main()
{
B b(10);
b.a.print();

return 0;
}*/

///13
/*
class Test
{
int value;
public:
Test(int v = 0) { value = v; }
int getValue()  const { return value; }
};
int main()
{
const Test t;
cout << t.getValue();
return 0;
}*/

///14
/*
class A
{
public:
A& operator=(const A&a)
{
cout << "A's assignment operator called" << endl;
return *this;
}
};
class B
{
A a[2];
};
int main()
{
B b1, b2;
b1 = b2;

return 0;
}*/

///15
/*
class A {
private:
const int x = 5;
public:
A(): x(2) {
}
int getX() const {
return x;
}
};

int main() {
auto obj = new A();
cout << obj->getX();
return 0;}*/


///16
/*
class A {
private:
int x = 5;
public:
A(): x(2) {
x = 6;
}
const int getX() const {
return x;
}
};

int main() {
auto obj = new A();
cout << obj->getX();
return 0;
}*/

///17
/*
class Test
{
public:
    int x = 0;
Test(Test &) { }
Test() { }
~Test() { cout<<"DEST";}
};
Test& fun()
{
cout << "fun() Called\n";
Test t;
return t;
}
int main()
{
Test t1;
Test t2 = fun();
cout<<t2.x;
return 0;
}*/

///18
/*
int a = 2;
class Test {
 int &t = a;
public:
Test(int &t):t(t) {}
int getT() { return t; }
};
int main() {
int x = 20;
Test t1(x);
cout<<t1.getT()<<endl;
x = 30;

cout<<t1.getT()<<endl;
return 0;
}
*/

///19
/*
class Test
{
static int x;
public:
Test() { x++; }
static int getX() {return x;}
};
int Test::x = 0;
int main()
{
cout << Test::getX() << " ";
Test t[5];
cout << Test::getX();
}*/

///20
/*
class Test
{
private:
static int count;
public:
Test& fun();
};
int Test::count = 0;
Test& Test::fun()
{

Test::count++;
cout << Test::count << " ";
return *this;
}
int main()
{
Test t;
t.fun().fun().fun().fun();
return 0;
}
*/


///21
/*
class Cls {
int x;
public:
Cls(int i): x(i) { }
int& f() {
return x;
}
};
int main() {
Cls a(14);
int b = a.f()++;
cout << b << '\n';
return 0;
}*/

///22
/*
class Cls {
int x;
public:
Cls(int i = 1) {
x = i;
}
int setX(int i) {
int y = x;

x = i;
return y;
}
int getX() {
return x;
}
};
int main() {
Cls *p = new Cls[10];
int i = 0;
for (; i < 10; ++i)
p[i].setX(i);
for (i = 0; i < 10; i++)
cout << p[i].getX();
return 0;
}
*/

///23
/*
class A {

int x, *y;
public:
A(int i) { x = i; y = new int[x]; }
A(const A &a) { x = a.x; y = new int[x]; }
int getX() const {
return x;
}
};
int f(A a) {
return a.getX();
}
int main() {
const A a(5);
cout << (a.getX() == f(a));
return 0;
}*/

///24
/*
class Cls {
int x;
public:
int setX(int i) { int y = x; x = i; return x; }
int getX() { return x; }
};
int main() {
Cls *p = new Cls[100];
int i = 0;
for (; i < 50; i++)
p[i].setX(i);
for (i = 5; i < 20; ++i) {
cout << p[i].getX() << " ";
}
return 0;
}*/

///25

class Cls {
int x;
public:
Cls(int i = 0) {
cout << 1;
x = i;
}
Cls(const Cls &ob) {
cout << 2;
x = ob.x;
}
int getX() const {
return x;
}
};
const Cls &f(Cls &c) {
return c;
}
int main() {
Cls r;
Cls s = f(f(f(r)));
cout << s.getX();
return 0;

}


///26
/*
class Cls {
static int i;
int j;
public:
Cls(int x = 7) {
j = x;
}
static int imp(int k) {
Cls a;
return i + k + a.j;
}
int getJ() const {
return j;
}
};
int Cls::i;
int main() {
int k = 5;
cout << Cls::imp(k);
return 0;
}*/
