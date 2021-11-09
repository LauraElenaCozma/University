#include <iostream>
#include <vector>
using namespace std;


class produs
{
    string denProd;
    float pretProd;

public:

    produs(){ pretProd=0;}
    produs(string denProd1,float pretProd1=0)
    {
        denProd=denProd1;
        pretProd=pretProd1;
    }
    produs(const produs& ob)
    {
        denProd=ob.denProd;
        pretProd=ob.pretProd;
    }
    produs& operator=(const produs& ob)
    {
        if(this==&ob)return (*this);
        denProd=ob.denProd;
        pretProd=ob.pretProd;
        return (*this);
    }

    friend istream& operator>>(istream& in,produs& ob)
    {
        in>>ob.denProd>>ob.pretProd;
        return in;
    }
    friend ostream& operator<<(ostream& out,const produs& ob)
    {
        out<<ob.denProd<<' '<<ob.pretProd<<' ';
        return out;
    }
    string get_denProd()
    {
        return denProd;
    }

    float get_pretProd()
    {
        return pretProd;
    }


};


class comanda
{
protected:

    int num;
    static int nr_com;
    produs prod;
    int nrPortii;
    int zi,luna,an;

public:
    comanda()
    {
        nr_com++;
        num=nr_com;
        nrPortii=0;
        zi=luna=an=0;
    }

    comanda(string denProd,float pretProd,int nrP) : prod(denProd, pretProd)
    {
        nr_com++;
        num=nr_com;
        nrPortii=nrP;
        zi=luna=an=0;
    }
    comanda(string denProd,float pretProd,int nrP,int z,int l,int a) : prod(denProd, pretProd)
    {
        nr_com++;
        num=nr_com;
        nrPortii=nrP;
        zi=z;
        luna=l;
        an=a;
    }
    comanda(const comanda& ob)
    {
        nr_com++;
        num=nr_com;
        nrPortii=ob.nrPortii;
        prod=ob.prod;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
    }
    comanda& operator=(const comanda& ob)
    {
        if(this==&ob)return (*this);
        nrPortii=ob.nrPortii;
        prod=ob.prod;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
        return (*this);
    }
    virtual void citire(istream& in)
    {
        in>>prod>>nrPortii>>zi>>luna>>an;
    }
    virtual void afisare(ostream& out) const
    {
        out<<prod<<' '<<"nr portii: "<<nrPortii<<" data: "<<zi<<'.'<<luna<<'.'<<an<<' ';
    }
    friend istream& operator>>(istream& in, comanda& ob)

    {
        ob.citire(in);
        return in;
    }

    friend ostream& operator<<(ostream& out,const comanda& ob)
    {
        ob.afisare(out);
        return out;
    }

    comanda& operator+(int x)
    {
        nrPortii+=x;
        return (*this);
    }

    comanda operator++(int)
    {
        comanda aux=(*this);
        nrPortii++;
        return aux;
    }

    comanda& del()
    {
        nrPortii=0;
        zi=luna=an=0;
        return (*this);
    }

    int get_zi()
    {
        return zi;
    }

    int get_luna()
    {
        return luna;
    }
    int get_an()
    {
        return an;
    }

    produs get_prod()
    {
        return prod;
    }

};
int comanda::nr_com=0;


class comandaSpeciala : virtual public comanda
{
protected:

    string obsC;
    float pretSupl;

public:
    comandaSpeciala() : comanda() {}
    comandaSpeciala(string denProd,float pretProd,int nrP,string obs,float pretSup) : comanda(denProd,pretProd,nrP) ,obsC(obs) , pretSupl(pretSup) {}
    comandaSpeciala(string denProd,float pretProd,int nrP,int z,int l,int a,string obs,float pretSup) : comanda(denProd,pretProd,nrP,z,l,a) ,obsC(obs) , pretSupl(pretSup) {}
    comandaSpeciala(const comandaSpeciala& ob)
    {
        obsC=ob.obsC;
        pretSupl=ob.pretSupl;
    }
    comandaSpeciala& operator=(const comandaSpeciala& ob)
    {
        if(this==&ob)return (*this);
        obsC=ob.obsC;
        pretSupl=ob.pretSupl;
        return (*this);
    }
    void citire(istream& in)
    {
        comanda::citire(in);
        in.get();
        getline(in,obsC);
        in>>pretSupl;
    }

    void afisare(ostream& out) const
    {
        comanda::afisare(out);
        out<<obsC<<' '<<pretSupl<<'\n';
    }

    string get_obsc()
    {
        return obsC;
    }

};

class comandaOnline : virtual public comanda
{
protected:

    string adr;
    int comLivr;

public :
    comandaOnline() : comanda() {}
    comandaOnline(string denProd,float pretProd,int nrP, string a) : comanda(denProd,pretProd,nrP), adr(a)  {comLivr=(5/100.0)*pretProd;}
    comandaOnline(string denProd,float pretProd,int nrP,int z,int l,int a, string ad) : comanda(denProd,pretProd,nrP,z,l,a), adr(ad)  {comLivr=(5/100.0)*pretProd;}
    comandaOnline(const comandaOnline& ob) : comanda(ob)
    {
        adr=ob.adr;
        comLivr=ob.comLivr;
    }
    comandaOnline& operator=(const comandaOnline& ob)
    {
        comanda::operator=(ob);
        if(this==&ob)return (*this);
        adr=ob.adr;
        comLivr=ob.comLivr;
        return (*this);
    }

    void citire(istream& in)
    {
        comanda::citire(in);
        getline(in,adr);
        comLivr=(5/100.0)*((this->get_prod()).get_pretProd());
    }

    void afisare(ostream& out) const
    {
        comanda::afisare(out);
        out<<adr<<" comision livrare: "<<comLivr<<' ';
    }

    int get_comLivr()
    {
        return comLivr;
    }

};

class comandaSpecialaOnline : public comandaSpeciala, public comandaOnline
{

public:
    comandaSpecialaOnline() : comandaSpeciala(), comandaOnline() {}
    comandaSpecialaOnline(string denProd,float pretProd,int nrP,string obs,float pretSup,string a) : comandaSpeciala(denProd,pretProd,nrP,obs,pretSup) , comandaOnline(denProd,pretProd,nrP,a) {}
    comandaSpecialaOnline(string denProd,float pretProd,int nrP,int z,int l,int a,string obs,float pretSup,string ad) : comandaSpeciala(denProd,pretProd,nrP,z,l,a,obs,pretSup) , comandaOnline(denProd,pretProd,nrP,z,l,a,ad) {}
    comandaSpecialaOnline(const comandaSpecialaOnline& ob) :comandaSpeciala(ob), comandaOnline(ob)
    {
        adr=ob.adr;
        comLivr=ob.comLivr;
    }

    comandaSpecialaOnline& operator=(const comandaSpecialaOnline& ob)
    {
        comandaSpeciala::operator=(ob);
        comandaOnline::operator=(ob);
        adr=ob.adr;
        comLivr=ob.comLivr;
        return *this;
    }

    void citire(istream& in)
    {
        comandaSpeciala::citire(in);
        getline(in,adr);
        comLivr=(5/100.0)*((this->get_prod()).get_pretProd());

    }

    void afisare(ostream& out)const
    {
        comandaSpeciala::afisare(out);
        out<<adr<<" comision livrare: "<<comLivr<<' ';

    }
};

class Ospatar
{
    string nume;
    vector <comanda *> C;
    int nrcomenzi;
    char gen;
    int varsta;

public:
    Ospatar()
    {
        nrcomenzi=0;
        varsta=0;
        gen='F';
    }

    Ospatar(string n,vector <comanda*> com,int nrcom,char g,int v) : nume(n) ,nrcomenzi(nrcom) , gen(g) , varsta(v)
    {
        C=com;
        C.resize(nrcom);
        for(int i=0;i<nrcom;i++)
        {
             comandaSpecialaOnline * cso= dynamic_cast <comandaSpecialaOnline *> (com[i]);
             if(cso!=NULL)
             {
                 C[i]=new comandaSpecialaOnline;
                 *(dynamic_cast <comandaSpecialaOnline *>(C[i]))=(*cso);
             }
             else
             {
                 comandaSpeciala * cs= dynamic_cast <comandaSpeciala *> (com[i]);
                 if(cs!=NULL)
                {
                    C[i]=new comandaSpeciala;
                    *(dynamic_cast <comandaSpeciala *>(C[i]))=*cs;
                }
                 else
                 {
                     comandaOnline * co= dynamic_cast <comandaOnline *> (com[i]);
                     if(co!=NULL)
                     {
                        C[i]=new comandaOnline;
                        *(dynamic_cast <comandaOnline *>(C[i]))=*co;
                     }
                     else
                     {
                         C[i]=new comanda;
                        *((comanda *)C[i])=*(com[i]);
                     }
                 }
             }
        }
    }
    Ospatar(const Ospatar& ob)
    {
        nume=ob.nume;
        nrcomenzi=ob.nrcomenzi;
        gen=ob.gen;
        varsta=ob.varsta;
        C=ob.C; //ar fi trebuit facut ca la constructorul de intializare
    }
    Ospatar& operator=(const Ospatar& ob)
    {
        if(this==&ob)return (*this);
        nume=ob.nume;
        nrcomenzi=ob.nrcomenzi;
        gen=ob.gen;
        varsta=ob.varsta;
        C=ob.C; //ar fi trebuit facut ca la constructorul de intializare
        return (*this);
    }

    friend ostream& operator<<(ostream& out,const Ospatar& ob)
    {
        out<<ob.nume<<" "<<ob.gen<<" "<<ob.varsta<<'\n';
        for(int i=0;i<ob.nrcomenzi;i++)
            out<<*(ob.C[i])<<'\n';
        return out;
    }

    bool operator>(const Ospatar& ob)
    {
        if(nrcomenzi>ob.nrcomenzi) return true;
        return false;
    }

    bool operator==(const Ospatar& ob)
    {
        if(nrcomenzi==ob.nrcomenzi) return true;
        return false;
    }

    vector <comanda*> get_comenzi()
    {
        return C;
    }

};


void afis_comenzi_dupa_data(int zi_d,int luna_d,int an_d,vector <comanda *> C , int nrc)
{
    cout<<"\n_______________________________________\nafis_comenzi_dupa_data\n\n";
    for(int i=0;i<nrc;i++)
    {
        int zi=C[i]->get_zi();
        int luna=C[i]->get_luna();
        int an=C[i]->get_an();

        if(zi==zi_d && luna==luna_d && an==an_d) cout<<*(C[i])<<'\n';
    }
}

void afis_papanasi(vector <comanda *> C , int nrc)
{
    cout<<"\n_______________________________________\nafis papanasi\n\n";
    for(int i=0;i<nrc;i++)
    {
        int luna=C[i]->get_luna();
        int an=C[i]->get_an();
        if(luna==5 && an==2016 && (C[i]->get_prod()).get_denProd()=="papanasi")cout<<*(C[i])<<'\n';
    }
    cout<<"\nCu nuca si cocos:\n\n";
    for(int i=0;i<nrc;i++)
    {
        int luna=C[i]->get_luna();
        int an=C[i]->get_an();
        comandaSpeciala *cs=dynamic_cast <comandaSpeciala *>(C[i]);
        if(cs!=NULL)
        {
            if(luna==5 && an==2016 && (cs->get_obsc())=="papanasi cu nuca si cocos") cout<<*cs<<'\n';
        }

    }
}

void afis_comenzi(vector <comanda *> C , int nrc)
{
    for(int i=0;i<nrc;i++)
    {
        cout<<*(C[i])<<'\n'<<'\n';
    }
}

void procent_online(vector <comanda *> C , int nrc)
{
    float sumacom=0,sumaonline=0;
    for(int i=0;i<nrc;i++)
    {

        int luna=C[i]->get_luna();
        int an=C[i]->get_an();

        if(luna==5 && an==2016)
        {
            sumacom+=(C[i]->get_prod()).get_pretProd();
            comandaOnline * com=dynamic_cast<comandaOnline *>(C[i]);

            if(com!=NULL)
                sumaonline+=((C[i]->get_prod()).get_pretProd())-(com->get_comLivr());

        }
    }
    if(sumaonline==0)cout<<0;
    else cout<<sumacom/(float)sumaonline;
}

void ospatar_profitabil( vector <Ospatar> O ,int nro)
{
    vector <float> s(nro,0);
    float maxi=0;
    int poz=0;
    for(int i=0;i<nro;i++)
    {
        vector <comanda*> com=O[i].get_comenzi();

        for(int j=0;j<com.size();j++)
        {
            if((com[j]->get_an())>=2016)s[i]+=(com[j]->get_prod()).get_pretProd();
        }


        if(maxi<s[i]){maxi=s[i]; poz=i;}
    }

    cout<<O[poz];

}
int main()
{
    produs meniu[4]={produs("frigariu",30),produs("cola",7.5),produs("cafea",5)};
    comanda c1("frigarui",30,2,30,5,2016),c2("papanasi",7.5,3),c3("cafea",5,1),c4=c2,c5;
    c3=c3+4;
    c2++;
    c2.del();
    //cin>>c5;
   // cout<<c4<<endl<<c5;
    vector <comanda *> com1,com2;
    comandaSpeciala c6("papanasi",7.5,3,"papanasi cu nuca si cocos",5);
    com1.push_back(&c1);
    com1.push_back(&c6);
    com1.push_back(&c3);
    com2.push_back(&c4);
    com2.push_back(&c5);
    Ospatar o1("Ionescu",com1,3,'M',25),o2("Popescu",com2,2,'F',30);
   // cout<<c6;
    cout<<o1<<o2;
    cout<<'\n'<<(o1>o2)<<'\n'<<(o1==o2);
    vector <Ospatar> O;
    O.push_back(o1);
    O.push_back(o2);
    cout<<'\n';
    ospatar_profitabil( O ,2);
    cout<<'\n';
    vector <comanda *> C;
    int nrc=6;
    C.push_back(&c1);
    C.push_back(&c2);
    C.push_back(&c3);
    C.push_back(&c4);
    C.push_back(&c5);
    C.push_back(&c6);
    afis_comenzi(C,nrc);
   // afis_comenzi_dupa_data(0,0,0,C ,nrc);
    afis_papanasi(C,nrc);
    cout<<"\n\n";
    procent_online(C,nrc);
    return 0;
}
