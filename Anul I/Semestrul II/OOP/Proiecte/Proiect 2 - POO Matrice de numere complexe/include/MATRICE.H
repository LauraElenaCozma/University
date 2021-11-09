#ifndef MATRICE_H
#define MATRICE_H
#include "Complex.h"
#include <iostream>

using namespace std;

class Matrice
{
protected:

    Complex **v;

public:

    Matrice();
    Matrice(int n,int m);

    virtual ~Matrice() = 0;

    Complex ** getv();

    virtual void citire( istream& ) = 0;
    virtual void afisare( ostream& ) const  = 0;

    friend istream& operator>>(istream &, Matrice & );
    friend ostream& operator<<(ostream &,const Matrice &  );

    virtual int triunghiulara() =0;
    virtual void diagonala() =0;

};



#endif // MATRICE_H
