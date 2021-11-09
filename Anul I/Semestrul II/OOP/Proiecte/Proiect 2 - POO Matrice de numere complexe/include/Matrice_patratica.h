#ifndef MATRICE_PATRATICA_H
#define MATRICE_PATRATICA_H
#include "Matrice.h"

class Matrice_patratica: public Matrice
{
    int dim;

public:

    Matrice_patratica();
    Matrice_patratica(int n);
    Matrice_patratica(const Matrice_patratica &ob) ;

    ~Matrice_patratica();

    Matrice_patratica& operator=(const Matrice_patratica &ob);

    void elimin(int ,Matrice_patratica& )const ;
    Complex determinant() const;

    int triunghiulara();
    void diagonala();

    void citire(istream&);
    void afisare( ostream& ) const;


};





#endif // MATRICE_PATRATICA_H
