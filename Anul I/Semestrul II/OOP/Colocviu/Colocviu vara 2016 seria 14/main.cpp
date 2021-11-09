#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
ifstream fin("date.in");
class ingredient
{
    string denIng;
    double pretIng;
    int cantIng;
    string masIng;

public:
    ingredient(string den="", double pret=0, int cant=0, string mas="")
    {
        denIng=den;
        pretIng=pret;
        cantIng=cant;
        masIng=mas;
    }

    ingredient(const ingredient& ob)
    {

        denIng=ob.denIng;
        pretIng=ob.pretIng;
        cantIng=ob.cantIng;
        masIng=ob.masIng;

    }


    ingredient& operator=(const ingredient& ob)
    {
        if(this==&ob)return *this;
        denIng=ob.denIng;
        pretIng=ob.pretIng;
        cantIng=ob.cantIng;
        masIng=ob.masIng;

        return *this;
    }

    friend istream& operator>>(istream& in,ingredient& ob)
    {
        in>>ob.denIng>>ob.pretIng>>ob.cantIng>>ob.masIng;
        return in;
    }

    friend ostream& operator<<(ostream& out,const ingredient& ob)
    {
        out<<ob.denIng<<" Pret: "<<ob.pretIng<<" Cantitate: "<<ob.cantIng<<" "<<ob.masIng<<' ';
        return out;
    }

    ingredient& operator+(int x)
    {
        cantIng+=x;
        return (*this);
    }

    ingredient operator++(int )
    {
        ingredient i = (*this);
        cantIng++;
        return i;
    }

    ingredient& operator-=(double x)
    {
        pretIng-=x;
        return (*this);
    }

    void del()
    {
        cantIng=0;
        pretIng=0;
        denIng.clear();
        masIng.clear();
    }

    bool operator==(ingredient ob)
    {
        return (denIng==ob.denIng && pretIng==ob.pretIng && cantIng==ob.cantIng && masIng==ob.masIng);
    }

    double get_pretIng()
    {
        return pretIng;
    }



};


class pizza
{
    int codPizza;
    static int nr_pizza;
    string denPizza;
    int nrIngPizza;
    vector <ingredient> ingPizza;
    bool vegPizza;

public:
    pizza()
    {
        nr_pizza++;
        codPizza=nr_pizza;
        nrIngPizza=0;
        vegPizza=false;
    }
    pizza(string den,vector <ingredient> ing,int nring, bool veg)
    {
        nr_pizza++;
        codPizza=nr_pizza;
        denPizza=den;
        nrIngPizza=nring;
        ingPizza=ing;
        vegPizza=veg;
    }

    pizza(const pizza& ob)
    {
        nr_pizza++;
        codPizza=nr_pizza;
        denPizza=ob.denPizza;
        nrIngPizza=ob.nrIngPizza;
        ingPizza=ob.ingPizza;
        vegPizza=ob.vegPizza;
    }

    pizza& operator=(const pizza& ob)
    {
        if(this==&ob)return *this;
        denPizza.clear();
        ingPizza.clear();
        denPizza=ob.denPizza;
        nrIngPizza=ob.nrIngPizza;
        ingPizza=ob.ingPizza;
        vegPizza=ob.vegPizza;

        return (*this);
    }

    pizza& operator-(ingredient x)
    {
        vector<ingredient>::iterator poz;
        for(vector<ingredient>::iterator i=ingPizza.begin(); i!=ingPizza.end();i++)
            if((*i)==x)poz=i;
        ingPizza.erase(poz);
        return (*this);
    }
    pizza& operator+(ingredient x)
    {
        ingPizza.push_back(x);
        return (*this);
    }

    void nume(string s)
    {
        denPizza=s;
    }

    string nume()
    {
        return denPizza;
    }

    double pret()
    {
        double s=0;
        for(int i=0;i<nrIngPizza;i++)
            s+=ingPizza[i].get_pretIng();
        return 1.5*s;
    }

    virtual void citire(istream& in)
    {
        in>>denPizza>>nrIngPizza;
        ingPizza.resize(nrIngPizza);
        for(int i=0;i<nrIngPizza;i++)
            in>>ingPizza[i];
        in>>vegPizza;
    }

    friend istream& operator>>(istream& in, pizza& ob)
    {
        ob.citire(in);
        return in;
    }

    virtual void afisare(ostream& out) const
    {
        out<<" denumire pizza "<<denPizza<<" Pizza vegetariana: "<<vegPizza<<" \nIngrediente:\n";
        for(int i=0;i<nrIngPizza;i++)
            out<<ingPizza[i]<<"\n";
    }

    friend ostream& operator<<(ostream& out, const pizza& ob)
    {
        ob.afisare(out);
        return out;
    }
    void set_veg()
    {
        vegPizza=0;
    }
    void set_name(string n)
    {
         denPizza=n;
    }

    virtual char get_tip()
    {
        return 'p';
    }

    virtual double pret_ingrediente()
    {
        double s=0;
        for(int i=0;i<nrIngPizza;i++)
           s+=ingPizza[i].get_pretIng();

        return s;
    }

    virtual void afis_ingrediente()
    {
        for(int i=0;i<nrIngPizza;i++)
            cout<<ingPizza[i]<<'\n';
    }


};
int pizza::nr_pizza=0;

class pizzaSpec : public pizza
{
    vector <ingredient> ingPizza;
    int nrIngPizza;

public:
    pizzaSpec() :pizza() , nrIngPizza(0) { set_veg();}
    pizzaSpec(string den , vector <ingredient> ing , int nring , bool veg , vector <ingredient> ingsup , int nrIngSup ):  pizza(den,ing,nring,veg) , ingPizza(ingsup) , nrIngPizza(nrIngSup) { set_veg(); }
    pizzaSpec(const pizzaSpec& ob) : pizza(ob)
    {
        set_veg();
        ingPizza=ob.ingPizza;

        nrIngPizza=ob.nrIngPizza;

    }
    pizzaSpec& operator=(const pizzaSpec& ob)
    {
        pizza:: operator=(ob);
        if(this==&ob)return (*this);

        ingPizza=ob.ingPizza;
        nrIngPizza=ob.nrIngPizza;

        return (*this);
    }

    void citire(istream& in)
    {
        in>>nrIngPizza;
        ingPizza.resize(nrIngPizza);
        for(int i=0;i<nrIngPizza;i++)
            in>>ingPizza[i];
    }

    void afisare(ostream& out) const
    {
        pizza::afisare(out);
        out<<" SPECIALA : ";
        for(int i=0;i<nrIngPizza;i++)
            out<<ingPizza[i]<<'\n';
    }
    double pret_ingrediente()
    {
        double s=pizza::pret_ingrediente();
        for(int i=0;i<nrIngPizza;i++)
           s+=ingPizza[i].get_pretIng();

        return s;
    }
    char get_tip()
    {
        return 's';
    }

    void afis_ingrediente()
    {
        pizza::afis_ingrediente();
        for(int i=0;i<nrIngPizza;i++)
            cout<<ingPizza[i]<<'\n';
    }

};


class bautura
{
    string denBaut;
    double pretBaut;

public:

    bautura() {pretBaut=0;}
    bautura(string den, double pret) : denBaut(den),pretBaut(pret){}
    friend istream& operator>>(istream& in,bautura& ob)
    {
        in>>ob.denBaut>>ob.pretBaut;
        return in;
    }
    friend ostream& operator<<(ostream& out,const bautura& ob)
    {
        out<<ob.denBaut<<' '<<ob.pretBaut<<' ';
        return out;
    }

    double get_pretBaut()
    {
        return pretBaut;
    }
};

class ofSpec
{
    pizza * P;
    bautura b;
    double pret;

public:
    ofSpec() { P=NULL; pret = 0;}
    ofSpec(pizza * P1, bautura b1,double pret1)
    {
        if(P1->get_tip()=='p')
        {
            P=new pizza;
            *((pizza *)P)=*((pizza *)P1);
        }
        else
        {
            P=new pizzaSpec;
            *((pizzaSpec *)P)=*((pizzaSpec *)P1);

        }

        pret=pret1;
        b=b1;
    }

    ofSpec(const ofSpec& ob)
    {
        pizzaSpec * ps= dynamic_cast <pizzaSpec*>(ob.P);
        if(ps!=NULL)
            {P=new pizzaSpec; *((pizzaSpec *)P)=*(ps);}
        else {P=new pizza; (*P)=*(ob.P);}

        b=ob.b;
        pret = ob.pret;
    }

    ofSpec& operator=(const ofSpec& ob)
    {
        if(this==&ob)return (*this);

        pizzaSpec * ps= dynamic_cast <pizzaSpec*>(ob.P);
        if(ps!=NULL)
            {P=new pizzaSpec; *((pizzaSpec *)P)=*(ps);}
        else {P=new pizza; (*P)=*(ob.P);}

        b=ob.b;
        pret = ob.pret;

        return (*this);
    }

     friend istream& operator>>(istream& in,ofSpec& ob)
     {
         char tip;
         in>>tip;
         if(tip=='p')ob.P=new pizza;
         else ob.P=new pizzaSpec;
         in>>*(ob.P)>>ob.b>>ob.pret;
         return in;
     }

     friend ostream& operator<<(ostream& out, const ofSpec& ob)
     {
         out<<*(ob.P)<<" "<<ob.b<<" "<<ob.pret<<" lei\n";
         return out;
     }

     double get_pret()
     {
         return pret;
     }

     pizza * get_pizza()
     {
         return P;
     }

    bautura get_bautura()
    {
        return b;
    }
};


class pizzerie
{
    int nr_i;
    vector <ingredient> I;
    int nr_p;
    vector <pizza *> P;
    int nr_b;
    vector <bautura> B;
    int nr_o;
    vector <ofSpec> O;

public:
    pizzerie()
    {
        nr_i=0;
        nr_p=0;
        nr_b=0;
        nr_o=0;
    }
    pizzerie(int i,vector <ingredient> I1,int p,vector <pizza *> P1,int b,vector <bautura > B1,int o,vector <ofSpec> O1)
    {

        nr_i=i;
        nr_p=p;
        nr_b=b;
        nr_o=o;

        I=I1;
        B=B1;
        O=O1;
        P.resize(nr_p);
        for(int i=0;i<nr_p;i++)
        {
            pizzaSpec *aux=dynamic_cast <pizzaSpec *> (P1[i]);

            if(aux!=NULL)
            {
                P[i]=new pizzaSpec;
                *((pizzaSpec *)P[i])=*((pizzaSpec *)P1[i]);
            }
            else
            {
                P[i]=new pizza;
                *((pizza *)P[i])=*(P1[i]);
            }
        }

    }

    pizzerie& operator=(const pizzerie& ob)
    {
        if(this==&ob)return *this;
        nr_i=ob.nr_i;
        nr_b=ob.nr_b;
        nr_p=ob.nr_p;
        nr_o=ob.nr_o;

        O=ob.O;
        I=ob.I;
        B=ob.B;

        P.resize(nr_p);
        for(int i=0;i<nr_p;i++)
        {
            pizzaSpec *aux=dynamic_cast <pizzaSpec *> (ob.P[i]);

            if(aux!=NULL)
            {
                P[i]=new pizzaSpec;
                *((pizzaSpec *)P[i])=*((pizzaSpec *)ob.P[i]);
            }
            else
            {
                P[i]=new pizza;
                *((pizza *)P[i])=*(ob.P[i]);
            }
        }

        return (*this);

    }
    void citire_ingrediente()
    {
        fin>>nr_i;
        I.resize(nr_i);
        for(int i=0;i<nr_i;i++)
            fin>>I[i];
    }
    void citire_bauturi()
    {
        fin>>nr_b;
        B.resize(nr_b);
        for(int i=0;i<nr_b;i++)
            fin>>B[i];
    }

    void adaug_pizza(pizza * p1)
    {
        P.push_back(p1);
        nr_p++;
    }

    void adaug_oferta(pizza *p1,bautura b,double pret)
    {
        nr_o++;
        O.push_back(ofSpec(p1,b,pret));

    }
    void afisare_ingrediente()
    {
        cout<<"\nINGREDIENTE:\n";
        for(int i=0;i<nr_i;i++)
            cout<<I[i]<<'\n';
    }

    void afis_pizza()
    {
        vector <pizzaSpec> PS;
        cout<<"\nPIZZA:\n";
        for(int i=0;i<nr_p;i++)
        {
            pizzaSpec * aux=dynamic_cast<pizzaSpec *> (P[i]);

            if(aux!=NULL)
                PS.push_back(*aux);
            else cout<<*(P[i])<<' ';

        }
        cout<<"\nPIZZA SPECIALA:\n";
        for(int i=0;i<PS.size();i++)
            cout<<PS[i]<<' ';
    }

    void afis_oferte_speciale()
    {
        cout<<"\nOFERTE SPECIALE:\n";
        for(int i=0;i<nr_o;i++)
        {
            cout<<O[i]<<'\n';
            cout<<"Castig: ";
            double s=O[i].get_pret();
            pizza *p=O[i].get_pizza();
            s-=p->pret_ingrediente();
            bautura b=O[i].get_bautura();
            s-=b.get_pretBaut();

            cout<<s<<'\n'<<'\n';

        }
    }

    void afis_ingrediente(pizza * p)
    {
        p->afis_ingrediente();
    }


};
int main()
{
    vector <ingredient> lista;
    lista.push_back(ingredient("piept de pui",15,1,"kg"));
    lista.push_back(ingredient("sare",0.75,10,"gram"));
    lista.push_back(ingredient("salam",1.5,5,"felii"));
    lista.push_back(ingredient("salam",1.5,5,"felii"));
    lista.push_back(ingredient());
    ingredient i1("sunca",3,5,"felii");


    pizza p1("Rustica",lista,4,false);
    pizza p2=p1;
    pizza * point1=&p1;
    pizza * point2=&p2;


    vector <pizza *> P;


    vector <bautura> B;
    B.push_back(bautura("cola",3.5));
    B.push_back(bautura("apa",1.5));
    B.push_back(bautura("sampanie",20));

    vector <ofSpec> O;

    pizzerie X(5,lista,0,P,3,B,0,O);

    X.adaug_pizza(point1);
    X.adaug_pizza(point2);

    lista.pop_back();
    vector <ingredient > suplimentar;
    suplimentar.push_back(i1);
    pizzaSpec p3("Quatroformaggi",lista,4,true,suplimentar,1);
    pizzaSpec *point3=&p3;
    X.adaug_pizza(point3);
    X.afisare_ingrediente();
    cout<<'\n';
    X.afis_pizza();

    X.adaug_oferta(point1,B[1],27);
    X.adaug_oferta(point3,B[0],25);

    X.afis_oferte_speciale();

    cout<<"\nIngrediente pizza point3:\n";
    X.afis_ingrediente(point3);
   /* fin>>lista[2];
    cout<<lista[0]<<'\n'<<lista[1]<<'\n'<<lista[2]<<'\n'<<lista[3]<<'\n'<<lista[4]<<'\n';
    lista[3]=lista[3]+3;
    lista[1]++;
    lista[0]-=2.5;
    //lista[2].del();
    cout<<'\n'<<lista[0]<<'\n'<<lista[1]<<'\n'<<lista[2]<<'\n'<<lista[3]<<'\n'<<lista[4]<<'\n';

    pizza p1("Rustica",lista,4,false);
    pizza p2=p1,p3;
    p2=p2-lista[2];
    p3=p2+i1;
    p3.nume("Prosciuto");
    cout<<" Pizza "<<p1.nume()<<p1.pret()<<"lei\n";
    cout<<" Pizza "<<p2.nume()<<p2.pret()<<"lei\n";
    cout<<" Pizza "<<p3.nume()<<p3.pret()<<"lei\n";*/


    return 0;
}
