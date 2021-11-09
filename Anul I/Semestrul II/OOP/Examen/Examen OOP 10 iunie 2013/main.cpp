#include <iostream>
#include <typeinfo>

using namespace std;


///Exercitiul 1
/*class A
{ static int x; int y;
public: A(int i) { x=i; y=-i; }
static int put_x(int i=x) { x=i; return x; }
};
int A::x=5;
int main()
{ A a(7);
cout<<A::put_x();
return 0; }
*/

///exercitiul 2
/*int f(int y, int z)
{ cout<<" y nu este referinta "; if (y<z) throw z-y; return y/2;}
int f(int &y)
{ cout<<" y este referinta "; return y/2 ;}
int main()
{ int x;
try
{ cout<<"Da-mi un numar par: ";
cin>>x;
if (x%2) x=f(x, 0);
else x=f(x);
cout<<"Numarul "<<x<<" e bun!"<<endl; }
catch (int i)
{ cout<<"Numarul "<<i<<" nu e bun!"<<endl;
} return 0; }*/
//Exercitiul 4
/*class X
{int i;
public:
X() { i = 0; }
void set(int ii) { i = ii; cout<< "__"<<ii+2;}
int read() const { return i; }
int permute() { return i = i * 47; } };
class Y : public X
{
int i;
X j;
public:
Y() { i = 0; j.set(2); }
int change() {
    i = permute();
    j.permute();
    cout << j.read();
    return i; }

 void set(int ii)
 { i = ii;
j.set(ii+1);
X::set(ii); } };

int main()
{
Y D;
D.change();
cout<<'\n';
D.read();

D.permute();

D.set(12);
cout<<'\n';

return 0;
}*/


//Ex 6
/*class X
{	int i;
public:	X(int ii = 5) { i = ii; cout<< i;};
void afisare(int j) const { cout<<i;};   ///!!!trb fct const
 }o;
int main()
{
     X O (7);
     X &O2=o;
     O2.afisare(5);
    const X* p=&O;
    p->afisare(3);
    return 0;
}*/
//Ex 7

/*
class clsB
{ int x;
public: clsB(int i=0) {cout << "CO "; x=i; }
~clsB(){ cout << "DO ";} };

class cls :public clsB
{
    int x;
    clsB Y;
public:
    cls(int i=0) {cout << "Cl "; x=i; }
    ~cls(){ cout << "D1 ";}
} p;
class clss : virtual public clsB
{ int x;
cls xx;
public: clss(int i=0) {cout << "C2 "; x=i; }
~clss(){ cout << "D2 ";}
};
class clss2{
int x;
clss xx;
cls xxx;
public: clss2(int i=0) {cout << "C3 "; x=i; }
~clss2(){ cout << "D3 ";}
};


clss o;

int main()
{clss2 s;
return 0;
}*/

//Ex 9
/*template<class T, class U>
T f(T x, U y)
{ return x+y; }
int f(int x, int y)
{return x-y; }
int main()
{
int *a=new int(4), b(16);
cout<<*f(a,b);
return 0; }
*/

//Ex 10
/*#include <iostream>
using namespace std;
template <class X> void swapt(X &a, X &b)
{	X temp;
temp = a;
a = b;
b = temp; }

template <class X, class Y>
void swapt(X &a, Y &b, Y c)
{	Y temp;
temp = b; b = c;
c = temp; }

void swapt(int &a, int b, int c=0)
{ int temp; temp = a+2;
a = b-1;
b = temp; }
 int main()
{ int i=13,j=15; swapt(i,j); cout<< i<<j; swapt(i,j,12); cout<< i<<j; return 0; }
*/

///ex 11
/*
class CL
{
    static int x;
public: CL(int i=3) {x=i; }
    int get_x() { return x; }
    int& set_x(int i) { x=i;return x;}
    CL operator=(CL al) { set_x(al.get_x()); return al;}
} a(19);
int CL::x;
int main()
{ CL b;
cout<<(b=a).get_x();
return 0;
}*/


///ex 12
/*class B
{ int i;
public: B() { i=1; }
int get_i() { return i; } };
class D: B
{ int j;
public: D() { j=2; }
int get_j() {return j; } };
int main()
{ B *p=new D;
cout<<p->get_i();
if (typeid((B*)p).name()=="D*") cout<<((D*)p)->get_j();
return 0; }*/
/*
struct X { int i;
public: X(int ii = 0) { i = ii; cout<< i;};
void afisare(){cout<<i++;}; } o;
 X apel(int j) { return X(j); }
void apel2(X& x) {
x.afisare(); }
int main()
{ apel2(apel(2)=X(5));
return 0; }
*/

/*template <class T>
T multiply(T v1,T v2){ return v1*v2;}

int main()
{
    int x=multiply<int>(10,11.3);
    return 0;
}
*/
/*
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
int main()
{ C c(1,2,3);
cout<<c.get_x()+c.get_y()+c.get_z();
return 0; }
*/
