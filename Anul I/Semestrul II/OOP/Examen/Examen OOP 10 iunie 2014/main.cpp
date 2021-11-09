#include <iostream>
#include <typeinfo>
using namespace std;
/*
class A
{
    int i;
protected:
    static int x;
public:
    A(int j=7) {i=j; x=j;}
    int get_x() { return x;}
    int set_x(int j){int y=x;x=j; return y;}
    A operator=(A a1) { set_x(a1.get_x()); return a1;}

};

int A::x=15;
int main()
{
    A a(212) ,b;
    cout<<(b=a).get_x();
    return 0;
}


/*
template <class X,class Y>
X f(X x, Y y)
{
    return x+y;
}

int * f(int * x,int y)
{
    return x-y;
}

int main()
{
    int * a=new int(200), *b=a;
    cout<<*f(a,b);
}*/
/*
template <class X>
void test(X &a,X &b)
{
    cout<<"TTest";
}

void test(int &a,int &b)
{
    cout<<"Test 1";
}

void test(int e,int f)
{
    cout<<"Test 2";
}

void test(int q,int *h)
{
    cout<<"Test 3";
}


int main()
{
    int a=5,b=15,c=25,*d=&a;
    test(a,b);
    test(c,d);
    return 0;
}*/

/*
class A
{
    int valoare;
public:
    A(int param1=3) : valoare(param1) {}
    int getValoare() { return this->valoare;}
};
int main()
{
    A vector[]={ *(new A(3)), *(new A(4)),*(new A(5)),*(new A(6))};
    cout<<vector[2].getValoare();
    return 0;
}

*/
///8
/*
int f(int y)
{
    if(y<0) throw y;
    return y/2;
}

int main()
{
    int x;
    try
    {
        cout<<"Da mi un nr par";
        cin>>x;
        if(x%3)x=f(x);
        else throw x;
        cout<<"Numarul "<<x<<" e bun!\n";
    }
    catch(int i)
    {
        cout<<"Numarul "<<x<<" nu e bun!\n";
    }
    return 0;
}*/
///9
/*
class A
{
public:
    virtual int get_i() { return 1;}
};

class B : public A
{
    int get_i() { return 2;}
};

int main()
{
    const int i=cin.get();
    if(i%3) { A o;}
    else { B o;}
    cout<<o.get_i();
}*/
///10
/*
class cls
{
    int x;
public:
    cls(int i=0) {cout<<"c1 "; x=i;}
    ~cls(){cout<<"d1 ";}
};


class cls1
{
    int x;
    cls xx;
public:
    cls1(int i =0)
    {
        cout<<"C2 "; x=i;
    }

    ~cls1()
    {
        cout<<"d2 ";
    }
}c;

class cls2
{
    int x;
    cls1 xx;
    cls xxx;
public:
    cls2(int i=0) { cout<<"c3 ";x=i;}
    ~cls2() { cout<<"d3 ";}
};

int main()
{
    cls2 s;
    return 0;
}*/
///11
/*
class B
{
    int i;
public:
    B() {i=1;}
    int get_i() { return i;}
};

class D : public B
{
    int j;
public:
    D() { j=2;}
    int get_j(){return j;}
};

int main()
{
    D*p=new D;
    cout<<p->get_i()<<' ';
    if(typeid((D*)p).name()=="D*") cout<<((D*)p)->get_j();
    return 0;
}*/
///!!!! trebuie adaugat const int& pt ca atunci cand se face atribuirea campul x e constant


class cls
{
    int x;
public:
    cls(int i=3){x=i;}
   int& f() const {return x;}
};

int main()
{
    const cls a;
    int b=a.f();
    cout<<b;
    return 0;
}
///14

/*
class B
{
    protected: int x;
    public:
        B(int i=0) {x=i;}
        virtual B minus() { return (1-x);}

};

class D : public B
{
public:
    D(int i=0) : B(i) {}
    void afisare(){cout<<x;}
};


int main()
{
    D *p1=new D(18);
    *p1=p1->minus();  //nu e supraincarcat op = unul e de tip B si unul D
    p1->afisare();
    return 0;
}*/

///16
/*
class B
{
    protected: int x;
    public:
        B(int i=14) {x=i;}

};

class D : B
{
public:
    D(B ob)  {x=ob.x;}
    void afisare(){cout<<x;}
};


int main()
{
    B ob1;
    D ob2(ob1);
    ob2.afisare();
    return 0;
}*/
///18
/*
class B
{
    protected: int x;
    public:
        B(int i=105) {x=i;}
        virtual int get_x() =0;

};

class D : public B
{
public:
    D(int i) : B(i) {}
    D operator+(const D& a){return x+a.x;}
};


int main()
{
    D ob1(17), ob2(12);
    cout<<(ob1+ob2).get_x();
    return 0;
}*/

