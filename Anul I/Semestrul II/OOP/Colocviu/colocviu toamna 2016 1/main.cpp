#include <iostream>
#include <fstream>
#include <string>
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


data adauga_zile(data d,int zile)
{
    if(zile+d.zi<=30)
        d.zi+=zile;
    else
    {
        zile/=30;
        if(zile+d.luna<=12)
            d.luna+=zile;
        else
        {
            zile/=12;
            d.an+=zile;
        }
    }
    return d;
}
class zbor
{
protected:
    static int nr_zbor;
    string id;
    string oras_plecare;
    string oras_sosire;
    data plecare;
    int durata;


public:

    zbor()
    {
        zbor::nr_zbor++;
        plecare.zi=0;
        plecare.luna=0;
        plecare.an=0;
        durata=0;

    }
    zbor(string id1,string plec,string sos,data d,int dur)
    {
        zbor::nr_zbor++;
        id=id1;
        oras_plecare=plec;
        oras_sosire=sos;
        plecare=d;
        durata=dur;

    }
    zbor(const zbor& ob)
    {
        zbor::nr_zbor++;
        id=ob.id;
        oras_plecare=ob.oras_plecare;
        oras_sosire=ob.oras_sosire;
        plecare=ob.plecare;
        durata=ob.durata;
    }

    zbor& operator=(const zbor& ob)
    {
        if(this==&ob)return (*this);
        id=ob.id;
        oras_plecare=ob.oras_plecare;
        oras_sosire=ob.oras_sosire;
        plecare=ob.plecare;
        durata=ob.durata;
        return (*this);
    }
    virtual ~zbor()
    {
        id.erase();
        oras_plecare.erase();
        oras_sosire.erase();
        zbor::nr_zbor--;
    }
    virtual void citire(istream& in)
    {
        in>>id;
        in.get();
        getline(in,oras_plecare);
        getline(in,oras_sosire);
        in>>plecare.zi>>plecare.luna>>plecare.an>>durata;
    }

    friend istream& operator>>(istream& in,zbor& ob);

    virtual void afisare(ostream & out) const
    {
        out<<": Id "<<id<<" Plecare: "<<oras_plecare<<" Sosire: "<<oras_sosire<<" Durata "<<durata<<' '<<" Data plecarii: "<<plecare.zi<<'.'<<plecare.luna<<'.'<<plecare.an<<' ';
    }

    friend ostream& operator<<(ostream& out,const zbor& ob)
    {
        ob.afisare(out);
        return out;
    }
    data get_plecare() const
    {
        return plecare;
    }

    virtual int get_perioada() const
    {
        return 0;
    }

    virtual bool e_discount()
    {
        return false;
    }
};

istream& operator>>(istream& in,zbor& ob)
{
    ob.citire(in);
    return in;
}

int zbor::nr_zbor=0;

class zbor_cu_discount: virtual public zbor
{
protected:

    float discount;
public:
    zbor_cu_discount()  : zbor()
    {
        discount=0;
    }

    zbor_cu_discount(string id1,string plec,string sos,data d,int dur,int disc) : zbor(id1,plec,sos,d,dur)
    {
        discount=disc;
    }

    zbor_cu_discount(const zbor_cu_discount& ob)  : zbor((const zbor&)ob)
    {
        discount=ob.discount;
    }

    zbor_cu_discount& operator=(const zbor_cu_discount& ob)
    {
        zbor::operator=(ob);
        discount=ob.discount;
        return (*this);

    }
    virtual ~zbor_cu_discount()
    {
        discount=0;
    }
    void citire(istream& in)
    {
        zbor::citire(in);
        in>>discount;
    }

    void afisare(ostream& out) const
    {
        zbor::afisare(out);
        out<<" Discount "<<discount;
    }
    int get_perioada() const
    {
        return 0;
    }
    bool e_discount()
    {
        return true;
    }

};

class zbor_temporar: virtual public zbor
{
protected:

    int perioada;
public:
    zbor_temporar() : zbor() {perioada=0;}
    zbor_temporar(string id1,string plec,string sos,data d,int dur,int per) : zbor(id1,plec,sos,d,dur)
    {
        perioada=per;
    }

    zbor_temporar(const zbor_temporar& ob) : zbor((const zbor& )ob)
    {
        perioada=ob.perioada;
    }

    zbor_temporar& operator=(const zbor_temporar& ob)
    {
        zbor::operator=(ob);
        perioada=ob.perioada;
        return *this;
    }
    ~zbor_temporar()
    {
        perioada=0;
    }
    void citire(istream& in)
    {
        zbor::citire(in);
        in>>perioada;
    }
    void afisare(ostream & out) const
    {
        zbor::afisare(out);
        out<<" Perioada zborului temporar "<<perioada;
    }
    virtual int get_perioada() const
    {
        return perioada;
    }
    bool e_discount()
    {
        return false;
    }
};

class zbor_temporar_cu_discount:public zbor_cu_discount,public zbor_temporar
{
public:
    ~zbor_temporar_cu_discount(){};
    zbor_temporar_cu_discount() : zbor(), zbor_cu_discount(), zbor_temporar(){}
    zbor_temporar_cu_discount(string id1,string plec,string sos,data d,int dur,int per,int disc) : zbor(id1,plec,sos,d,dur) , zbor_cu_discount(id1,plec,sos,d,dur,disc) , zbor_temporar(id1,plec,sos,d,dur,per){}

    zbor_temporar_cu_discount(const zbor_temporar_cu_discount& ob) : zbor((const zbor& )ob) , zbor_cu_discount((const zbor_cu_discount& )ob),zbor_temporar((const zbor_temporar&)ob){}

    zbor_temporar_cu_discount& operator=(const zbor_temporar_cu_discount& ob)
    {
        zbor::operator=(ob);
        perioada=ob.perioada;
        discount=ob.discount;
        return *this;
    }
    void citire(istream& in)
    {
        zbor::citire(in);
        in>>discount;
        in>>perioada;
    }
    void afisare(ostream & out) const
    {
        zbor::afisare(out);
        cout<<"Discount "<<discount<<" perioada zborului temporar "<<perioada;
    }
    virtual int get_perioada() const
    {
        return perioada;
    }
    bool e_discount()
    {
        return true;
    }
};
class ruta
{
    string oras_plecare;
    string oras_sosire;
    float pret;
    int nr_curse;
    vector <zbor*> curse;

public:
    ruta()
    {
        pret=0;
        nr_curse=0;
    }
    ruta(string plec,string sos, float pret1, int nr_curse1, vector <zbor*> curse1)
    {
        oras_plecare=plec;
        oras_sosire=sos;
        pret=pret1;
        nr_curse=nr_curse1;
        curse.resize(nr_curse);
        curse=curse1;
    }

    friend  istream& operator>>(istream& in, ruta& ob)
    {
        getline(in,ob.oras_plecare);
        getline(in,ob.oras_sosire);
        in>>ob.pret>>ob.nr_curse;
        ob.curse.resize(ob.nr_curse);
        for(int i=0;i<ob.nr_curse;i++)
        {
            char tip;
            /// 'z' - zbor, 't'-zbor temporar, 'd'-zbor cu discount, 'm'- zbor si cu discount si temporar(mixt)
            fin>>tip;
            if(tip=='z') ob.curse[i]=new zbor;
            else if(tip=='t')ob.curse[i]=new zbor_temporar;
                 else if(tip=='d')ob.curse[i]=new zbor_cu_discount;
                      else if(tip=='m')ob.curse[i]=new zbor_temporar_cu_discount;
            in>>*(ob.curse[i]);

            in.get();

        }
        if(ob.nr_curse==0)in.get();

        return in;
    }

    friend ostream& operator<<(ostream& out,const ruta& ob)
    {
        cout<<"\nPlecare: "<<ob.oras_plecare<<" Sosire: "<<ob.oras_sosire<<" Pret: "<<ob.pret<<" Nr curse "<<ob.nr_curse<<'\n';
        for(int i=0;i<ob.nr_curse;i++)
            cout<<*(ob.curse[i]);
        return out;
    }
    void add_zbor(zbor* z)
    {
        curse.push_back(z);
        nr_curse++;
    }

    vector <zbor*> get_curse() const
    {
        return curse;
    }

    int get_nr_curse() const
    {
        return nr_curse;
    }
};

void adauga_ruta(ruta rut,vector <ruta>& R,int& nr_rute)
{
    R.push_back(rut);
    nr_rute++;
}

void afisare_rute(vector <ruta>& R,int& nr_rute)
{
    for(int i=0;i<nr_rute;i++)
        cout<<R[i]<<'\n';
}

void adauga_cursa(zbor* z, vector<ruta>& R, int nr_rute, int poz)//r[poz] e modificat
{
    R[poz].add_zbor(z);
}

void afis_curse_intre_2_date(data d1,data d2,vector<ruta>& R,int nr_rute)
{
    for(int i=0;i<nr_rute;i++)
    {
        vector <zbor*> z=R[i].get_curse();
        int nrz=R[i].get_nr_curse();
        for(int j=0;j<nrz;j++)
        {
            data d=z[j]->get_plecare();
            if(cmp_date(d1,d)<=0 && cmp_date(d,d2)<=0)
                cout<<*(z[j])<<'\n';
        }
    }

}

void curse_active_curent(data curenta,vector<ruta>& R,int nr_rute)
{
    for(int i=0;i<nr_rute;i++)
    {
        vector <zbor*> z=R[i].get_curse();
        int nrz=R[i].get_nr_curse();
        for(int j=0;j<nrz;j++)
        {
            data d=z[j]->get_plecare();


            if(z[j]->get_perioada()!=0)
            {
                d=adauga_zile(d,z[j]->get_perioada());
                if(cmp_date(d,curenta)>=0)
                    cout<<*(z[j])<<'\n';
            }
            else cout<<*(z[j])<<'\n';




        }


    }
}

void afis_rute_fara_discount(vector<ruta>& R,int nr_rute)
{
    for(int i=0;i<nr_rute;i++)
    {
        vector <zbor*> z=R[i].get_curse();
        int nrz=R[i].get_nr_curse();
        int ok=0;
        for(int j=0;j<nrz ;j++)
        {
            ok+=z[j]->e_discount();
        }
        if(!ok)cout<<R[i]<<'\n';

    }
}


int main()
{
    vector <ruta> R;
    int nr_rute;
    fin>>nr_rute;
    R.resize(nr_rute);
    fin.get();
    for(int i=0;i<nr_rute;i++)
        {fin>>R[i]; }


    int opt;
    do
    {   cout<<"\n___________________________________________\n";
        cout<<"1 : Adauga ruta noua\n";
        cout<<"2 : Afiseaza toate rutele\n";
        cout<<"3 : Adauga o cursa pe o anumita ruta\n";
        cout<<"4 : Afiseaza toate cursele dintre 2 date\n";
        cout<<"5 : Afiseaza toate cursele active la data curenta\n";
        cout<<"6 : Afiseaza rute fara discount\n";
        cout<<"Optiunea ta este: ";
        cin>>opt;
        switch(opt)
        {
        case 1:{
                vector <zbor*> v;
                ruta rut("moscova","berlin",200,0,v);
                adauga_ruta(rut,R,nr_rute);
               }
            break;
        case 2:afisare_rute(R,nr_rute);
            break;
        case 3:zbor *z;
               char tip;
               fin>>tip;
               if(tip=='z') z=new zbor;
               else if(tip=='t')z=new zbor_temporar;
                    else if(tip=='d')z=new zbor_cu_discount;
                         else if(tip=='m')z=new zbor_temporar_cu_discount;
               fin>>*(z);
               adauga_cursa(z,R,nr_rute,1);
            break;
        case 4:afis_curse_intre_2_date({25,2,2019},{13,5,2020},R,nr_rute);
            break;
        case 5:curse_active_curent({16,5,2019},R,nr_rute);
            break;
        case 6:afis_rute_fara_discount(R,nr_rute);
            break;
        default:
            break;
        }
    }
    while(opt!=0);

    return 0;
}
