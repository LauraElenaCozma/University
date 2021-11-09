#include "Matrice_patratica.h"

Matrice_patratica::Matrice_patratica() : Matrice()
{
    dim=0;
}

Matrice_patratica::Matrice_patratica(int n) : Matrice(n,n)
{
    dim=n;
}

Matrice_patratica::Matrice_patratica(const Matrice_patratica &ob) : Matrice(ob.dim,ob.dim)
{
    dim=ob.dim;

    for(int i=0;i<dim;i++)
    {
        for(int j=0;j<dim;j++)
            v[i][j]=ob.v[i][j];
    }

}

Matrice_patratica::~Matrice_patratica()
{
    if(v!=NULL)
    {
        for(int i=0;i<dim;i++)
        delete[] v[i];

        delete[] v;
        v=NULL;
    }
    dim=0;
}


Matrice_patratica& Matrice_patratica::operator=(const Matrice_patratica &ob)
{
    if(this==&ob)return (*this);

    if(v!=NULL)
    {
        for(int i=0;i<dim;i++)
        delete[] v[i];

        delete[] v;
        v=NULL;
    }

    dim=ob.dim;
    v=new Complex*[dim];
    for(int i=0;i<dim;i++)
        v[i]=new Complex[dim];
    for(int i=0;i<dim;i++)
    {
        for(int j=0;j<dim;j++)
            v[i][j]=ob.v[i][j];
    }
    return (*this);
}


int Matrice_patratica::triunghiulara()
{
    Complex z;
    int oksup=1,okinf=1;
    for(int i=0;i<dim && oksup;i++)
        for(int j=i+1;j<dim && oksup;j++)
            if(v[i][j]!=z)oksup=0;

    for(int i=0;i<dim && okinf;i++)
        for(int j=0;j<i && okinf;j++)
           if(v[i][j]!=z)okinf=0;
    return oksup+okinf;  //daca returneaza 0, intreamna ca nu e nici triunghiulara superior, nici inferior. daca returneaza 1 intreamna ca e ori superior, ori inferior. 2 inseamna ca e diagonala
}

void Matrice_patratica::diagonala()
{
    int val=triunghiulara();
    if(val==2)cout<<"E diagonala\n";
    else if(val==1) cout<<"Nu e diagonala, dar e triunghiulara\n";
         else cout<<"Nu e diagonala si nici triunghiulara\n";
}


void Matrice_patratica::elimin(int k,Matrice_patratica& a) const
{
    //cout<<"-----"<<(*this)<<'\n'; nu merge, deoarece functia de afisare contine determinant in ea si intra in recursie

    a.dim=dim-1;
    a.v=new Complex *[dim-1];
    for(int i=0;i<dim-1;i++)
        a.v[i]=new Complex[dim-1];
    for(int i=1;i<dim;i++)       //fac o matrice fara linia 0 si coloana k
        for(int j=0;j<dim;j++)
            if(j<k)a.v[i-1][j]=v[i][j];
            else if(j>k)a.v[i-1][j-1]=v[i][j];


}

Complex Matrice_patratica::determinant() const
{

       if(dim==1)return v[0][0];     //am ajuns la un determinant de 1*1
       else
       {
           Complex suma(0,0);
           Matrice_patratica b;
           for(int i=0;i<dim;i++)    //dezvoltam dupa prima linie
           {
               elimin(i,b);
               Complex d=b.determinant();
               if(i%2==1)suma=suma+v[0][i]*d;
               else suma=suma-v[0][i]*d;
           }
           return suma;
       }
}


void Matrice_patratica::citire( istream& fin)
{
    //dezaloc inainte de citire
    if(v!=NULL)
    {
        for(int i=0;i<dim;i++)
        delete[] v[i];

        delete[] v;
        v=NULL;
        dim=0;
    }

    //afiseaza un obiect de tip matrice patratica
    fin>>dim;
    v=new Complex *[dim];

    for(int i=0;i<dim;i++)
    {
        v[i]=new Complex[dim];
        for(int j=0;j<dim;j++)
            fin>>v[i][j];

    }

}

void Matrice_patratica::afisare( ostream& fout) const
{
    for(int i=0;i<dim;i++)
    {
        for(int j=0;j<dim;j++)
            fout<<v[i][j];
        fout<<'\n';
    }
    fout<<"Determinant: "<<determinant();  //functia de afisare contine si determinantul
}
