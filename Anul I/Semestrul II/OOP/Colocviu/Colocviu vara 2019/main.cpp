//Cozma Laura-Elena, grupa 144  CNU GCC Compiler
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;
ifstream fin("date.in");

class bilet
{
protected:

    static int nr_bilet;
    string serie;
    string cod_tren;
    string plecare;
    string sosire;
    int zi,luna,an;
    string ora;
    int durata;
    int distanta;
    float pret;


public:
    float get_pret()
    {
        return pret;
    }

    string get_cod_tren()
    {
        return cod_tren;
    }
    string get_serie()
    {
        return serie;
    }
    virtual void creare_serie() = 0;
    virtual void creare_pret_bilet() = 0;
    bilet(string cod_tren1="",string plecare1="", string sosire1="",int z=0,int l=0,int a=0,string o="",int dur=0,int dist=0)
    {
        nr_bilet++;
        cod_tren=cod_tren1;
        plecare=plecare1;
        sosire=sosire1;
        zi=z;
        luna=l;
        an=a;
        ora=o;
        durata=dur;
        distanta=dist;

    }
    //am folosit constructorii care erau dati de compilator

    virtual void citire(istream& in)
    {
        in>>cod_tren>>plecare>>sosire>>zi>>luna>>an>>ora>>durata>>distanta;
    }

    virtual void afisare(ostream& out) const
    {
        out<<serie<<' '<<plecare<<' '<<sosire<<" data: "<<zi<<'.'<<luna<<'.'<<an<<" "<<"Ora: "<<ora<<" Durata: "<<durata<<" Distanta: "<<distanta<<" Pret:"<<pret;

    }

    friend istream& operator>>(istream& in, bilet& ob)
    {
        ob.citire(in);
        return in;
    }

    friend ostream& operator<<(ostream& out, const bilet& ob)
    {
        ob.afisare(out);
        return out;
    }

    int get_distanta()
    {
        return distanta;
    }
    virtual ~bilet() {}
};

int bilet::nr_bilet=0;


class bilet_IR : public bilet
{
public:

    void creare_pret_bilet()
    {
        pret=0.7*distanta;
    }
    virtual void creare_serie() = 0;
    bilet_IR(string cod_tren1="",string plecare1="", string sosire1="",int z=0,int l=0,int a=0,string o="",int dur=0,int dist=0) : bilet(cod_tren1,plecare1,sosire1,z,l,a,o,dur,dist)
    {
    }

    virtual void citire(istream& in)
    {
        bilet::citire(in);
    }

    virtual void afisare(ostream& out) const
    {
        bilet::afisare(out);

    }

};
class bilet_IR_I : public bilet_IR
{
public:
    void creare_serie()
    {
        string nr;
        ostringstream temp;
        temp<<nr_bilet;
        nr=temp.str();

        serie="IRI-"+nr;
    }
    void creare_pret_bilet()
    {
        bilet_IR::creare_pret_bilet();
        pret=(120/100.0)*pret; //taxa de comfort
    }
    bilet_IR_I(string cod_tren1="",string plecare1="", string sosire1="",int z=0,int l=0,int a=0,string o="",int dur=0,int dist=0) : bilet_IR(cod_tren1,plecare1,sosire1,z,l,a,o,dur,dist)
    {
        creare_serie();
        creare_pret_bilet();
    }
    string get_serie()
    {
        return serie;
    }

    void citire(istream& in)
    {
        bilet::citire(in);
        creare_pret_bilet();
    }

    void afisare(ostream& out)
    {
        bilet::afisare(out);
    }
};

class bilet_IR_II : public bilet_IR
{
public:
    void creare_pret_bilet()
    {
        bilet_IR::creare_pret_bilet();
    }
    void creare_serie()
    {
        string nr;
        ostringstream temp;
        temp<<nr_bilet;
        nr=temp.str();

        serie="IRII-"+nr;
    }
    bilet_IR_II(string cod_tren1="",string plecare1="", string sosire1="",int z=0,int l=0,int a=0,string o="",int dur=0,int dist=0) : bilet_IR(cod_tren1,plecare1,sosire1,z,l,a,o,dur,dist)
    {
        creare_serie();
        creare_pret_bilet();
    }
    string get_serie()
    {
        return serie;
    }

    void citire(istream& in)
    {
        bilet::citire(in);
        creare_pret_bilet();

    }

    void afisare(ostream& out)
    {
        bilet::afisare(out);
    }
};


class bilet_R : public bilet
{
public:

    void creare_pret_bilet()
    {
        pret=0.35*distanta;
    }
    virtual void creare_serie() = 0;
    bilet_R(string cod_tren1="",string plecare1="", string sosire1="",int z=0,int l=0,int a=0,string o="",int dur=0,int dist=0) : bilet(cod_tren1,plecare1,sosire1,z,l,a,o,dur,dist)
    {
    }

    virtual void citire(istream& in)
    {
        bilet::citire(in);
    }

    virtual void afisare(ostream& out) const
    {
        bilet::afisare(out);

    }
};

class bilet_R_I : public bilet_R
{
public:
    void creare_pret_bilet()
    {
        bilet_R::creare_pret_bilet();
        pret=(120/100.0)*pret;
    }
    void creare_serie()
    {
        string nr;
        ostringstream temp;
        temp<<nr_bilet;
        nr=temp.str();

        serie="RI-"+nr;
    }
    bilet_R_I(string cod_tren1="",string plecare1="", string sosire1="",int z=0,int l=0,int a=0,string o="",int dur=0,int dist=0) : bilet_R(cod_tren1,plecare1,sosire1,z,l,a,o,dur,dist)
    {
        creare_serie();
        creare_pret_bilet();
    }
    string get_serie()
    {
        return serie;
    }

    void citire(istream& in)
    {
        bilet::citire(in);
        creare_pret_bilet();
    }

    void afisare(ostream& out)
    {
        bilet::afisare(out);
    }
};

class bilet_R_II : public bilet_R
{
public:
    void creare_pret_bilet()
    {
        bilet_R::creare_pret_bilet();
    }
    void creare_serie()
    {
        string nr;
        ostringstream temp;
        temp<<nr_bilet;
        nr=temp.str();

        serie="RII-"+nr;
    }
    bilet_R_II(string cod_tren1="",string plecare1="", string sosire1="",int z=0,int l=0,int a=0,string o="",int dur=0,int dist=0) : bilet_R(cod_tren1,plecare1,sosire1,z,l,a,o,dur,dist)
    {
        creare_serie();
        creare_pret_bilet();
    }
    string get_serie()
    {
        return serie;
    }

    void citire(istream& in)
    {
        bilet::citire(in);
        creare_pret_bilet();
    }

    void afisare(ostream& out)
    {
        bilet::afisare(out);
    }
};

void citire_bilete(vector <bilet*> &B,int &nr_b)
{
    fin>>nr_b;
    B.resize(nr_b);
    string tip;
    for(int i=0;i<nr_b;i++)
    {
        fin>>tip;
        if(tip=="IR_I") B[i]=new bilet_IR_I;
        else if(tip=="IR_II")B[i]=new bilet_IR_II;
             else if(tip=="R_I")B[i]=new bilet_R_I;
                  else if(tip=="R_II")B[i]=new bilet_R_II;

        fin>>*(B[i]);
    }
}

/*
void afisare_bilete(vector <bilet*> B,int nr_b)
{
    cout<<"\n__________________________________\nAfiseaza biletele:\n\n";
    for(int i=0;i<nr_b;i++)
    {
        cout<<*(B[i])<<'\n';
    }
}
*/
void afisare_bilete(vector <bilet*> B,int nr_b)
{
    //am afisat biletele si dupa categorie
    cout<<"\n__________________________________\nAfiseaza biletele:\n\n";
    cout<<"Inter-regio clasa I:\n\n";
    vector <bilet_IR_II> IR_II;
    vector <bilet_R_I> R_I;
    vector <bilet_R_II> R_II;
    for(int i=0;i<nr_b;i++)
    {
        bilet_IR_I * iri=dynamic_cast <bilet_IR_I *>(B[i]);

        if(iri!=NULL)
        {
            cout<<*(B[i])<<'\n';

        }
        else
        {
            bilet_IR_II *irii=dynamic_cast <bilet_IR_II *>(B[i]);
            if(irii!=NULL)
                IR_II.push_back(*irii);
            else
            {
                bilet_R_I *ri=dynamic_cast <bilet_R_I *>(B[i]);
                if(ri!=NULL)
                  R_I.push_back(*ri);
                else {bilet_R_II * rii=dynamic_cast <bilet_R_II *> (B[i]); R_II.push_back(*rii);}
            }
        }

    }
    cout<<"\nInter-regio clasa II:\n\n";
    for(unsigned int i=0;i<IR_II.size();i++)
        cout<<IR_II[i]<<'\n';
    cout<<"\nRegio clasa I:\n\n";
    for(unsigned int i=0;i<R_I.size();i++)
        cout<<R_I[i]<<'\n';
    cout<<"\nRegio clasa II:\n\n";
    for(unsigned int i=0;i<R_II.size();i++)
        cout<<R_II[i]<<'\n';
}

void afisare_bilete_dupa_distanta(vector <bilet*> B,int nr_b,int distanta)
{
    cout<<"\n__________________________________\nAfiseaza biletele dupa distanta:\n\n";
    for(int i=0;i<nr_b;i++)
        if(B[i]->get_distanta()>distanta)
    {
        cout<<*(B[i])<<'\n';
    }
}



void eliberare_bilet(bilet * bil,vector <bilet*> &B,int &nr_b)
{
    string tip;
    fin>>tip;
    if(tip=="IR_I") bil=new bilet_IR_I;
        else if(tip=="IR_II")bil=new bilet_IR_II;
             else if(tip=="R_I")bil=new bilet_R_I;
                  else if(tip=="R_II")bil=new bilet_R_II;

    fin>>*bil;
    B.push_back(bil);
    nr_b++;

}
void afisare_bilete_dupa_cod_tren(vector <bilet*> B,int nr_b,string cod_tren)
{
    cout<<"\n__________________________________\nAfiseaza biletele dupa codul trenului:\n\n";
    for(int i=0;i<nr_b;i++)
        if(B[i]->get_cod_tren()==cod_tren)
    {
        cout<<*(B[i])<<'\n';
    }
}

void anulare_bilet(vector <bilet*> &B,int &nr_b,string serie)
{
    cout<<"\n__________________________________\nAnulare bilet:\n\n";
    vector<bilet*>::iterator i;
    int nr=0,ok=0;
    for(i=B.begin();i!=B.end() && !ok;i++,nr++)
    {
        if(B[nr]->get_serie()==serie) {ok=1; }
    }

    if(ok)
    {
        if((i-1)==B.end()) B.pop_back();
        else B.erase(i-1,i);

        nr_b--;}
}



int main()
{
    bilet_R_II b("R","Roman","Bucuresti",23,5,2019,"13",5,300);
    cout<<b;
    vector <bilet *> B;
    int nr_b;


    bilet * bil;
    //am citit biletele
    citire_bilete(B,nr_b);
    //am afisat toate biletele
    afisare_bilete(B,nr_b);
    //am eliberat biletul bil. acesta se citeste la finalul fisierului
    eliberare_bilet(bil,B,nr_b);
    //am afisat toate biletele
    afisare_bilete(B,nr_b);
    //am afisat toate biletele care parcurg o distanta mai mare de 90 km
    afisare_bilete_dupa_distanta(B,nr_b,90);
    //am afisat toate biletele care au codul trenului R-2
    afisare_bilete_dupa_cod_tren(B,nr_b,"R-2000");
    //am anulat biletul IRII-2
    anulare_bilet(B,nr_b,"IRII-2");
    //am afisat biletele
    afisare_bilete(B,nr_b);
    for(int i=0;i<nr_b;i++)
        delete B[i];

    return 0;
}
