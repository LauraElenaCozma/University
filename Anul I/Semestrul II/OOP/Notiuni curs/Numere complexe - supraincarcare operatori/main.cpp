#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("date.in");
class Complex
{
    private:
        double im,re;
    public:
        Complex operator+ (Complex C);
        void set_values(double vre,double vim)
        {
            im=vim;
            re=vre;
        }

        void print_number();
        friend ostream& operator<<(ostream& f,const Complex C);

        friend istream& operator>>(istream& f, Complex &C);

        void multiply(int x);


};

Complex Complex::operator+(Complex C)
{
    Complex S;
    S.re=re+C.re;
    S.im=im+C.im;

    return S;
}

void Complex::print_number()
{
    cout<<re<<' '<<im<<'\n';
}

ostream& operator<<(ostream& f,const Complex C)
{
    f<<C.re<<' '<<C.im<<'\n';
}


istream& operator>>(istream& f,Complex &C)
{
    f>>C.re>>C.im;
}


void Complex::multiply(int x)
{
    re*=x;
    im*=x;

}
int main()
{
    Complex A,B,C;
//    A.set_values(2,-5);
//    B.set_values(4,2);
    fin>>A>>B;
//    A.print_number();
//    B.print_number();
    cout<<A;

    A.multiply(3);
    //C.print_number();
    cout<<A;
    return 0;
}
