#include <iostream>

using namespace std;
///1
/*
class cls
{
    int i;
public:
    cls(int i=0): i(i) {}
    int f(cls b)
    {
        b.i=i;
        return i;
    }
};

int main()
{
    cls a(8) , b(-5) , x[10];

    for(int i=0;i<10;i++)x[i]=10-i;
    cout<<x[3].f(a)<<' '<<x[4].f(b)<<' '<<a.f(a);
}*/

///3
/*
int f(int x)
{
    class A
    {
    public:
        int i;
    }o;
    return o.i-5+x;
}

int main()
{
    cout<<f(1);
    return 0;

}
*/

///5
/*
class A
{
    static int * const x;
    public: A(){}
            int get_x() { return (*x)++;}

};
int * const A::x(new int(1000));

int main()
{
    A *a=new A,b;
    cout<<b.get_x();
    cout<<a->get_x();
    return 0;
}*/

///7

/*
class A
{
    int x;
public:
    A(int y=0) : x(y) {}
    A operator+(A* o)
    {
        A r(*this);
        r.x=r.x+o->x;
        return r;
    }
    friend ostream& operator<<(ostream& o,A a);
};

ostream& operator<<(ostream& o,A a)
{
    o<<a.x;
    return o;
}

int main()
{
    A o1(2);
    cout<<(o1+&o1);
    return 0;
}*/
///8
/*
class A
{
    int x;
public:
    A(const int &i) : x(i) {}
    int get_x() { return x;}
    A operator+(int &);

};
A A::operator+(int &i)
    {
        A t(i);
        return t;
    }
ostream& operator<<(ostream& o,A a)
{
    o<<a.get_x();
    return o;
}

int main()
{
    A a=5;
    int b=55,c=7;
    cout<<a+b<<' '<<a+c;
    return 0;
}*/
///9
/*
class cls
{
    int i;
    public: cls() {cout<<1;}
};

class cls2 : public cls
{
    public:cls2(){ cout<<2;};
};

class cls3 : public cls
{
    public: cls3() { cout<<3;};
};

class cls4: public cls3,public cls2
{
    public: cls4() { cout<<4;};
};

int main()
{
    cls4 ob;
}*/
///10
/*
class A
{
    int i;
public:
    A(int x=5):i(x) {}
    virtual int f(A a)
    {
        return i+a.i;
    }
};

class B: public A
{
    int j;
public:
    B(int x=-3): j(x) {}
    int f(B b)
    {
        return j+b.j;

    }
};

int main()
{
    int i;
    cin>>i;
    A *o;
    if(i%3) o=new A(i);
    else o=new B(i);

    cout<<o->f(*o);

}
*/

/*
class A
{
public:
    void eat(){cout<<"A";}
};

class B: virtual public A
{
public:
    void eat(){cout<<"B";}
};

class C: virtual public A
{
public:
    void eat(){cout<<"C";}
};

class D:public B,C
{
    void eat() {cout<<"D";}
};

int main()
{
    C *ob=new D;
    ob->eat();
}
*/

///13
/*
class X
{
    int i;
public:
    X(int j=5) {i=j; cout<<i<<' ';}
    const int afisare(int j) const
    {
        cout<<i<<' '; return i+j;
    }

};

int main()
{
    const X O(7) , &O2=O , *p=&O2;
    cout<<p->afisare(3);
}*/
///15

/*
class A
{
    public:
    int i;
public:
    A(int x=5) : i(x) {}
    virtual int f(A a)
    {
        return i+a.i;
    }
};

class B: public A
{int j;
public:
    B(int x=-3): j(x){}
    int f(A b) { return j+b.i;}
};

int main()
{
    int i;
    cin>>i;
    A *o;
    if(i%3)o=new A(i);
    else o=new B(i);
    cout<<o->f(*o);
    return 0;
}*/

///18
class A
{
    static int x;
    const int y;
public:
    A(int i) : y(-i+7) { x=i;}
    int put_x(A a)
    {
        return x+a.y;
    }

};

int A::x=13;
int main()
{
    A a(10);
    cout<<a.put_x(18);
}
