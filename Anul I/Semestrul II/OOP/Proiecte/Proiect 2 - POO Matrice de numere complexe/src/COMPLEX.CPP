#include "Complex.h"

//constructorii
Complex::Complex()
{
    re=0;
    im=0;
}

Complex::Complex(float a,float b): re(a),im(b)
{
}

Complex::Complex(const Complex& ob)   //am facut constructor de copiere, desi era potrivit si cel implicit, dar asa scria in cerinta
{
    re=ob.re;
    im=ob.im;
}


float Complex::get_re()
{
    return re;
}

float Complex::get_im()
{
    return im;
}

void Complex::set_re(float val)
{
    re=val;
}

void Complex::set_im(float val)
{
    im=val;
}



//supraincarcarea operatorilor
Complex Complex::operator+(const Complex& ob)
{
    //suma a doua numere complexe
    Complex S;
    S.re=re+ob.re;
    S.im=im+ob.im;

    return S;
}

Complex Complex::operator-(const Complex& ob)
{
    //diferenta a doua numere complexe
    Complex S;
    S.re=re-ob.re;
    S.im=im-ob.im;

    return S;
}

Complex Complex::operator*(const Complex& ob)
{
    //inmultirea a doua numere complexe
    Complex P;
    P.re=re*ob.re-im*ob.im;
    P.im=re*ob.im+im*ob.re;

    return P;
}

bool Complex::operator !=(const Complex& ob)
{
    //verifica daca doua numere complexe sunt diferite
    if(ob.re==re && im==ob.im)
        return false;
    return true;
}

Complex& Complex::operator=(const Complex& ob)
{
    //suma a doua numere complexe
    if(this==&ob) return (*this);
    re=ob.re;
    im=ob.im;
    return (*this);
}



istream& operator>>(istream& fin, Complex& ob)
{
    //citirea unui obiect de tip complex
    fin>>ob.re>>ob.im;
    return fin;
}

ostream& operator<<(ostream& fout, const Complex& ob)
{
    if(ob.re!=0)
    {
        if(ob.im==0)cout<<ob.re<<" ";
        else if(ob.im>0)cout<<ob.re<<"+"<<ob.im<<"i ";
        else cout<<ob.re<<ob.im<<"i ";
    }
    else
    {
        if(ob.im==0)cout<<"0 ";
        else cout<<ob.im<<"i ";
    }

     return fout;
}
