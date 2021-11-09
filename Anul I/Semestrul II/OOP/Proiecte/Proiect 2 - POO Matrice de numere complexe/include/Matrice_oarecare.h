#ifndef MATRICE_OARECARE_H
#define MATRICE_OARECARE_H
#include "Matrice.h"

class Matrice_oarecare: public Matrice
{
    int lin,col;

public:
    Matrice_oarecare();
    Matrice_oarecare(int n,int m);
    Matrice_oarecare(const Matrice_oarecare& ob);

    ~Matrice_oarecare();

    int triunghiulara();
    void diagonala();

    Matrice_oarecare& operator=(const Matrice_oarecare& ob);


    void citire( istream& );
    void afisare( ostream& ) const ;



};




#endif // MATRICE_OARECARE_H
