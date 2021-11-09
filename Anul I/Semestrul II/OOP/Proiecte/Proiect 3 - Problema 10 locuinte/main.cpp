#include <iostream>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("date.in");
class locuinta
{
protected:
    char *nume;
    float suprafata;
    float discount;
    float pret;

public:
    locuinta();
    locuinta(char n[],float s,float d,float p);
    locuinta(const locuinta& ob);

    locuinta& operator=(const locuinta &ob);

    virtual float chirie( ) = 0 ;
    virtual void citire(istream& in) ;
    friend istream& operator>>(istream& in, locuinta & ob);


    virtual void afisare(ostream& out) const;
    friend ostream& operator<<(ostream& out,const locuinta& ob);
};

locuinta::locuinta()
{
    nume=new char[1];
    nume[0]='\0';
    suprafata=0;
    discount=0;
    pret = 0;
}

locuinta::locuinta(char n[],float s,float d,float p) : suprafata(s), discount(d) , pret(p)
{
    nume=new char[strlen(n)+1];
    strcpy(nume,n);
}

locuinta::locuinta(const locuinta &ob)
{
    nume=new char[strlen(ob.nume)+1];
    strcpy(nume,ob.nume);
    suprafata=ob.suprafata;
    discount=ob.discount;
    pret=ob.pret;

}

locuinta& locuinta::operator=(const locuinta &ob)
{
    delete[] nume;
    nume=new char[strlen(ob.nume)+1];
    strcpy(nume,ob.nume);
    suprafata=ob.suprafata;
    discount=ob.discount;
    pret=ob.pret;

    return (*this);
}

void locuinta::citire(istream& in)
{
    char n[100];
    in.get();
    in.getline(n,100) ;
    nume=new char[strlen(n)+1];
    strcpy(nume,n);
    in>>suprafata;
    in>>discount;
    in>>pret;
}

istream& operator>>(istream& in, locuinta & ob)
{
    ob.citire(in);
    return in;
}

void locuinta::afisare(ostream& out) const
{
    out<<"\nNume: "<<nume<<"  Suprafata: "<<suprafata<<"  Discount: "<<discount<<" Pret "<<pret;
}

ostream& operator<<(ostream& out,const locuinta& ob)
{
    ob.afisare(out) ;
    return out;
}


class apartament:public locuinta
{
    int etaj;

public:
    apartament();
    apartament(int et,char n[],float s,float d,float p);
    apartament(const apartament& ob);
    apartament& operator=(const apartament& ob);
    float chirie( );
    void citire(istream& in);
    void afisare(ostream& out) const ;

};

apartament::apartament() : locuinta()
{
    etaj = 0;
}

apartament::apartament(int et,char n[],float s,float d,float p) : locuinta(n,s,d,p)
{
    etaj = et;
}


apartament::apartament(const apartament& ob) : locuinta((locuinta const &)ob)
{
    etaj=ob.etaj;

}

apartament& apartament::operator=(const apartament& ob)
{
    etaj=ob.etaj;

    nume=new char[strlen(ob.nume)+1];
    strcpy(nume,ob.nume);
    suprafata=ob.suprafata;
    discount=ob.discount;

    return (*this);

}

float apartament::chirie( )
{
    if(discount!=0)
        return (float)(suprafata*pret)/(float)discount;
    else return (float)(suprafata*pret);
}


void apartament::citire(istream& in)
{
    locuinta::citire(in);
    in>>etaj;
}

void apartament::afisare(ostream& out) const
{   out<<"Apartament\n";
    locuinta::afisare(out);
    out<<" Etaj: "<<etaj<<'\n';
    out<<'\n';
}
class casa:public locuinta
{
    float dim_curte;
    int nr_etaje;
    float *dim_etaje;
    float pret_curte;

public:

    casa();
    casa(int dim,int ne,float * de,float pc,char n[],float s,float d,float pr);
    casa(const casa& ob);
    float chirie( );
    void citire(istream& in);
    void afisare(ostream& out) const;
};

casa::casa() :locuinta()
{
    dim_curte = 0;
    nr_etaje = 0;
    dim_etaje = NULL;
}

casa::casa(int dim,int ne,float * de,float pc,char n[],float s,float d,float pr) : locuinta(n,s,d,pr)
{
    dim_curte = dim;
    nr_etaje = ne;
    pret_curte=pc;
    dim_etaje = new float[ne+1];
    for(int i=0;i<ne;i++)
        dim_etaje[i]=de[i];
}

casa::casa(const casa& ob) : locuinta((const locuinta&) ob)
{
    pret_curte=ob.pret_curte;
    dim_curte = ob.dim_curte;
    nr_etaje = ob.nr_etaje;
    dim_etaje = new float[ob.nr_etaje+1];

    for(int i=0;i<nr_etaje;i++)
        dim_etaje[i]=ob.dim_etaje[i];
}

float casa::chirie( )
{
    if(discount!=0)
        return (float)(suprafata*pret)/(float)discount+dim_curte*pret_curte;
    else return (float)(suprafata*pret)+dim_curte*pret_curte;
}

void casa::citire(istream& in)
{
    locuinta::citire(in);
    in>>dim_curte;
    in>>nr_etaje;
    dim_etaje=new float[nr_etaje];
    for(int i=0;i<nr_etaje;i++)
        in>>dim_etaje[i];
    in>>pret_curte;
}

void casa::afisare(ostream& out) const
{
    out<<"Casa\n";
    locuinta::afisare(out);
    out<<" Dimensiunea curtii: "<<dim_curte<<" Numarul de etaje: "<<nr_etaje<<"\nDimensiunea fiecarui etaj: ";
    for(int i=0;i<nr_etaje;i++)
        out<<dim_etaje[i]<<' ';
    out<<"Pretul curtii "<<pret_curte<<'\n';
}

template <class T>
class Gestiune;
template <class T>
istream& operator>>(istream& in,Gestiune<T>& ob);
template <class T>
ostream& operator<<(ostream& out,const Gestiune<T> &ob);


template <class T>
class Gestiune
{
    int nrl;
    vector <locuinta *> L;
    vector <float> chirii;

    static int nr_gestiuni;

public:
    Gestiune();
    Gestiune(vector <locuinta*> loc, vector <float> c);
    Gestiune(const Gestiune<T>& ob);

    Gestiune& operator=(const Gestiune<T>& ob);
    void operator+=(T ob);
    friend istream& operator>> < >(istream& in,Gestiune<T>& ob);
    friend ostream& operator<< < >(ostream& out,const Gestiune<T> &ob);
} ;
template <class T>
int Gestiune<T>::nr_gestiuni = 0;
template <class T>
Gestiune<T>::Gestiune()
{
}
template <class T>
Gestiune<T>::Gestiune(vector <locuinta*> loc, vector <float> c)
{
    nrl=0;
    L=loc;
    chirii=c;

}

template <class T>
Gestiune<T>::Gestiune(const Gestiune& ob)
{
    nrl=ob.nrl;
    L=ob.L;
    chirii=ob.chirii;
}

template<class T>
Gestiune<T>& Gestiune<T>::operator=(const Gestiune& ob)
{
    delete[] L;
    delete[] chirii;

    nrl=ob.nrl;
    L=ob.L;
    chirii=ob.chirii;

    return (*this);
}

template <class T>
void Gestiune<T>::operator+=(T ob)
{
    nrl++;
    L.push_back(ob);
    chirii.push_back(ob->chirie());
}
template <class T>
istream& operator>>(istream& in,Gestiune<T> & ob)
{
    in>>ob.nrl;
    ob.L.resize(ob.nrl);
    ob.chirii.resize(ob.nrl);
    for(int i=0;i<ob.nrl;i++)
    {
        char tip;
        in>>tip;
        cout<<tip<<'\n';
        if(tip=='a')ob.L[i]=new apartament;
        else ob.L[i]=new casa;
        in>>*(ob.L[i]);
        ob.chirii[i]=ob.L[i]->chirie();
    }
    return in;

}

template <class T>
ostream& operator<<(ostream& out,const Gestiune<T> &ob)
{
    for(int i=0;i<ob.nrl;i++)
        out<<*(ob.L[i])<<' ';
    out<<"\nIar chiriile lor sunt: ";
    for(int i=0;i<ob.nrl;i++)
        cout<<ob.chirii[i]<<' ';

    cout<<"\n";
    return out;
}
template< >
class Gestiune<char*>;

template < >
istream& operator>>(istream& in, Gestiune<char *>& ob);
template < >
ostream& operator<<(ostream& out,const Gestiune<char *>& ob);


template < >
class Gestiune<char*>
{
    int nrClienti;
    vector <char*> clienti;

public:
   Gestiune()
   {
       nrClienti=0;
   }
   Gestiune(int nr,vector <char*> c)
   {
       nrClienti=nr;
       clienti=c;
   }
   Gestiune(const Gestiune<char *>& ob);
   Gestiune<char *>& operator=(const Gestiune<char *>& ob);
   friend istream& operator>>(istream& in, Gestiune<char *>& ob);
   friend ostream& operator<<(ostream& out,const Gestiune<char *>& ob);

   void operator+=(char* ob);
};
Gestiune<char*>::Gestiune(const Gestiune<char *>& ob)
{
    nrClienti=ob.nrClienti;
    clienti.resize(ob.clienti.size());
    for(int i=0;i<clienti.size();i++)
    {
        clienti[i]=new char[strlen(ob.clienti[i])+1];
        strcpy(clienti[i],ob.clienti[i]);
    }
}

Gestiune<char *>& Gestiune<char *>::operator=(const Gestiune<char *>& ob)
{
    for(int i=0;i<clienti.size();i++)
        delete[] clienti[i];

    nrClienti=ob.nrClienti;
    clienti.resize(ob.clienti.size());
    for(int i=0;i<clienti.size();i++)
    {
        clienti[i]=new char[strlen(ob.clienti[i])+1];
        strcpy(clienti[i],ob.clienti[i]);
    }
    return (*this);
}

istream& operator>>(istream& in, Gestiune<char *>& ob)
{
    in>>ob.nrClienti;
    ob.clienti.resize(ob.nrClienti);
    in.get();
    for(int i=0;i<ob.nrClienti;i++)
    {
        char nume[100];
        in.getline(nume,100);
        ob.clienti[i]=new char[strlen(nume)+1];
        strcpy(ob.clienti[i],nume);
    }
    return in;
}

ostream& operator<<(ostream& out,const Gestiune<char *>& ob)
{
    cout<<"Numarul de clienti este: "<<ob.nrClienti<<'\n';
    for(int i=0;i<ob.nrClienti;i++)
        cout<<ob.clienti[i]<<'\n';
    cout<<'\n';
    return out;
}

void Gestiune<char*>::operator+=(char* ob)
{
    nrClienti++;
    clienti.push_back(ob);
}
int main()
{

    Gestiune<locuinta*> G;
    fin>>G;
    cout<<G<<'\n';
    locuinta * loc;
    char tip;
    fin>>tip;
    if(tip=='c')loc=new casa;
    else loc=new apartament;
    fin>>(*loc);
    G+=loc;
    cout<<'\n'<<G<<'\n';


   /* Gestiune <char *> gest;
    fin>>gest;
    cout<<gest<<'\n';
    char s[100];
    fin.getline(s,100);
    char * aux;
    aux=new char[strlen(s)+1];
    strcpy(aux,s);
    gest+=s;
    cout<<gest;
    return 0;*/
}


/*
3
c
Pristavu Diana
500
2
50
1000
3
10 12 24
100
a
Cozma
300
10
40
3
c
Dauer
1000
3
70
300
2
125 326
100
a
Laura
250
10
40
2

*/
