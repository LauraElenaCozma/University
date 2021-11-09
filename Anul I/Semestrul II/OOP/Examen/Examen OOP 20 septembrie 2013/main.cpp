#include <iostream>
using namespace std;

///neterminat

/*int f(int y)
{ try {if (y>0) throw y;} catch(int i){throw;} return y-2;}
int f(int y, int z)
{ try {if (y<z) throw z-y;} catch(int i){throw;} return y+2;}
float f(float &y)
{ cout<<" y este referinta"; return (float) y/2 ;}
int main()
{ int x;
try
{ cout<<"Da-mi un numar par: ";
cin>>x;
if (x%2) x=f(x, 0);
else x=f(x);
cout<<"Numarul "<<x<<" e bun!"<<endl;
}
catch (int i)
{ cout<<"Numarul "<<i<<" nu e bun!"<<endl;
}
return 0;
}*/

/*
class A
{ int x;
public: A(int i) {x=i; }
int get_x() { return x; }
int& set_x(int i) { x=i;}
A operator=(A a1) { set_x(a1.get_x()); return a1;}
};
class B:public A{
int y;
public: B(int i=0):A(i){y=i;}
void afisare(){cout<< y;}
};
int main()
{ B a(112), b, *c;
cout<<(b=a).get_x();
(c=&a)->afisare();
return 0;
}*/
///3
/*
struct cls
{ int x;
public: int set_x(int i) { int y=x; x=i; return x; }
int get_x(){ return x; } };
int main()
{ cls *p=new cls[100];
int i=0;
for(;i<50;i++) p[i].set_x(i);
for(i=5;i<20;i++) cout<<p[i].get_x()<<" ";
return 0;
}*/
///4
/*
using namespace std;
class A
{ protected: int x;
 public: A(int i=14) { x=i; } };
class B: protected A
{ public: B():A(2){}
 B(B& b) { x=b.x-14; }
void afisare() { cout<<x; } };
int main()
{ /*B b1, b2(b1);
b2.afisare();
A*a=new B;
return 0;
}
*/

///5
/*
class A
{ protected: static int x;
 public: A(int i=0) { x=i; }
 virtual A schimb() { return(7-x); } };
class B: public A
{ public: B(int i=0) { x=i; }
 void afisare() { cout<<x; } };
int A::x=5;
int main()
{A *p1=new B(18);
*p1=p1->schimb();
((B*)(p1))->afisare();
return 0;
}*/

///6
/*
template<class T, class U>
T fun(T x, U y)
{ return x+y;
}
int fun(int x, int y)
{ return x-y;
}
int fun(int x)
{ return x+1;
}
int main()
{ int *a=new int(10), b(5);
 cout<<fun(a,b);
 return 0;
}*/

///7
/*
class B
{ protected: int x;
 public: B(int i=12) { x=i; }
 virtual B f(B ob) { return x+ob.x+1; }
 void afisare(){ cout<<x; } };
class D: public B
{ public: D(int i=-15):B(i-1) {x++;}
 B f(B ob) { return x-2; } };
int main()
{ B *p1=new D, *p2=new B, *p3=new B(p1->f(*p2));
 p3->afisare();
 return 0;
}*/

///8
/*
struct B
{ int i;
 public: B() { i=1; }
 virtual int get_i() { return i; } }a;
class D: virtual public B
{ int j;
 public: D() { j=2; }
 int get_i() {return B::get_i()+j; } };
class D2: virtual public B
{ int j2;
 public: D2() { j2=3; }
 int get_i() {return B::get_i()+j2; } };
class MM: public D2, public D
{ int x;
 public: MM() { x=D::get_i()+D2::get_i(); }
 int get_i() {return x; } };
MM b;
int main()
{ B *o= new MM();
 cout<<o->get_i()<<"\n";
 MM *p= dynamic_cast<MM*>(o);
 if (p) cout<<p->get_i()<<"\n";
 D *p2= dynamic_cast<D*>(o);
 if (p2) cout<<p2->get_i()<<"\n";
 return 0;
}
*/

///9
/*
class A
{ public: int x;
 A(int i=-13) { x=i; } };
class B: virtual public A
{ public: B(int i=-15) { x=i; } };
class C: virtual public A
{ public: C(int i=-17) { x=i; } };
class D: virtual public A
{ public: D(int i=-29) { x=i; } };
class E: public B, public D, public C
{ public: int y;
 E(int i,int j):D(i),B(j){ y=x+i+j; }
 E(E& ob) { y=ob.x-ob.y; }};
int main()
{ E e1(5,10), e2=e1;
cout<<e2.y;
return 0;
}
*/

///10
/*
#include <iostream>
#include <typeinfo>
using namespace std;
class B
{ int i;
 public: B(int x) { i=x+1; }
 int get_i() { return i; }
};
class D: public B
{ int j;
 public: D():B(1) { j=i+2; }
 int get_j() {return j; }
};
int main()
{ B *p=new D[10];
 cout<<p->get_i();
 if (typeid((B*)p).name()=="D*") cout<<((D*)p)->get_j();
 return 0;
}*/

///11
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
}
*/

