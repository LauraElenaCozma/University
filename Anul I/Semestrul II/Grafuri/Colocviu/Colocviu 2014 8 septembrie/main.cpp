#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("date.in");

struct data
{
    int zi,luna,an;
};



int cmp_date(data d1,data d2)
{
    if(d1.an<d2.an)return -1;
    else if(d1.an>d2.an)return 1;
         else
         {
             if(d1.luna<d2.luna)return -1;
             else if(d1.luna>d2.luna)return 1;
                  else
                  {
                      if(d1.zi<d2.zi)return -1;
                      else if(d1.zi>d2.zi)return 1;
                           else return 0;
                  }
         }
}

int nr_ani(data d1, data d2)
{
    return d2.an-d1.an;
}
class angajat
{
protected:
    string nume;
    string prenume;
    data inceput;
    float prima;
    static float prima_fixa;

public:
    virtual string tip_contract() const = 0;
    virtual string tip_activitate() const = 0 ;
    angajat(string nume1="",string prenume1="",data inceput1={0,0,0}) : nume(nume1) , prenume(prenume1) , inceput(inceput1)  { }
    angajat(const angajat& ob)
    {
        nume=ob.nume;
        prenume=ob.prenume;
        inceput=ob.inceput;
        prima=ob.prima;
    }
    angajat& operator=(const angajat& ob)
    {
        if(this==&ob)return *this;
        nume=ob.nume;
        prenume=ob.prenume;
        inceput=ob.inceput;
        prima=ob.prima;

        return *this;
    }
    virtual void calcul_prima() = 0;
    virtual void citire(istream & in)
    {
        in>>nume>>prenume>>inceput.zi>>inceput.luna>>inceput.an;

    }

    virtual void afisare(ostream& out) const
    {
        out<<nume<<" "<<prenume<<' '<<tip_contract()<<' '<<inceput.zi<<'.'<<inceput.luna<<'.'<<inceput.an<<" "<<tip_activitate()<<" Prima: "<<prima<<' ';
    }
    friend istream& operator>>(istream& in, angajat& ob)
    {
        ob.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out,const angajat& ob)
    {
        ob.afisare(out);
        return out;
    }
};
float angajat::prima_fixa=400;

class angajat_permanent : public angajat
{

public:
    angajat_permanent(string nume1="",string prenume1="",data inceput1={0,0,0}) : angajat(nume1,prenume1,inceput1) { }
    angajat_permanent(const angajat_permanent& ob): angajat(ob) { }
    angajat_permanent& operator=(const angajat_permanent& ob)
    {
        angajat::operator=(ob);
        return *this;
    }
    string tip_contract() const { return "Permanent";}
    virtual string tip_activitate() const = 0;
};

class plata_cu_ora : public angajat
{
    data terminare;
public:
    plata_cu_ora(string nume1="",string prenume1="",data inceput1={0,0,0},data terminare1={0,0,0}) : angajat(nume1,prenume1,inceput1)
    {
        terminare=terminare1;
        calcul_prima();
    }
    plata_cu_ora(const plata_cu_ora& ob) : angajat(ob)
    {
        terminare=ob.terminare;
    }
    plata_cu_ora& operator=(const plata_cu_ora& ob)
    {
        angajat::operator=(ob);
        terminare=ob.terminare;
        return *this;
    }
    void calcul_prima()
    {
        if(cmp_date(terminare,{31,12,2014})<=0) prima=angajat::prima_fixa/2;
        else prima=angajat::prima_fixa;

    }
    void citire(istream& in)
    {
        angajat::citire(in);
        in>>terminare.zi>>terminare.luna>>terminare.an;
        calcul_prima();
    }
    void afisare(ostream& out) const
    {
        angajat::afisare(out);
        cout<<"Data incheierii contractului: "<<terminare.zi<<'.'<<terminare.luna<<'.'<<terminare.an<<'\n';
    }
    string tip_contract() const {return "Plata cu ora";}
    string tip_activitate() const { return "";}
    data get_terminare() const
    {
        return terminare;
    }
};

class TESA : public angajat_permanent
{
    int weekend;
public:
    TESA(string nume1="",string prenume1="",data inceput1={0,0,0},int weekend1=0) : angajat_permanent(nume1,prenume1,inceput1) , weekend(weekend1) {calcul_prima();}
    TESA(const TESA& ob) : angajat_permanent(ob)
    {
        weekend=ob.weekend;
    }
    TESA& operator=(const TESA& ob)
    {
        angajat_permanent::operator=(ob);
        weekend=ob.weekend;
        return *this;
    }
    void citire(istream& in)
    {
        angajat::citire(in);
        in>>weekend;
        calcul_prima();
    }
    void afisare(ostream& out) const
    {
        angajat::afisare(out);
        cout<<"Weekend ul ales "<<weekend<<'\n';
    }
    void calcul_prima()
    {
        prima=angajat::prima_fixa;

    }
    string tip_activitate() const { return "TESA"; }
    string tip_contract() const { return angajat_permanent::tip_contract();}
    int get_weekend()
    {
        return weekend;
    }
};

class lucrativ : public angajat_permanent
{
    int nr_copii;
public:
    lucrativ(string nume1="",string prenume1="",data inceput1={0,0,0},int nr_copii1=0) : angajat_permanent(nume1,prenume1,inceput1) , nr_copii(nr_copii1) { calcul_prima();}
    lucrativ(const lucrativ& ob) : angajat_permanent(ob)
    {
        nr_copii=ob.nr_copii;
    }
    lucrativ& operator=(const lucrativ& ob)
    {
        angajat_permanent::operator=(ob);
        nr_copii=ob.nr_copii;
        return *this;
    }
    void citire(istream& in)
    {
        angajat::citire(in);
        in>>nr_copii;
        calcul_prima();
    }
    void afisare(ostream& out) const
    {
        angajat::afisare(out);
        cout<<"Numarul de copii minori "<<nr_copii<<'\n';
    }
    void calcul_prima()
    {
        prima=angajat::prima_fixa;
        prima+=(nr_copii*nr_ani(inceput,{31,12,2014})*angajat::prima_fixa/100.0);

    }
    int get_nr_copii()
    {
        return nr_copii;
    }
    string tip_activitate() const { return "Lucrativ";}
    string tip_contract() const { return angajat_permanent::tip_contract();}
};

class firma
{
    vector <angajat *> A;
    int nr_angajati = 0;

public:
    void citire_angajati()
    {
    fin>>nr_angajati;
    A.resize(nr_angajati);

    char tip; //l=lucrativ, o=plata cu ora, t=tesa

    for(int i=0;i<nr_angajati;i++)
    {
        fin>>tip;
        if(tip=='l')A[i]=new lucrativ;
        else if(tip=='t')A[i]=new TESA;
             else A[i]=new plata_cu_ora;
        fin>>*(A[i]);
    }
    }

    void afisare_angajati()
    {
        for(int i=0;i<nr_angajati;i++)
        {
            cout<<A[i]->tip_contract()<<' ';
            if(A[i]->tip_contract()=="Permanent") cout<<A[i]->tip_activitate()<<'\n';
            else cout<<'\n';
            cout<<*(A[i]);
        }
        cout<<'\n';
    }

    void afisare_angajati_lucrativi_cu_minori()
    {
        cout<<"\nAngajat lucrativ cu copii minori:\n";
        for(int i=0;i<nr_angajati;i++)
        {
            if(A[i]->tip_contract()=="Permanent" && A[i]->tip_activitate()=="Lucrativ" && ((lucrativ *)A[i])->get_nr_copii()>0) cout<<*(A[i]);
        }
    }

    void vacanta_weekend2()
    {
        int ok=0;
        cout<<"\nAngajati care pleaca in vacanta in al doilea weekend:\n";
        for(int i=0;i<nr_angajati;i++)
        {
            if(A[i]->tip_contract()=="Permanent" && A[i]->tip_activitate()=="TESA" && ((TESA *)A[i])->get_weekend()==2) {cout<<*(A[i]); ok=1;}
        }

        if(!ok)cout<<"Nu exista.\n";
    }

    void angajati_ora_dupa_martie2015()
    {
        int ok=0;
        cout<<"\nAngajati platiti cu ora care au contractul de munca pana dupa martie 2015:\n";
        for(int i=0;i<nr_angajati;i++)
        {
            if(A[i]->tip_contract()=="Plata cu ora" && cmp_date(((plata_cu_ora *)A[i])->get_terminare(),{1,3,2015})>=0) {cout<<*(A[i]); ok=1;}
        }

        if(!ok)cout<<"Nu exista.\n";
    }

};




int main()
{
    firma X;
    X.citire_angajati();
    X.afisare_angajati();
    X.afisare_angajati_lucrativi_cu_minori();
    X.vacanta_weekend2();
    X.angajati_ora_dupa_martie2015();
    return 0;
}
