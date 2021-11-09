/*#include <iostream>
using namespace std;
class pwr {
   double b;
   int e;
   double val;
public:
   pwr(double base, int exp);
   double get_pwr() { return this->val; }
};

pwr::pwr(double base, int exp)
{
   this->b = base;
   this->e = exp;
   this->val = 1;
   if(exp==0) return;
   for( ; exp>0; exp--) this->val = this->val * this->b;
}

int main()
{
     pwr x(4.0, 2), y(2.5, 1), z(5.7, 0);
     cout << x.get_pwr() << " ";
     cout << y.get_pwr() << " ";
     cout << z.get_pwr() << "\n";
     return 0;
}
*/

#include <iostream>
using namespace std;
class cl {
public:
   cl(int i) { val=i; }
   int val;
   int double_val() { return val+val; }
};

int main()
{
   int cl::*data; // data member pointer
   int (cl::*func)(); // function member pointer
   cl ob1(1), ob2(2); // create objects
   data = &cl::val; // get offset of val
   func = &cl::double_val; // get offset of double_val()
   cout << "Here are values: ";
   cout << ob1.*data << " " << ob2.*data << "\n";
   /*cout << "Here they are doubled: ";
   cout << (ob1.*func)() << " ";
   cout << (ob2.*func)() << "\n";*/
   return 0;
}
