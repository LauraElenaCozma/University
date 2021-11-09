#include <iostream>

using namespace std;

class produs
{
protected:
    string nume;
    string unitate;

public:
    produs(string nume1="",string unit="") : nume(nume1), unitate(unit) {}
    virtual void citire(istream& in)
    {
        getline(in,nume);
        in>>unitate;
    }

    virtual void afisare(ostream& out) const
    {
        out<<nume<<' '<<unitate<<' ';
    }
    friend istream& operator>>(istream& in,produs& ob)
    {
        ob.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out,const produs& ob)
    {
        ob.afisare(out);
        return out;
    }
};

class perisabil: virtual public produs
{
protected:
    int perioada_val;

public:
    perisabil(string nume1="",string unit="",int per=0) : produs(nume1,unit) , perioada_val(per) {}
    void citire(istream& in)
    {
        produs::citire(in);
        in>>perioada_val;
    }
    void afisare(ostream& out)
    {
        produs::afisare(out);
        out<<perioada_val<<' ';
    }

};


class promotie: virtual public produs
{
protected:
    int discount;

public:
    promotie(string nume1="",string unit="",int disc=0) : produs(nume1,unit) , discount(disc) {}
    void citire(istream& in)
    {
        produs::citire(in);
        in>>discount;
    }
    void afisare(ostream& out)
    {
        produs::afisare(out);
        out<<discount<<' ';
    }

};

class perisabil_la_promotie : public perisabil, public promotie
{
public:
    perisabil_la_promotie(string nume1="",string unit="",int per=0 , int disc=0) :perisabil(nume1,unit,per) , promotie(nume1,unit,disc) {}

    void citire(istream& in)
    {
        produs::citire(in);
        in>>perioada_val>>discount;
    }
    void afisare(ostream& out)
    {
        produs::afisare(out);
        out<<perioada_val<<' '<<discount<<' ';
    }
};

class lot
{
    produs * p;
    int zi,luna,an;
    int cantitate;

public:
    lot(produs * p1,int z,int l,int a,int cant) : zi(z), luna(l) ,an(a) ,cantitate(cant)
    {

    }

};

int main()
{
    perisabil_la_promotie p;
    return 0;
}
