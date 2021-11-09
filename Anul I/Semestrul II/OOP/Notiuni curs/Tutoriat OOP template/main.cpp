#include <iostream>

using namespace std;
/*
template <long i>
int fun()
{
//i =20;
}
int main() {
fun<4>();
return 0;
}
*/

///2
/*
template <typename T>
void fun(const T&x)
{
static int count = 0;
cout << "x = " << x << " count = " << count << endl;
++count;
return;
}
int main()
{
fun<int> (1);
cout << endl;
fun<int>(1);
cout << endl;
fun<double>(1.1);
cout << endl;
return 0;
}*/
///3
/*
template <typename T>
T maxi(T x, T y)
{
    static int s=0;
    cout<<s;
    s++;
return (x > y)? x : y;
}
int main()
{
cout << maxi(3, 7) << std::endl;
cout << maxi(3.0, 7.0) << std::endl;
cout << maxi(3, 7.0) << std::endl;
return 0;
}*/

///4
/*
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
}
*/

///5
/*
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


///6
/*
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
}*/

///7
/*
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

/*
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
/*
class A
{ int x;
  public: A(int i=0) { x=i; }
          A operator+(const A& a) { return x+a.x; }
          int get()
          {
              return x;
          }
         template <class T> ostream& operator<<(ostream&o)
         { o<<x; return o; }
       };

    /*   template <class T>
       ostream & operator<<(ostream &o, A x)
       {
           o<<x.get();
           return o;
       }
    */
   /* ostream & operator<<(ostream &o, A x)
       {
           o<<x.get();
           return o;
       }

int main()
{ A a1(33), a2(-21);
   (a1+a2).operator<<<A>(cout); //! in clasa cu template
   // (a1+a2) << cout             //! in clasa, no template

   //  operator<< <A> (cout,(a1+a2)); //! in afara clasei, template

 //   operator<<(cout,a1+a2); //! in afara clasei, no template
  //  cout<< a1+a2;           //! in afara clasei, no template


  return 0;
}*/
class A
{
public:
    A(int i=0){cout<<"A";}
    A(const A&ob){cout<<"copy";}
};
int main()
{
    A a=3;
}

