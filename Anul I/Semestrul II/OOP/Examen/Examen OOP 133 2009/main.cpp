#include <iostream>

using namespace std;

///1
/*
class A
{
    static int x;
    int y;
public:
    A(int i,int j) : y(j) {x=i;}
};

int A::x;
int main()
{
    A g(2,4.0);
    return 0;
}*/

///2
/*
class A
{
    int x;
public:
    A(int i=43) {x=i;}
    int get_x() { return x;}
};

class B
{
    int x;
public:
    B(int i=107) { x=i;}
    operator A();
};
B::operator A() { return x;}



int main()
{
    B b;
    A a=b;
    cout<<a.get_x();
}
*/

///3
/*
class A{
    int	dim;int *v;
public:
    A(int i) {cout<<"c "<<this<<"\n";
        dim=i;
        v=new int[dim];
        for (int i=0; i<dim;i++) v[i]=i;
    }
    A(A& a) {cout<<"copy "<<this<<"\n";
        dim=a.dim;
        v=new int[dim];
        for (int j=0;j<dim;j++) v[j]=a.v[j];}

    ~A()	{cout<<"D "<<this<<"\n";delete[] v;}
    int size() { return dim; }
    int& operator[](int i) { return v[i];}
    A operator+(A al); };

A A::operator+(A a1){
    cout<<"+\n";
A a2(0);
a2.dim=dim; v=new int[a2.dim];
for (int j=0;j<a2.dim;j++) a2.v[j]=v[j]+a1.v[j];
return a2;}

ostream& operator<<(ostream& out, A a){
    out<<a.size();
    for (int i=0; i<a.size(); i++) out<<a[i]<<" ";
    return out;
}
int main(){
A a(10), b(10), c(10);
c=a+b;
cout<<c;
return 0;
}
*/
///6 ----------------atentie. se merge pe functia din derivata numai daca este definita si in clasa si este virtuala. pentru a rezolva se face dynamic cast
/*
class A
{
public:
    int x;
    A(int i=0) { x=i;}
    virtual A minus() {return (1-x);}
};

class B : public A
{
public:
    B(int i=0) {x=i;}
    void afisare() { cout<<x;}
};
int main()
{
    A *p1=new B(18);
    *p1=p1->minus();
    (dynamic_cast<B*>(p1))->afisare();
    return 0;
}*/
///15
/*
template <class T>
T f(T x, T y)
{
    return x+y;
}

int f(int x,int y)
{
    return x-y;
}

int main()
{
    int *a=new int(3),b(23);

    cout<<f(*a,b);
}*/


///133

class A
{
    int x;
public:
    A(int i=0) :x(i) {}
    int get_x() {return x;}
    int& set_x(int i) {x=i;}
    A operator=(A a2)
    {
        set_x(a2.get_x());
        return a2;
    }
};

int main()
{
    A a(212),b;
    cout<<(b=a).get_x();
}
