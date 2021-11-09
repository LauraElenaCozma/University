#include <iostream>

using namespace std;
///1
/*
class B
{ int i;
  public: B() { i=50; }
          virtual int get_i() { return i; }
};
class D: public B
{ int j;
  public: D() { j=47; }
          int get_j() {return j; }
};
int main()
{ D *p=new B;
  cout<<p->get_i();
  cout<<((D*)p)->get_j();
  return 0;
}*/

///2
/*
template<class X>
int functie(X x, X y)
{ return x+y;
}
int functie(int x, int *y)
{ return x-*y;
}
int main()
{ int a=27, *b=new int(45);
  cout<<functie(a,b);
  return 0;
}*/

///3
/*
class A
{   protected: static int x;
    private: int y;
    public: A(int i) { x=i; y=-i+3; }
        int put_x(A a) { return x+a.y; } };
int A::x=5;
int main()
{   A a(10);
    cout<<a.put_x(70);
    return 0;
}*/

///4
/*
class A
{ int i;
  public: A(int x=3):i(x) {}
  virtual int get_i() { return i; }};
class B: public A
{ int j;
  public: B(int x=10):j(x) {}
  virtual int get_j() {return A::get_i()+j; }};
int main()
{ A o1(5);
  B o2;
  cout<<o1.get_i();
  cout<<o2.get_j();
  cout<<o2.get_i();
  return 0;
}*/

///5
/*
class B
{ protected: int i;
  public: B(int j=5) {cout << " cb "; i=j-2; }
          ~B(){ cout << " db ";}
          int get_i() { return i; } };

class D1: public B
{ protected:int j;
  public: D1(int k=10) {cout << " cd1 "; j=i-k+3; }
          ~D1(){ cout << " dd1 ";} };

 class D2: public D1
{ int k;
  public: D2(int l=15) {cout << " cd2 "; k=i+j-l+3; }
           ~D2(){ cout << " dd2 ";}  };
D1 f(D1 d1, D2 d2) {return d1.get_i()+d2.get_i(); }

int main()
{ D2 ob2; D1 ob1(3);
  cout<<f(ob1,ob2).get_i()+ob2.get_i();
  return 0;
}*/

///6
/*
class B
{    protected: int x;
     public: B(int i=3) { x=i; }
             virtual B f(B ob) { return x+ob.x; }
             void afisare(){ cout<<x; } };
class D: public B
{	public: D(int j=4): B(j+2) {int i=j;}
        D f(D ob) { return x+1; } };
int main()
{ B *p1=new D, *p2=new B, *p3=new B(p1->f(*p2));
 	  p3->afisare();
  return 0;
}*/

///7
/*class cls
{	int x;
public: cls(int i) { x=i; }
int set_x(int i) { int y=x; x=i; return y; }
int get_x(){ return x; } };
int main()
{ cls *p=new cls[10];
      for(int i=3;i<9;i++) p[i].set_x(i);
	  for(int i=0;i<4;i++) cout<<p[i].get_x();
return 0;
}*/

///8
/*
struct X {   int i;
public:   X(int ii ) { i = ii; };
     int f1() const { return i; }
X f2() const {   int i=this->f1(); return X(74-i); }};
const X f3() {   return X(8); }
int f4(const X& x) { return x.f1(); }
int main() { X ob(19);
    cout<<f4(ob.f2());
    return 0; }
*/

///9
/*
class A
{   protected: int x;
    public: A(int i):x(i){}
            int get_x(){ return x; } };
class B: private A
{   protected: int y;
    public: B(int i,int j):y(i),A(j){}
            int get_y(){ return get_x()+y; } };
class C: private B
{   protected: int z;
    public: C(int i,int j,int k):z(i),B(j,k){}
            int get_z(){ return get_x()+get_y()+z; } };
int main()
{   C c(1,2,3);
    cout<<c.get_z();
    return 0;
}*/

///10
/*
class A
{   static int *x;
    public: A() {}
            int get_x() { return (++(*x))++; } };
int *A::x(new int(10));
int main()
{   A *p=new A,b;
    cout<<b.get_x()<<" ";
    cout<<p->get_x();
    return 0;
}
*/

///11
/*
class X {   int i;
public:   X(int ii = 5) { i = ii; cout<< i<< " ";};
          const int tipareste(int j) { cout<<i<< " "; return i+j; }; };
int main()
{ X O (7);
  O.tipareste(5);
  X &O2=O;
  O2.tipareste(6);
  const X* p=&O;
  cout<<p->tipareste(7);
  return 0;
}*/












