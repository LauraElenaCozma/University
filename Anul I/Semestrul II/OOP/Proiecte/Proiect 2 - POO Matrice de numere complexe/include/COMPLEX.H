#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

using namespace std;

class Complex
{
    float re,im;

public:
    Complex();
    Complex(float a,float b);
    Complex(const Complex& ob);

    friend istream& operator>>(istream& fin, Complex& ob);
    friend ostream& operator<<(ostream& fout, const Complex& ob);

    float get_re();
    float get_im();
    void set_re(float val);
    void set_im(float val);

    Complex operator+(const Complex& );
    Complex operator-(const Complex& );
    Complex operator*(const Complex& );
    Complex& operator=(const Complex& );
    bool operator !=(const Complex& );

};





#endif // COMPLEX_H
