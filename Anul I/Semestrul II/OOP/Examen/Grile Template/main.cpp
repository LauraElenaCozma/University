///  Exercitiul 1
/*
#include <iostream>

using namespace std;

template <class S, class T> class Pair
{
private:
    S x;
    T y;
};

template <class S> class Element
{
private:
    S x;
};

int main()
{
    Pair <Element <int>, Element <char> > p;
    return 0;
}*/


/// Exercitiul 2
/*
#include <iostream>

using namespace std;

template <int N>
class A
{
    int arr[N];
public:
    virtual void fun(){cout<<"A::fun()";}
};

class B: public A<2>{
public:
    void fun(){cout<<"B::fun()";}
};

class C: public B{};

int main()
{
    A <2> *a = new C;
    a->fun();
    return 0;
}
*/

///Exercitiul 3
/*
#include <iostream>

using namespace std;

template <int i>

int fun()
{
    //i=20;
}

int main()
{
    fun<4>();
    return 0;
}
*/

/// Exercitiul 4
/*#include <iostream>

using namespace std;

template <typename T>

void fun(const T& x)
{
    static int count =0;

    cout<<"x = "<<x<<" count = "<<count<<endl;

    count ++;
    return ;
}

int main()
{
    fun<int>(1);
    cout<<endl;
    fun<int>(1);
    cout<<endl;
    fun<double>(1.1);
    cout<<endl;
    return 0;
}*/


///Exercitiul 5

/*#include <iostream>

using namespace std;

template <typename T>
T maxi(T x,T y)
{
    return (x> y)? x : y;
}

int main()
{
    cout<<maxi(3,7)<<endl;
    cout<<maxi(3.0,7.0)<<endl;
    cout<<maxi<int>(3,7.0)<<endl; //  --- rezolvare: convertim 7.0 la int sau puntem explicit maxi<int>
    return 0;

}*/


///Exercitiul 6

/*#include <iostream>
using namespace std;
template <class T>
class Test
{
private:
    T val;
public:
    static int count;
    Test() { count++; }
};
template<class T>
int Test<T>::count = 0;

int main()
{
    Test<int> a;
    Test<int> b;
    Test<double> c;
    cout << Test<int>::count << endl;
    cout << Test<double>::count << endl;
    return 0;
}*/


///Exercitiul 7
/*#include<iostream>
#include<stdlib.h>
using namespace std;
template<class T, class U>
class A {
T x;
U y;
static int count;
};
int main() {
A<char, char> a;
A<int, int> b;
cout << sizeof(a) << endl;
cout << sizeof(b) << endl;
return 0;
}*/


///Exercitiul 8
/*#include<iostream>
#include<stdlib.h>
using namespace std;
template<class T, class U, class V=double>
class A {
    T x;
    U y;
    V z;
    static int count;
};
int main()
{
    A<int, int> a;
    A<double, double> b;
    cout << sizeof(a) << endl;
    cout << sizeof(b) << endl;
    return 0;
}*/


///Exercitiul 9
/*#include <iostream>
using namespace std;
template <class T, int max>
int arrMin(T arr[], int n)
{
int m = max;
for (int i = 0; i < n; i++)
if (arr[i] < m)
m = arr[i];
return m;
}
int main()
{
int arr1[] = {10, 20, 15, 12};
int n1 = sizeof(arr1)/sizeof(arr1[0]);
char arr2[] = {1, 2, 3};
int n2 = sizeof(arr2)/sizeof(arr2[0]);
cout << arrMin<int, 10000>(arr1, n1) << endl;
cout << arrMin<char, 256>(arr2, n2);
return 0;
}
*/

///Exercitiul 10
/*#include <iostream>
using namespace std;
template <int i>
void fun()
{
i = 20;
cout << i;
}
int main()
{
fun<10>();
return 0;
}*/

/// Exercitiul 11
/*#include <iostream>
using namespace std;
template <class T>
T max (T &a, T &b)
{
return (a > b)? a : b;
}
template <>
int max <int> (int &a, int &b)
{
cout << "Called ";
return (a > b)? a : b;
}
int main ()
{
int a = 10, b = 20;
cout << max <int> (a, b);
}*/

///Exercitiul 12
/*#include <iostream>
using namespace std;
template<int n> struct funStruct
{
static const int val = 2*funStruct<n-1>::val;
};
template<> struct funStruct<0>
{
static const int val = 1 ;
};
int main()
{
cout << funStruct<10>::val << endl;
return 0;
}*/

#include <iostream>
using namespace std;

template <class T>
void f(T a, T b)
{
    cout<<"temp 1 par\n";
}
template<>
void f(float a,float b)
{
    cout<<"temp 0 par\n";
}
/*
void f(float a,float b)
{
    cout<<"non-template\n";
}*/


int main()
{
f<float >(9.0,8.8);
return 0;
}



