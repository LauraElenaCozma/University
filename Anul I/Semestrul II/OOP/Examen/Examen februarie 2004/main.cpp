#include <iostream>
#include<stdlib.h>
using namespace std;
///1
/*
class matrice{
int a[2][3];
public:
int* operator[](int i) {return a[i];}
};
int main(){
matrice m;
cout<<m[1][1];
//cout<<m.a[1][1];
cout<<m.operator[](1)[1];
return 0;
}*/


///2
/*
class cls{
public:
cls() {cout<<"Constructor";}
};
int main(){
cls *p;
p = new cls;
p = (cls*) malloc (sizeof(cls));
return 0;
}*/


///3
/*
class B1 {public: int x;};
class B2 {public: int y;};
class B3 {public: int z;};
class B4 {public: int t;};
class D: public B1, private B2, protected B3, B4 {public: int u;};
int main(){
D d;

cout<<d.u;
cout<<d.x;
//cout<<d.y;
//cout<<d.z;
//cout<<d.t;
return 0;
}
*/

///4
/*
class D;
class B{
int x;
friend void f(B, D);
public:
B(int i=0) {x=i;}
};
class D: public B {
public:
int y;
D(int i=0, int j=0): B(i) {y=j;}
};
void f(B b, D d) {cout<<b.x<<" "<<d.y;}
int main(){
B b;
D d;
f(b, d);
}
*/

///5
/*
class B{
int x;
public:
B(int i=0) {x=i;}
int get_x() {return x;}
};
class D: public B {
public:
int f() {return get_x();}
};
int main(){
D d;
cout<<d.f();
}
*/

///6
/*
class B
{
int x;
public:
B(int v) {v=x;}
int get_x() {return x;}
};
class D: private B
{
int y;
public:
D(int v): B(v) {}
int get_x() {return x;}
};
void main(){
D d(10);
cout<<d.get_x();
}
*/

///9
/*
class cls{
int vi;
public:
cls(int v=18) {vi=v;}
operator int() {return vi;}
cls operator++() {vi++; return *this;}
cls operator++(int);
};
cls cls::operator++(int)
{
cls aux=*this;
vi++;
return aux;
}
int main(){
cls p(20);
int x=p++, y=++p;
cout<<"x="<<x<<", y="<<y<<endl;
}*/

///10
/*
class cls{
public:
  int vi;
  cls(int v=3) {vi=v;}
};

void f(cls c) {cout<<c.vi;}

int main(){
  const cls d(5);
  f(d);
}
*/

///11
/*
class cls
{
public:
  int x;
  cls() {x=3;}
  void f(const cls &c) const{cout<<c.x;}
};

int main(){
  const cls d;
  d.f(d);
}
*/


///12
/*
class cls
{
public:
  ~cls(){cout<<"Destructor\n";}
};

cls f(cls c) {return c;}

int main()
{
  cls r;
  f(f(r));
}
*/

///15
/*
class vector
{
  int *p, nr;
public:
  operator int() {return nr;}
  vector(int);
};

vector::vector(int n)
{
  p=new int[n];
  nr=n;
  while(n--) p[n]=n;
}

void f(int i)
{
  while(i--) cout<<i<<endl;
}

int main()
{
  vector x(10);
  f(x);
}
*/
///16
/*
class Y;

class Z;

class X{
  int x;
public:
  X(int n=0) {x=n;}
  friend Y;
  friend Z;
};

class Y{
  int y;
  friend Z;
};

class Z{
public:
  void f(X u) {cout<<u.x;}
};

int main(){
  X a;
  Z b;
  b.f(a);
}

*/

///17
class cls2
{
public:
  int vi;
  cls2(int v=20) {vi=v;}
};

class cls1
{
public:
  int vi;
  cls1(int v=30) {vi=v;}
  cls1(cls2 p) {vi=p.vi;}
};



cls1 f(cls1 p)
{
  p.vi++;
  return p;
}

int main(){
  cls1 p; f(p); cout<<endl<<p.vi;
  cls2 r; f(r); cout<<endl<<r.vi;
}

