#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;
ifstream fin("date.in");

///INCOMPLET> NU INTELEG ENUNTUL
struct data
{
    int luna,an;
};

int nr_luni(data d1,data d2)
{
    int n=abs(d1.an-d2.an)*12;
    if(d1.luna<d2.luna)n+=abs(d1.luna-d2.luna);
    else n-=abs(d1.luna-d2.luna);
    return n;
}


class proprietate
{
protected:

    string adresa;
    float suprafata;
    float chirie;
public:
    virtual void citire(istream& in)
    {

        in>>adresa;
        in>>suprafata>>chirie;
    }

    virtual void afisare(ostream& out) const
    {
        out<<"\nAdresa "<<adresa<<" suprafata "<<suprafata<<" chirie "<<chirie;
    }
    friend istream& operator>>(istream& in, proprietate& ob);
    friend ostream& operator<<(ostream& out, const proprietate& ob);
};

istream& operator>>(istream& in, proprietate& ob)
{
    ob.citire(in);
    return in;
}

ostream& operator<<(ostream& out, const proprietate& ob)
{
    ob.afisare(out);
    return out;
}

class casa: public proprietate
{
    int nr_niv;
    float s_curte;

public:
    void citire(istream& in)
    {
        proprietate::citire(in);
        in>>nr_niv>>s_curte;
    }
    void afisare(ostream& fout) const
    {
        proprietate::afisare(fout);
        fout<<" Nr niveluri "<<nr_niv<<" suprafata curte "<<s_curte<<'\n';
    }
};

class apartament: public proprietate
{
    int etaj;
    int nr_camere;
public:
    void citire(istream& in)
    {
        proprietate::citire(in);
        in>>etaj>>nr_camere;
    }
    void afisare(ostream& fout) const
    {
        proprietate::afisare(fout);
        fout<<"Etaj "<<etaj<<" Nr camere "<<nr_camere<<'\n';
    }
};

class contract
{
protected:
    string nume;
    float discount;

public:
    contract()
    {
        nume=new char[1];
        nume[0]='\0';
    }
    contract(string s)
    {
        nume = s;

    }

    virtual void citire(istream& in)
    {
        in>>nume;
    }
    friend istream& operator>>(istream& in, contract & ob);

    virtual void afisare(ostream& out) const
    {
        cout<<"Numele este "<<nume<<" discountul este "<<discount<<' ';
    }

    friend ostream& operator<<(ostream& out, const contract& ob);

};

istream& operator>>(istream& in, contract & ob)
{
    ob.citire(in);
    return in;
}

ostream& operator<<(ostream& out, const contract& ob)
{
    ob.afisare(out);
    return out;
}


class inchiriere: public contract
{

    data sf;
    data inc;
public:
    inchiriere()
    {
        sf.luna=0;
        sf.an=0;
        inc.luna=0;
        inc.an=0;
        discount=0;
    }
    inchiriere(string s,data d1,data d2)
    {
        inc=d1;
        sf=d2;
        int n=nr_luni(d1,d2);
        if(n/12.0>=2)discount=0.1;
        else if(n/12.0>=1)discount=0.05;
        else discount=0;
    }
    void set_discount()
    {
        int n=nr_luni(inc,sf);
        if(n/12.0>=2)discount=0.1;
        else if(n/12.0>=1)discount=0.05;
        else discount=0;
    }
    void citire(istream& in)
    {
        contract::citire(in);
        in>>inc.luna>>inc.an>>sf.luna>>sf.an;
        set_discount();
    }

    void afisare(ostream& out) const
    {
        contract::afisare(out);
        cout<<"Data incepere contract "<<inc.luna<<"."<<inc.an<<" data incheierii contractului "<<sf.luna<<'.'<<sf.an<<'\n';
    }

};

class vanzare: public contract
{
    data tranzactie;
    data integral;
public:
    vanzare()
    {
        tranzactie.luna=0;
        tranzactie.an=0;
        integral.luna=0;
        integral.an=0;
        discount=0;
    }
    vanzare(string s,data d1,data d2)  :contract(s)
    {
        tranzactie=d1;
        integral=d2;
        int nr=nr_luni(d1,d2);
        if(d1.an==d2.an && d1.luna==d2.luna)discount=0.1;
        else if(nr<=60)discount=0.07;
        else if(nr<=120)discount=0.05;
        else discount=0;
    }
    void set_discount()
    {
        int nr=nr_luni(tranzactie,integral);
        if(tranzactie.an==integral.an && tranzactie.luna==integral.luna)discount=0.1;
        else if(nr<=60)discount=0.07;
        else if(nr<=120)discount=0.05;
        else discount=0;
    }
    void citire(istream& in)
    {
        contract::citire(in);
        set_discount();
        in>>tranzactie.luna>>tranzactie.an>>integral.luna>>integral.an;
    }
    void afisare(ostream& out) const
    {
        contract::afisare(out);
        cout<<"Data tranzactiei "<<tranzactie.luna<<"."<<tranzactie.an<<" data platire integrala "<<integral.luna<<'.'<<integral.an<<'\n';
    }
};

int main()
{
    proprietate **P;
    contract ** C;

    int n,m;
    fin>>n;
    P=new proprietate *[n];
    for(int i=0;i<n;i++)
    {
        if(i%2==0)P[i]=new casa;
        else P[i]=new apartament;
        fin>>*(P[i]);
        cout<<*(P[i])<<' ';
    }

    fin>>m;
    C=new contract*[m];
    for(int i=0;i<m;i++)
    {
        if(i%2==0)C[i]=new inchiriere;
        else C[i]=new vanzare;
        fin>>*(C[i]);
        cout<<*(C[i])<<'\n';
    }
    return 0;
}
