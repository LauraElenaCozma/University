#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
ifstream fin("date.in");

class pacient
{
protected:
    string nume;
    string prenume;
    string adresa;
    int varsta;
    float colesterol;
    float tensiune;
    int zi,luna,an;  //data la care s-au facut analizele

public:
    pacient(string nume1="",string prenume1="",string adresa1="",int varsta1=0,float c=0,float t=0,int z=0,int l=0,int a=0) : nume(nume1), prenume(prenume1), adresa(adresa1), varsta(varsta1), colesterol(c),tensiune(t),zi(z),luna(l),an(a){}
    pacient (const pacient& ob)
    {
        nume=ob.nume;
        prenume=ob.prenume;
        adresa=ob.adresa;
        varsta=ob.varsta;
        colesterol=ob.colesterol;
        tensiune=ob.tensiune;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
    }
    pacient& operator= (const pacient& ob)
    {
        if(this==&ob)return (*this);
        nume=ob.nume;
        prenume=ob.prenume;
        adresa=ob.adresa;
        varsta=ob.varsta;
        colesterol=ob.colesterol;
        tensiune=ob.tensiune;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
        return (*this);
    }

    virtual void  citire(istream &in)
    {
        in>>nume>>prenume>>adresa>>varsta>>colesterol>>tensiune>>zi>>luna>>an;
    }
    friend istream& operator>>(istream& in,pacient& ob)
    {
        ob.citire(in);
        return in;
    }
    virtual void  afisare(ostream& out) const
    {
        cout<<"\nNume "<<nume<<" prenume "<<prenume<<' '<<adresa<<" varsta "<<varsta<<" colesterol: "<<colesterol<<" tensiune "<<tensiune<<" Data: "<<zi<<'.'<<luna<<'.'<<an<<' ';
    }
    friend ostream& operator<<(ostream& out,const pacient& ob)
    {
        ob.afisare(out);
        return out;
    }
    float get_colesterol()
    {
        return colesterol;
    }
    float get_tensiune()
    {
        return tensiune;
    }
    string get_nume()
    {
        return nume;
    }
    virtual ~pacient() = 0;
    virtual char get_tip() = 0;
    virtual string get_sedentarism(){};
    virtual string get_fumat(){};
    virtual string get_precedent(){};

};
pacient::~pacient()
{

}

class adult: public pacient
{
    public:
       adult(string nume1="",string prenume1="",string adresa1="",int varsta1=0,float c=0,float t=0,int z=0,int l=0,int a=0) :pacient(nume1,prenume1,adresa1,varsta1,c,t,z,l,a){}
       adult(const adult& ob) : pacient(ob){}
       adult& operator=(const adult& ob)
       {
           pacient::operator=(ob);
           return (*this);
       }
       void citire(istream& in)
        {
            pacient::citire(in);

        }
        void afisare(ostream & out) const
        {
            pacient::afisare(out);
        }
        virtual char get_tip() =0;
        ~adult(){}
};

class adult_sub_40 : public adult
{
    public:
       adult_sub_40(string nume1="",string prenume1="",string adresa1="",int varsta1=0,float c=0,float t=0,int z=0,int l=0,int a=0) :adult(nume1,prenume1,adresa1,varsta1,c,t,z,l,a){}
       adult_sub_40(const adult_sub_40& ob) : adult(ob){}
       adult_sub_40& operator=(const adult_sub_40& ob)
       {
           adult::operator=(ob);
           return (*this);
       }
       void citire(istream& in)
        {
            adult::citire(in);

        }
        void afisare(ostream & out) const
        {
            adult::afisare(out);
        }
        char get_tip()
        {
            return 's';
        }
        ~adult_sub_40(){}
};

class adult_peste_40 : public adult
{
    string sedentarism;
    string fumat;

public:
    adult_peste_40(string nume1="",string prenume1="",string adresa1="",int varsta1=0,float c=0,float t=0,int z=0,int l=0,int a=0,string sed="", string f="") :adult(nume1,prenume1,adresa1,varsta1,c,t,z,l,a)
    {
        sedentarism=sed;
        fumat=f;
    }
    adult_peste_40(const adult_peste_40& ob) : adult(ob)
    {
        sedentarism=ob.sedentarism;
        fumat=ob.fumat;
    }
    adult_peste_40& operator=(const adult_peste_40& ob)
    {
        adult::operator=(ob);
        if(this==&ob)return *this;
        sedentarism=ob.sedentarism;
        fumat=ob.fumat;
        return *this;
    }
    void citire(istream& in)
    {
        adult::citire(in);
        in>>sedentarism>>fumat;

    }
    void afisare(ostream & out) const
    {
        adult::afisare(out);
        out<<" Sedentarism "<<sedentarism<<" fumat: "<<fumat;
    }

    ~adult_peste_40(){}
    char get_tip()
    {
        return 'p';
    }
    string get_sedentarism()
    {
        return sedentarism;
    }

    string get_fumat()
    {
        return fumat;
    }
};

class copil : public pacient
{
    string precedent;
    string nume_parinte;
    string prenume_parinte;
    float proteinaC;

public:
    copil(string nume1="",string prenume1="",string adresa1="",int varsta1=0,float c=0,float t=0,int z=0,int l=0,int a=0,string precedent="",string np="",string pp="",float pC=0) :pacient(nume1,prenume1,adresa1,varsta1,c,t,z,l,a){}
    copil(const copil& ob) : pacient(ob)
    {
        precedent=ob.precedent;
        nume_parinte=ob.nume_parinte;
        prenume_parinte=ob.prenume_parinte;
        proteinaC=ob.proteinaC;
    }
    copil& operator=(const copil& ob)
    {
        pacient::operator=(ob);
        if(this==&ob)return *this;
        precedent=ob.precedent;
        nume_parinte=ob.nume_parinte;
        prenume_parinte=ob.prenume_parinte;
        proteinaC=ob.proteinaC;
        return (*this);
    }
    void citire(istream& in)
    {
        pacient::citire(in);
        in>>precedent>>nume_parinte>>prenume_parinte>>proteinaC;

    }
    void afisare(ostream & out) const
    {
        pacient::afisare(out);
        out<<" Precedent "<<precedent<<" nume_parinte "<<nume_parinte<<" prenume_parinte "<<prenume_parinte<<" Proteina C: "<<proteinaC;
    }
    char get_tip()
    {
        return 'c';
    }
    ~copil(){}
    string get_precedent()
    {
        return precedent;
    }

};



class info_pacienti
{
    vector <pacient *> P;
    int nr_pacienti;

public:
    info_pacienti()
    {
        nr_pacienti=0;
    }
    info_pacienti(int nr_pacienti1, vector <pacient* > P1)
    {
        nr_pacienti=nr_pacienti1;
        P=P1;
    }
    info_pacienti(const info_pacienti& ob)
    {
        P=ob.P;
        nr_pacienti=ob.nr_pacienti;
    }
    info_pacienti& operator=(const info_pacienti& ob)
    {
        if(this==&ob)return (*this);
        P=ob.P;
        nr_pacienti=ob.nr_pacienti;
        return (*this);
    }
    friend operator>>(istream& in, info_pacienti& ob)
    {
        in>>ob.nr_pacienti;
        ob.P.resize(ob.nr_pacienti);

        char tip;
        for(int i=0;i<ob.nr_pacienti;i++)
        {
            fin>>tip;
            if(tip=='c')ob.P[i]=new copil;
            else if(tip=='p')ob.P[i]=new adult_peste_40;
                 else if(tip=='s')ob.P[i]=new adult_sub_40;

            fin>>*(ob.P[i]);
        }
    }
    friend operator<<(ostream& out,const info_pacienti& ob)
    {
        for(int i=0;i<ob.nr_pacienti;i++)
            cout<<*(ob.P[i]);
    }

    void afis_adulti_ridicat()
    {
        cout<<"____________________________________________________\nAdulti cu risc ridicat:\n";
        for(int i=0;i<nr_pacienti;i++)
        {
            char tip=P[i]->get_tip();
            int ok=0;
            if(P[i]->get_colesterol()>240)ok++;
            if(P[i]->get_tensiune()>139)ok++;
            if(tip=='p')
            {
                if(P[i]->get_sedentarism()=="ridicat")ok++;
                if(P[i]->get_fumat()=="fumator")ok++;
            }
            if(ok>=2)cout<<*(P[i])<<'\n';
        }
    }

    void afis_copii_cu_risc()
    {
        cout<<"____________________________________________________\nCopii cu risc cardiovascular:\n";
        for(int i=0;i<nr_pacienti;i++)
        {
            char tip=P[i]->get_tip();
            int ok=0;
            if(P[i]->get_colesterol()>240)ok++;
            if(P[i]->get_tensiune()>139)ok++;
            if(tip=='c')
            {
                if(P[i]->get_precedent()=="DA")ok++;
                if(ok)cout<<*(P[i])<<'\n';
            }

        }
    }

    void afis_pacienti_dupa_nume(string nume)
    {
        cout<<"____________________________________________________\nAfiseaza pacientii cu numele "<<nume<<":\n";
        for(int i=0;i<nr_pacienti;i++)
        {
            if(P[i]->get_nume()==nume)cout<<*(P[i]);

        }
    }
};




int main()
{
    info_pacienti X;
    fin>>X;
    cout<<X;
    X.afis_adulti_ridicat();
    X.afis_copii_cu_risc();
    X.afis_pacienti_dupa_nume("Ionescu");
    return 0;
}
