#include "Matrice.h"
#include <iostream>

using namespace std;

Matrice::Matrice()
{
    v=NULL;
}

Matrice::Matrice(int n,int m)
{
    //pointerul dublu din Matrice va avea dimensiunle n si m dupa apelarea constrctorului
    v=new Complex*[n];

    for(int i=0;i<n;i++)
        v[i]=new Complex[m];
}

Matrice::~Matrice()
{

}


Complex ** Matrice::getv()
{
    return v;
}



istream& operator>>(istream &fin, Matrice & ob)
{
    //se citeste un obiect de tip matrice, functia citire urmand sa citeasca tipul specific, oarecare sau patratica
    ob.citire(fin);
    return fin;
}

ostream& operator<<(ostream& fout,const Matrice & ob)  //Atentie la const
{

    ob.afisare(fout);
    return fout;
}
