#include "Matrice_oarecare.h"
#include "Matrice.h"

Matrice_oarecare::Matrice_oarecare():Matrice()
{
    lin=0;
    col=0;
}

Matrice_oarecare::Matrice_oarecare(int n,int m):Matrice(n,m)
{
    lin=n;
    col=m;
}

Matrice_oarecare::Matrice_oarecare(const Matrice_oarecare& ob) : Matrice(ob.lin,ob.col)
{
    lin=ob.lin;
    col=ob.col;
    for(int i=0;i<lin;i++)
    {
        for(int j=0;j<col;j++)
            v[i][j]=ob.v[i][j];
    }
}


Matrice_oarecare::~Matrice_oarecare()
{
    if(v!=NULL)
    {
        for(int i=0;i<lin;i++)
        delete[] v[i];

        delete[] v;
        v=NULL;
    }
    lin=col=0;
}


int Matrice_oarecare::triunghiulara()
{
    return 0; //matricile oarecare nu pot fi triunghiulare
}

void Matrice_oarecare::diagonala()
{
    cout<<"E o matrice oarecare, nu putem stabili daca e triunghiulara sau diagonala\n";
}


Matrice_oarecare& Matrice_oarecare::operator=(const Matrice_oarecare& ob)
{
    //supraincarcarea operatorului =
    if(this==&ob)return *this;

    if(v!=NULL)
    {
        for(int i=0;i<lin;i++)
        delete[] v[i];

        delete[] v;
        v=NULL;
    }

    lin=ob.lin;
    col=ob.col;
    v=new Complex*[lin];
    for(int i=0;i<lin;i++)
        v[i]=new Complex[col];

    for(int i=0;i<lin;i++)
    {
        for(int j=0;j<col;j++)
            v[i][j]=ob.v[i][j];
    }

    return (*this);

}

void Matrice_oarecare::citire( istream& fin)
{
    if(v!=NULL)
    {
        for(int i=0;i<lin;i++)
        delete[] v[i];

        delete[] v;
        v=NULL;
    }
    lin=col=0;
    //citirea unui element de tip matrice oarecare
    fin>>lin>>col;

    v=new Complex*[lin];
    for(int i=0;i<lin;i++)
        v[i]=new Complex[col];


    for(int i=0;i<lin;i++)
        for(int j=0;j<col;j++)
            fin>>v[i][j];

}

void Matrice_oarecare::afisare( ostream& fout) const
{
    //afisarea unui element de tip matrice oarecare
    for(int i=0;i<lin;i++)
    {
        for(int j=0;j<col;j++)
            fout<<v[i][j];

        fout<<'\n';
    }
}
