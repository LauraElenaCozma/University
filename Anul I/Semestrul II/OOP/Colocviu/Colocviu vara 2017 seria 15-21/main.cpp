#include <iostream>
#include <string>
#include <vector>
using namespace std;

int nr_luni(int luna1,int an1,int luna2,int an2)
{
    int an=(an2-an1)*12;
    if(luna1>luna2) return an-(luna1-luna2); //inca nu s-a implinit un an
    return an+luna2-luna1;
}

int cmp_date(int luna1,int an1,int luna2,int an2)
{
    if(an1<an2)return -1;
    else if(an1>an2)return 1;
    else
    {
        if(luna1<luna2)return -1;
        else if(luna1>luna2)return 1;
        return 0;//egalitate
    }
}

class proprietate
{
protected:
    string adresa;
    float suprafata;
    float val_chirie;

public:
    proprietate(string adresa1="", float suprafata1=0, float val_chirie1=0) : adresa(adresa1), suprafata(suprafata1), val_chirie(val_chirie1) {}
    proprietate( const proprietate& ob)
    {
        adresa=ob.adresa;
        suprafata=ob.suprafata;
        val_chirie=ob.val_chirie;
    }
    proprietate& operator=( const proprietate& ob)
    {
        if(this==&ob)return *this;
        adresa.clear();
        adresa=ob.adresa;
        suprafata=ob.suprafata;
        val_chirie=ob.val_chirie;
        return *this;
    }

    virtual void citire(istream& in)
    {
        in>>adresa>>suprafata>>val_chirie;
    }

    virtual void afisare(ostream& out) const
    {
        out<<"Adresa "<<adresa<<" suprafata "<<suprafata<<" valoarea chiriei "<<val_chirie;
    }

    friend istream& operator>>(istream& in,proprietate& ob)
    {
        ob.citire(in);
        return in;
    }

    friend ostream& operator<<(ostream& out, const proprietate& ob)
    {
        ob.afisare(out);
        return out;
    }
    virtual char get_tip() = 0;
    float get_suprafata()
    {
        return suprafata;
    }
    float get_val_chirie()
    {
        return val_chirie;
    }
    virtual float get_suprafata_curte() = 0;
};

class apartament : public proprietate
{
    int etaj;
    int nr_camere;
public :
    apartament(string adresa1="", float suprafata1=0, float val_chirie1=0, int etaj1 = 0 , int nr_camere1 = 0) :proprietate(adresa1,suprafata1,val_chirie1), etaj(etaj1), nr_camere(nr_camere1) {}
    apartament(const apartament& ob) : proprietate(ob)
    {
         etaj=ob.etaj;
         nr_camere=ob.nr_camere;
    }
    apartament& operator=(const apartament& ob)
    {
         proprietate:: operator=(ob);
         if(this==&ob)return (*this);
         etaj=ob.etaj;
         nr_camere=ob.nr_camere;

         return (*this);
    }

    void citire(istream& in)
    {
        proprietate::citire(in);
        in>>etaj>>nr_camere;
    }


    void afisare(ostream& out) const
    {
        proprietate::afisare(out);
        out<<" Etaj "<<etaj<<" Nr camere "<<nr_camere<<"\n";
    }

    char get_tip()
    {
        return 'a';
    }
    float get_suprafata_curte()
    {
        return 1;
    }


};


class casa : public proprietate
{
    int nr_niveluri;
    float suprafata_curte;

public :
    casa(string adresa1="", float suprafata1=0, float val_chirie1=0, int nr_niveluri1 = 0 , float suprafata_curte1 = 0) :proprietate(adresa1,suprafata1,val_chirie1) , nr_niveluri(nr_niveluri1) , suprafata_curte(suprafata_curte1) {}
    casa(const casa& ob) : proprietate(ob)
    {
        nr_niveluri=ob.nr_niveluri;
        suprafata_curte=ob.suprafata_curte;
    }
    casa& operator=(const casa& ob)
    {
        proprietate::operator=(ob);
        if(this==&ob)return (*this);
        nr_niveluri=ob.nr_niveluri;
        suprafata_curte=ob.suprafata_curte;
        return (*this);
    }

    void citire(istream& in)
    {
        proprietate::citire(in);
        in>>nr_niveluri>>suprafata_curte;
    }

    void afisare(ostream& out) const
    {
        proprietate::afisare(out);
        cout<<" nr de niveluri "<<nr_niveluri<<" suprafata curte "<<suprafata_curte<<'\n';
    }
    char get_tip()
    {
        return 'c';
    }

    float get_suprafata_curte()
    {
        return suprafata_curte;
    }
};


class contract
{
protected:

    proprietate * p;
    string nume_client;

public:
    contract()
    {
        p=NULL;
    }
    contract(string nume_client1, proprietate *p1)
    {
        char tip=p1->get_tip();
        if(tip=='a'){p=new apartament; (*((apartament *)p))=*((apartament *)p1);}
        else {p=new casa; (*((casa *)p))=*((casa *)p1);}
        nume_client=nume_client1;

    }
    contract(const contract& ob)
    {
        char tip=(ob.p)->get_tip();
        if(tip=='a')p=new apartament;
        else p=new casa;
        (*p)=*(ob.p);
        nume_client=ob.nume_client;
    }

    contract& operator=(const contract& ob)
    {
        if(this==&ob)return (*this);
        char tip=(ob.p)->get_tip();
        if(tip=='a'){p=new apartament; (*((apartament *)p))=*((apartament *)ob.p); }
        else {p=new casa; (*((casa *)p))=*((casa *)ob.p);}

        nume_client=ob.nume_client;
        return (*this);
    }

    virtual void citire(istream &in)
    {
        char tip;
        in>>tip;
        if(tip=='a')p=new apartament;
        else p=new casa;
        in>>*p>>nume_client;
    }

    virtual void afisare(ostream& out) const
    {
        cout<<"\nProprietate: "<<(*p)<<"Nume client "<<nume_client;
    }

    friend istream& operator>>(istream& in, contract& ob)
    {
        ob.citire(in);
        return in;
    }

    friend ostream& operator<<(ostream& out,const contract& ob)
    {
        ob.afisare(out);
        return out;
    }

    virtual double chirie() = 0;

    proprietate* get_proprietate()
    {
        return p;
    }
};


class contract_inchiriere : public contract
{
    int luna_inc,an_inc;
    int luna_sf,an_sf;


public :
    contract_inchiriere()  : contract()
    {
        luna_inc=0;
        an_inc=0;
        luna_sf=0;
        an_sf=0;
    }
    contract_inchiriere(string nume_client1, proprietate *p1,int li,int ai,int ls,int as) : contract(nume_client1,p1)
    {
        luna_inc=li;
        an_inc=ai;
        luna_sf=ls;
        an_sf=as;
    }

    contract_inchiriere(const contract_inchiriere& ob) : contract(ob)
    {

        luna_inc=ob.luna_inc;
        an_inc=ob.an_inc;
        luna_sf=ob.luna_sf;
        an_sf=ob.an_sf;
    }

    contract_inchiriere& operator=(const contract_inchiriere& ob)
    {
        contract::operator=(ob);
        if(this==&ob)return (*this);
        luna_inc=ob.luna_inc;
        an_inc=ob.an_inc;
        luna_sf=ob.luna_sf;
        an_sf=ob.an_sf;
        return (*this);
    }

    void citire(istream& in)
    {
        contract::citire(in);
        in>>luna_inc>>an_inc>>luna_sf>>an_sf;
    }
    void afisare(ostream& out) const
    {
        contract::afisare(out);
        out<<" Data inceperii contractului "<<luna_inc<<'.'<<an_inc<< " data terminarii contractului "<<luna_sf<<'.'<<an_sf;
    }

    double chirie()
    {
        float an=nr_luni(luna_inc,an_inc,luna_sf,an_sf)/12.0;
        int discount=0;
        if(an>2)discount=10;
        else if(an>1)discount=5;

        int s=p->get_suprafata();
        int c=p->get_val_chirie();
        char tip=p->get_tip();
        if(tip=='a')
        {
            return c*s*(1-discount/100.0);
        }

        else
        {
            float sc=p->get_suprafata_curte();
            return c*(s+0.2*sc)*(1-(discount/100.0));
        }

    }

    int get_luna_sf()
    {
        return luna_sf;
    }

    int get_an_sf()
    {
        return an_sf;
    }
    int get_luna_inc()
    {
        return luna_inc;
    }

    int get_an_inc()
    {
        return an_inc;
    }

};

class contract_vanzare : public contract
{
    int luna_tranz,an_tranz;
    int luna_integral,an_integral;

public:
    contract_vanzare()  : contract()
    {
        luna_tranz=0;
        an_tranz=0;
        luna_integral=0;
        an_integral=0;
    }
    contract_vanzare(string nume_client1, proprietate *p1,int lt,int ant,int li,int ai) : contract(nume_client1,p1)
    {
        luna_tranz=lt;
        an_tranz=ant;
        luna_integral=li;
        an_integral=ai;
    }

    contract_vanzare(const contract_vanzare& ob) : contract(ob)
    {
        luna_tranz=ob.luna_tranz;
        an_tranz=ob.an_tranz;
        luna_integral=ob.luna_integral;
        an_integral=ob.an_integral;
    }

    contract_vanzare& operator=(const contract_vanzare& ob)
    {
        contract::operator=(ob);
        if(this==&ob)return (*this);
        luna_tranz=ob.luna_tranz;
        an_tranz=ob.an_tranz;
        luna_integral=ob.luna_integral;
        an_integral=ob.an_integral;
        return (*this);
    }

    void citire(istream& in)
    {
        contract::citire(in);
        in>>luna_tranz>>an_tranz>>luna_integral>>an_integral;
    }
    void afisare(ostream& out) const
    {
        contract::afisare(out);
        out<<" Data tranzactiei "<<luna_tranz<<'.'<<an_tranz<< " data platii integrale "<<luna_integral<<'.'<<an_integral;
    }

    double chirie()
    {
        int nrl=nr_luni(luna_tranz,an_tranz,luna_integral,an_integral);
        float chirie_lunara;
        float s=p->get_suprafata();
        float c=p->get_val_chirie();
        casa *ob = dynamic_cast <casa *> (this);
        //nu ne mai folosim de functia tip, folosim dynamic cast
        if(ob==NULL)
        {
            chirie_lunara = c*s;
        }

        else
        {
            float sc=p->get_suprafata_curte();
            chirie_lunara = c*(s+0.2*sc);
        }

        int disc=0;
        if(nrl>240)
        {
            cout<<"Nu pot fi mai mult de 240 de rate lunare!\n";
            return 0;
        }
        else if(nrl==0)
            disc=10;
            else if(nrl<60)
                disc=7;
                else if(nrl<120)
                    disc=5;
        return 240*chirie_lunara*(1-disc/100.0);
    }

    int get_luna_tranz()
    {
        return luna_tranz;
    }
    int get_an_tranz()
    {
        return an_tranz;
    }

    int get_luna_integral()
    {
        return luna_integral;

    }
    int get_an_integral()
    {
        return an_integral;
    }
};


class agentie_imobiliara
{
    int nr_p;
    vector <proprietate *> P;
    int nr_c;
    vector <contract * > C;

public:
    agentie_imobiliara() {nr_p=0; nr_c=0;}
    agentie_imobiliara(int nr_p1, vector <proprietate*> p1,int nr_c1,vector <contract* > c1)
    {
        nr_p=nr_p1;
        P=p1;
        nr_c=nr_c1;
        C=c1;
    }

    agentie_imobiliara(const agentie_imobiliara& ob)
    {
        nr_p=ob.nr_p;
        P=ob.P;
        nr_c=ob.nr_c;
        C=ob.C;
    }

    agentie_imobiliara& operator=(const agentie_imobiliara& ob)
    {
        if(this==&ob)return (*this);
        nr_p=ob.nr_p;
        P=ob.P;
        nr_c=ob.nr_c;
        C=ob.C;

        return (*this);
    }

    void adauga_proprietati(istream& fin, int n)
    {
        for(int i=1;i<=n;i++)
        {
            proprietate *p;
            char tip;
            fin>>tip;
            if(tip=='a')p=new apartament;
            else p=new casa;

            fin>>(*p);

            P.push_back(p);
        }

        nr_p+=n;
    }

    void adauga_contracte(istream& fin,int n)
    {
        for(int i=1;i<=n;i++)
        {
            contract *c;
            char tip;
            fin>>tip;
            if(tip=='i')c=new contract_inchiriere;
            else c=new contract_vanzare;

            fin>>(*c);

            C.push_back(c);
        }

        nr_c+=n;
    }

    void adauga_contract(contract * p)
    {
        C.push_back(p);
        nr_c++;
    }


    void proprietati_in_posesie()
    {
        vector <apartament> Ap;
        cout<<"CASE:\n";
        for(int i=0;i<nr_c;i++)
        {

            proprietate *p=C[i]->get_proprietate();
            casa * c=dynamic_cast <casa *> (p);
            if(c!=NULL)
                cout<<(*c)<<'\n';
            else
            {
                apartament * a=dynamic_cast <apartament *> (p);
                Ap.push_back((*a));
            }
        }

        cout<<"APARTAMENTE:\n";
        for(auto x : Ap)
            cout<<x<<' ';
    }

    void contracte_in_posesie()
    {
        vector <contract_vanzare> Vanzare;
        cout<<"CONTRACTE DE INCHIRIERE:\n";
        for(int i=0;i<nr_c;i++)
        {

            contract_inchiriere *ci=dynamic_cast <contract_inchiriere *> (C[i]);
            if(ci!=NULL)
                cout<<(*ci)<<'\n';
            else
            {
                contract_vanzare * con=dynamic_cast <contract_vanzare *> (C[i]);
                Vanzare.push_back((*con));
            }
        }

        cout<<"CONTRACTE DE VANZARE:\n";
        for(auto x : Vanzare)
            cout<<x<<' ';
    }


     void stare_proprietati(int luna_curenta,int an_curent)
    {
        vector <proprietate*> inchiriate;
        vector <proprietate*> vandute;

        //afisam proprietatile libere direct din for, iar pe cele inchiriate/ vandute le bagam in vectori si le afisam la iesirea din for
        cout<<"\nLIBERE:\n";
        for(int i=0;i<nr_c;i++)
        {
            contract_vanzare * con=dynamic_cast <contract_vanzare *> (C[i]);

            if(con!=NULL)  //daca c[i] e contract de vanzare
            {
                int luna=con->get_luna_tranz();
                int an=con->get_an_tranz();

                if(an<an_curent || (an==an_curent && luna<luna_curenta)) //s-a achitat deja
                    {
                        proprietate *p=C[i]->get_proprietate();
                        vandute.push_back(p);
                    }
            }
            else
            {
                contract_inchiriere *ci=dynamic_cast <contract_inchiriere *> (C[i]);
                int luna_i=ci->get_luna_inc();
                int an_i=ci->get_an_inc();
                int luna_s = ci->get_luna_sf();
                int an_s = ci->get_an_sf();
                proprietate *p=C[i]->get_proprietate();

                if(cmp_date(luna_i,an_i,luna_curenta,an_curent)<=0 && cmp_date(luna_curenta,an_curent,luna_s,an_s)<=0)
                {

                    inchiriate.push_back(p);
                }
                else cout<<*p<<'\n';
            }
        }

        cout<<"\nPROPRIETATI INCHIRIATE:\n";
        for(auto x : inchiriate)
            cout<<*x<<' ';
        cout<<"\nPROPRIETATI VANDUTE:\n";
        for(auto x : vandute)
            cout<<*x<<' ';
    }


    void suma_incasata(int luna_curenta,int an_curent)
    {
        double suma=0;
        for(int i=0;i<nr_c;i++)
        {
            contract_inchiriere *ci=dynamic_cast <contract_inchiriere*>(C[i]);

            if(ci!=NULL)
            {
                int luna_i=ci->get_luna_inc();
                int an_i=ci->get_an_inc();
                int luna_s = ci->get_luna_sf();
                int an_s = ci->get_an_sf();

                if(cmp_date(luna_i,an_i,luna_curenta,an_curent)<=0 && cmp_date(luna_curenta,an_curent,luna_s,an_s)<=0)//proprietatea e inchiriata in luna curenta
                    suma+=C[i]->chirie();
            }
            else
            {
                contract_vanzare *cv=dynamic_cast <contract_vanzare*>(C[i]);
                int luna_t=cv->get_luna_tranz();
                int an_t=cv->get_an_tranz();
                int luna_i=cv->get_luna_integral();
                int an_i=cv->get_an_integral();
                if(cmp_date(luna_t,an_t,luna_curenta,an_curent)<=0 && cmp_date(luna_curenta,an_curent,luna_i,an_i)<=0 )
                {
                    if(cmp_date(luna_t,an_t,luna_i,an_i)==0)suma+=C[i]->chirie();//este achitata in totalitate
                    else
                    {
                        int rate=nr_luni(luna_t,an_t,luna_i,an_i);
                        suma+=(C[i]->chirie()/(double)rate);
                    }
                }

            }
        }

        cout<<"\nSuma incasata in luna curenta: "<<suma<<'\n';
    }

};


///nu sunt facute in totalitate cerintele
int main()
{
    apartament a1("Roman",100,2,3,4);
    apartament a2("Brasov",140,30,2,2);
    apartament a3("Bucuresti",50,50,5,2);
    casa c1("Videle",50,10,1,10);
    casa c2("Onesti",300,30,2,200);

    agentie_imobiliara X;
    proprietate *pa1=new apartament;
    (*((apartament *)(pa1)))=a1;
    contract_inchiriere ci1("Popescu",pa1,2,2018,4,2019);
    proprietate *pa2=new casa;
    (*((casa *)(pa2)))=c1;
    contract_inchiriere ci2("Romica",pa2,3,2019,6,2019);

    contract *con1=new contract_inchiriere;
    *((contract_inchiriere*)con1)=ci1;

    contract *con2=new contract_inchiriere;
    *((contract_inchiriere*)con2)=ci2;
    X.adauga_contract(con1);
    X.adauga_contract(con2);
    X.contracte_in_posesie();
    X.proprietati_in_posesie();

    cout<<"_________________________________________";
    X.stare_proprietati(2,2019);
    X.suma_incasata(3,2019);
    return 0;
}
