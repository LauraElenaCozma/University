#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
ifstream fin("date.in");
class referinta
{
public:
    virtual void citire(istream& in){}
    virtual void afisare(ostream& out) const{}

    friend istream& operator>>(istream& in,referinta& ob)
    {
        ob.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out,const referinta& ob)
    {
        ob.afisare(out);
        return out;
    }
    virtual ~referinta() = 0;

};

referinta::~referinta() {}

class tiparit : public referinta
{
protected:

    int nr_autori;
    vector <string> nume;
    vector <string> prenume;
    string titlu;
    int an_publicatie;

public:
    tiparit() : referinta() { nr_autori=0; an_publicatie=0;}
    tiparit(int nr_a , vector <string> n,vector <string> p,string t,int an) : referinta() , nr_autori(nr_a) , nume(n) , prenume(p) , titlu(t) , an_publicatie(an) {}
    tiparit(const tiparit & ob) : referinta(ob)
    {
        nr_autori=ob.nr_autori;
        nume=ob.nume;
        prenume=ob.prenume;
        titlu=ob.titlu;
        an_publicatie=ob.an_publicatie;
    }

    tiparit& operator=(const tiparit & ob)
    {
        referinta::operator=(ob);
        if(this==&ob)return (*this);
        nr_autori=ob.nr_autori;
        nume=ob.nume;
        prenume=ob.prenume;
        titlu=ob.titlu;
        an_publicatie=ob.an_publicatie;
        return (*this);
    }

    void citire(istream& in)
    {
        referinta::citire(in);
        in>>nr_autori;
        nume.resize(nr_autori);
        prenume.resize(nr_autori);
        for(int i=0;i<nr_autori;i++)
        {
            in>>nume[i];
            getline(in,prenume[i]);

        }
        getline(in,titlu);
        in>>an_publicatie;
    }

    void afisare(ostream& out) const
    {
        referinta::afisare(out);
        for(int i=0;i<nr_autori;i++)
            out<<nume[i]<<' '<<prenume[i]<<'\n';
        out<<"Titlu: "<<titlu<<" , "<<an_publicatie<<' ';
    }

    virtual ~tiparit() =0 ;
    int get_an()
    {
        return an_publicatie;
    }

    vector <string> get_nume()
   {
       return nume;
   }
};

tiparit::~tiparit() {}


class articol : public tiparit
{
    string nume_revista;
    int nr_revista;
    int nr_pag;

public:
    articol() : tiparit() {nr_revista=0; nr_pag=0;}
    articol(int nr_a , vector <string> n,vector <string> p,string t,int an,string nume_rev,int nr_rev,int nr_pg) : tiparit(nr_a,n,p,t,an)
    {
        nume_revista=nume_rev;
        nr_revista=nr_rev;
        nr_pag=nr_pg;
    }

    articol(const articol& ob) : tiparit(ob)
    {
        nume_revista=ob.nume_revista;
        nr_revista=ob.nr_revista;
        nr_pag=ob.nr_pag;
    }
    articol& operator=(const articol& ob)
    {
        tiparit::operator=(ob);
        if(this==&ob)return (*this);
        nume_revista=ob.nume_revista;
        nr_revista=ob.nr_revista;
        nr_pag=ob.nr_pag;
        return *this;
    }

    void citire(istream& in)
    {
        tiparit::citire(in);
        in.get();
        getline(in,nume_revista);
        in>>nr_revista>>nr_pag;

    }
    void afisare(ostream& out) const
    {
        tiparit::afisare(out);
        out<<nume_revista<<" revista nr: "<<nr_revista<<" cu "<<nr_pag<<" pagini.\n";
    }

};

class carte : public tiparit
{
    string nume_editura;
    string oras_editura;

public:
    carte() : tiparit() {}
    carte(int nr_a , vector <string> n,vector <string> p,string t,int an, string num,string o) : tiparit(nr_a,n,p,t,an) , nume_editura(num) , oras_editura(o) {}
    carte(const carte& ob) : tiparit(ob)
    {
        nume_editura=ob.nume_editura;
        oras_editura=ob.oras_editura;
    }

    carte& operator=(const carte& ob)
    {
        tiparit::operator=(ob);
        if(this==&ob)return (*this);
        nume_editura=ob.nume_editura;
        oras_editura=ob.oras_editura;
        return (*this);
    }

    void citire(istream& in)
    {
        tiparit::citire(in);
        in.get();
        getline(in,nume_editura);
        getline(in,oras_editura);

    }

    void afisare(ostream& out) const
    {
        tiparit::afisare(out);
        out<<" Editura: "<<nume_editura<<" , "<<oras_editura<<'\n';
    }

};
class electronic : public referinta
{
public:
    electronic() : referinta(){}
    electronic(const electronic& ob) : referinta(ob) {}
    electronic& operator=(const electronic& ob)
    {
        referinta::operator=(ob);
        ///if(this==&ob)return (*this);  oricum returnam *this
        return *this;
    }

    void citire(istream& in){referinta::citire(in);}
    void afisare(ostream& out) const {referinta::afisare(out);}

    virtual ~electronic() = 0;

};

electronic::~electronic() {}


class pagina_web : public electronic
{
    string nume_proprietar;
    string titlu;
    string url;
    int zi,luna,an;//data accesarii

public:
    pagina_web() : electronic()
    {
        zi=luna=an=0;
    }

    pagina_web(string n,string t,string url1,int z,int l,int a) : electronic() , nume_proprietar(n) , titlu(t) , url(url1) , zi(z) , luna(l) , an(a) {}

    pagina_web(const pagina_web& ob) : electronic(ob)
    {
        nume_proprietar=ob.nume_proprietar;
        titlu=ob.titlu;
        url=ob.url;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
    }

    pagina_web& operator=(const pagina_web& ob)
    {
        if(this==&ob)return (*this);
        electronic::operator=(ob);

        nume_proprietar=ob.nume_proprietar;
        titlu=ob.titlu;
        url=ob.url;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;

        return (*this);
    }

    void citire(istream& in)
    {
        electronic::citire(in);
        in.get();
        getline(in,nume_proprietar);
        getline(in,titlu);
        getline(in,url);
        in>>zi>>luna>>an;
    }

    void afisare(ostream& out) const
    {
        electronic::afisare(out);
        out<<nume_proprietar<<' '<<titlu<<' '<<url<<' '<<zi<<' '<<luna<<' '<<an<<'\n';
    }
    string get_nume_proprietar()
    {
        return nume_proprietar;
    }

};


class bibliografie
{
    vector <referinta *> R;
    int nr_ref;

public:
    friend istream& operator>>(istream& in,bibliografie& ob)
    {
        in>>ob.nr_ref;
        in.get();
        (ob.R).resize(ob.nr_ref);
        for(int i=0;i<ob.nr_ref;i++)
        {
            char tip;
            in>>tip;
            if(tip=='a') (ob.R)[i]=new articol;
            else if(tip=='c') (ob.R)[i]=new carte;
                 else if(tip=='w')(ob.R)[i]=new pagina_web;

            in>>*(ob.R[i]);
        }
        return in;
    }

    friend ostream& operator<<(ostream& out,const bibliografie& ob)
    {
        cout<<"____________________________________________________________________\nAfisarea tuturor referintelor:\n";
        vector <carte> C;
        vector <pagina_web> W;
        cout<<"Bibliografie:\n\nArticole:\n\n";
        for(int i=0;i<ob.nr_ref;i++)
        {
            articol *a=dynamic_cast<articol *>(ob.R[i]);
            if(a!=NULL)
                cout<<*a<<'\n';
            else
            {
                carte *c=dynamic_cast<carte *>(ob.R[i]);
                if(c!=NULL)
                    C.push_back(*c);
                else W.push_back(*((pagina_web *)ob.R[i]));
            }
        }
        cout<<"\nCarti:\n\n";
        for(auto x : C)
            cout<<x<<'\n';
        cout<<"\nWebografie:\n\n";
        for(auto x : W)
            cout<<x<<'\n';
    }

    void afisare_referinte_tiparit_dupa_an(int an)
    {
        cout<<"\n____________________________________________________________________\nAfisare referinte tiparit dupa an:\n";
        cout<<"Articole:\n\n";
        vector <carte> C;
        for(int i=0;i<nr_ref;i++)
        {
            tiparit * t=dynamic_cast <tiparit *> (R[i]);
            if(t!=NULL)
            {
                int an_t=t->get_an();
                if(an_t==an)
                {
                    carte *c=dynamic_cast <carte *>(R[i]);
                    if(c!=NULL)C.push_back(*c);
                    else cout<<*t;
                }
            }
        }
        cout<<"\nCarti:\n\n";
        for(auto x : C)
            cout<<x<<'\n';
    }

    void afisare_referinte_tiparit_dupa_nume(string nume_dat)
    {
        cout<<"\n____________________________________________________________________\nAfisare referinte tiparit dupa nume:\n\n";
        cout<<"Articole:\n\n";
        vector <carte> C;
        for(int i=0;i<nr_ref;i++)
        {
            tiparit * t=dynamic_cast <tiparit *> (R[i]);
            if(t!=NULL)
            {
                vector <string> nume=t->get_nume();

                for(unsigned int j=0;j<nume.size();j++)
                    if(nume[j]==nume_dat)
                    {
                        carte *c=dynamic_cast <carte *>(R[i]);
                        if(c!=NULL)C.push_back(*c);
                        else cout<<*t;
                    }
            }
        }
        cout<<"Carti:\n\n";
        for(auto x : C)
            cout<<x<<'\n';
    }

    void afisare_referinte_electronic_dupa_nume(string nume_dat)
    {
        cout<<"\n____________________________________________________________________\nAfisare referinte electronic dupa nume:\n";
        cout<<"\nWebografie:\n\n";
        for(int i=0;i<nr_ref;i++)
        {
            pagina_web* t=dynamic_cast <pagina_web *> (R[i]);
            if(t!=NULL)
            {
                string nume=t->get_nume_proprietar();
                if(nume==nume_dat)cout<<(*t)<<'\n';
            }
        }
    }
};

int main()
{
    articol a(2,{"Cozma","Manolache"},{"Laura Elena","Andrei"},"Pe aripile ploii",2018,"Bravo!",2,12);
    carte c(2,{"Cozma","Manolache"},{"Laura Elena","Andrei"},"Pe aripile ploii",2018,"Libris","Cluj Napoca");
    cout<<a<<c;
    pagina_web p("Floroiu Miruna","Concepte de OOP","www.sdgsd.com",2,3,2019);
    cout<<p;

    bibliografie x;
    fin>>x;
    cout<<x;
    x.afisare_referinte_tiparit_dupa_an(2018);
    x.afisare_referinte_tiparit_dupa_nume("Moromete");
    return 0;
}
