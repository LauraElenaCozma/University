#include <iostream>

using namespace std;
///2 --------------- static in functie in clasa
/*
class cls1
{ int x;
public: cls1(){ x=13; }
int g(){ static int i; i++; return (i+x); } };

class cls2
{ int x;
public: cls2(){ x=27; }
cls1& f(){ static cls1 ob; return ob; } };

int main()
{ cls2 ob;
cout<<ob.f().g();
return 0;
}*/

///3
/*
class cls1
{ protected: int x;
public: cls1(int i=10) { x=i; }
int get_x() { return x;} };
class cls2:public  cls1
{ public: cls2(int i):cls1(i) {} };
int main()
{ cls1 d(37);
cout<<d.get_x();
return 0;
}*/


///4
/*class cls
{ int x;
public: cls(int y) {x=y; }

friend int operator*(cls a,cls b){return (a.x*b.x); } };

int main()
{ cls m(100),n(15);
cout<<m*n;
return 0;
}
*/

///5
/*
class B1 { public: int x; };
class B2 { int y; };
class B3 { public: int z; };
class B4 { public: int t; };
class D: private B1, protected B2, public B3, B4
{ int u; };
int main()
{ D d;
cout<<d.u;
cout<<d.x;
cout<<d.y;
cout<<d.z;
cout<<d.t;
return 0;
}*/

///6
/*
class cls
{ int vi;
public: cls(int v=37) { vi=v; }
friend int& f(cls); };
int& f(cls c) { return c.vi; }
int main()
{ const cls d(15);
f(d)=8;
cout<<f(d);
return 0;
}*/


///7
/*class cls1
{ public: int x;
cls1(int i=20) { x=i; } };
class cls2
{ public: int y;
cls2(int i=30) { y=i; }
operator cls1() { cls1 ob; ob.x=y; return ob; } };
cls1 f(cls1 ob)
{ ob.x++;
return ob;
}
int main()
{ cls1 ob1; f(ob1); cout<<ob1.x;
cls2 ob2; f(ob2); cout<<ob2.y;
return 0;
}*/

///8
/*
class cls
{ int x;
public: cls(int i=25) { x=i; }
int f() const; };
int cls::f() const{ return x; }
int main()
{ const cls d(15);
cout<<d.f();
return 0;
}*/

///9
/*class cls
{ public: int x;
cls(int i=0) { x=i; }
~cls(){cout<<"D";}};
cls f(cls c)
{ c.x++;
return c;
}
int main()
{ cls r(10);
cls s=f(r);
return 0;
}*/

///10
template <class tip>
tip dif(tip x, tip y)
{ return x-y;
}
unsigned dif(unsigned x, unsigned y)
{ return x>=y?x-y:y-x;
}
int main()
{ unsigned i=7,j=8;
cout<<dif(i,j);
return 0;
}
