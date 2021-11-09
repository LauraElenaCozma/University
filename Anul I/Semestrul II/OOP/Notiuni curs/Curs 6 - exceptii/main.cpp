
/*exemplul 1
// A simple exception handling example.
#include <iostream>
using namespace std;

int main()
{
   cout << "Start\n";
   try { // start a try block
       cout << "Inside try block\n";
       throw 100; // throw an error
       cout << "This will not execute";
   }
   catch (int i) { // catch an error
      cout << "Caught an exception -- value is: ";
      cout << i << "\n";
   }
   cout << "End";
   return 0;
}

*/

/* Throwing an exception from a function outside the
try block.*/
/*#include <iostream>
using namespace std;
void Xtest(int test)
{  cout << "Inside Xtest, test is: " << test << "\n";
   if(test) throw test;}

int main()
{  cout << "Start\n";
   try { // start a try block
      cout << "Inside try block\n";
      Xtest(0);
      Xtest(0);
      Xtest(2);
   }
   catch (int i) { // catch an error
      cout << "Caught an exception -- value is: ";
      cout << i << "\n";
    }
   cout << "End";
   return 0;
}*/

// Catching derived classes.
/*#include <iostream>
using namespace std;

class B {};

class D: public B {};

int main()
{
   D derived;
   try {
      throw derived;
   }
   catch(B b) {
      cout << "Caught a base class.\n";
   }
   catch(D d) {
      cout << "This won't execute.\n";
   }
   return 0;
}*/


// This example catches all exceptions.
/*#include <iostream>
using namespace std;
void Xhandler(int test)  throw(char)
{   try{
      if(test==0) throw test; // throw int
      if(test==1) throw 'a'; // throw char
      if(test==2) throw 123.23; // throw double
    }
   catch(...) { // catch all exceptions
      cout << "Caught One!"<<test<<'\n';
    }
}
int main()
{   cout << "Start\n";
    Xhandler(0);
    Xhandler(1);
    Xhandler(2);
    cout << "End";
    return 0;
}

*/
/*
#include <iostream>

using namespace std;
float f(int y)
{
    try{
        if(y%2)throw y/2;
       }5
    catch(int i)
    {
        if(i%2)throw ;
        cout<<" Numarul "<<i<<" nu e bun!"<<endl;
    }
    return y/2;


}


int main()
{
    int x;
    try
    {
        cout<<"da-mi un nr intreg: ";
        cin>>x;
        if(x)f(x);
        cout<<"Numarul "<<x<<" nu e bun\n";

    }
    catch(int i)
    {
        cout<<"Numarul "<<i<<" e bun\n";
    }
    return 0;
}*/
/*
#include <iostream>
using namespace std;
int f(int y)
{ if (y<0) throw y; return y/2;}
int f(int y, int z)
{ if (y<z) throw z-y; return y/2;}
float f(int &y)
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
}
*/


/*
#include <iostream>
using namespace std;
int f(int y)
{
 if (y < 0) throw y;
 return y/2;
}
int main()
{
 int x;
 try
 { cout<<"Da-mi un numar par: ";
 cin>>x;
 if (x%2) x = f(x);
 cout<<"Numarul "<<x<<" e bun!"<<endl;
 }
 catch (int i)
 { cout<<"Numarul "<<i<<" e bun!"<<endl;
 }
 return 0;
}*/

/*#include <iostream>
using namespace std;
int f(float y)
{
 if (y < 0) throw y;
 return y/2;
}
int main()
{
 int x;
 try
 { cout<<"Da-mi un numar par: ";
 cin>>x;
 if (x%2) x = f(x);
 else throw x;
 cout<<"Numarul "<<x<<" e bun!"<<endl;
 }
 catch (int i)
 { cout<<"Numarul "<<i<<" e bun!"<<endl;
 }
 return 0;
}*/

/*#include <iostream>
using namespace std;
int f(int y, int z)
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
 } return 0; }
*/
/*
#include <iostream>
using namespace std;
int f(int y)
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
#include <iostream>
using namespace std;
float f(float f)
{ if (f) throw f;
 return f/2;
}
int main()
{ int x;
 try
 {
 cout<<"Da-mi un numar intreg: ";
 cin>>x;
 if (x) f(x);
 else throw x;
 cout<<"Numarul "<<x<<" e bun!"<<endl;
 }
 catch (int i)
 { cout<<"Numarul "<<i<<" nu e bun!"<<endl;
 }
 return 0;
}*/


