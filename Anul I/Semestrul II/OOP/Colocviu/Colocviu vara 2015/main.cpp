#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
ifstream fin("date.in");

struct data
{
    int zi,luna,an;
};

class produs
{
    string denumire;
    string unit;
    int perisabil;
    float discount;

public:
    produs()
    {
        perisabil=0;
        discount=0;
    }
    produs(string denumire_produs,string unitate_de_masura,int perioada_de_valabilitate,float reducere)
    {
        denumire=denumire_produs;
        unit=unitate_de_masura;
        perisabil=perioada_de_valabilitate;
        discount=reducere;
    }

    produs(const produs& ob)
    {
        denumire=ob.denumire;
        unit=ob.unit;
        perisabil=ob.perisabil;
        discount=ob.discount;
    }

    produs& operator=(const produs& ob)
    {
        denumire=ob.denumire;
        unit=ob.unit;
        perisabil=ob.perisabil;
        discount=ob.discount;
        return (*this);
    }

    friend istream& operator>>(istream& in,produs& ob)
    {
        in>>ob.denumire;
        in>>ob.unit>>ob.perisabil>>ob.discount;
        return in;
    }
    friend ostream& operator<<(ostream& out,const produs& ob)
    {
        out<<"\nDenumire: "<<ob.denumire<<" Unitate de masura: "<<ob.unit<<" Perioada de valabilitate: "<<ob.perisabil<<" Discount: "<<ob.discount;
        return out;
    }

    int get_perisabil()
    {
        return perisabil;
    }
    bool operator==(produs p1)
    {
        if(denumire==p1.denumire)return 1;
        return 0;
    }
    float get_discount()
    {
        return discount;
    }

};

class lot
{
    produs p;
    float cantitate;
    data d;
    float pret;

public:
    lot() :p()
    {
        cantitate=0;
        d.zi=0;
        d.luna=0;
        d.an=0;
        pret=0;
    }

    lot(string denumire_produs,string unitate_de_masura_produs,int valabilitate,float reducere,float cantitate_produs,data venire,float pret_prod) : p(denumire_produs,unitate_de_masura_produs,valabilitate,reducere)
    {
        cantitate=cantitate_produs;
        d=venire;
        pret=pret_prod;
    }

    lot(const lot& ob)
    {
        p=ob.p;
        cantitate=ob.cantitate;
        d=ob.d;
        pret=ob.pret;
    }

    friend istream& operator>>(istream& in,lot& ob)
    {
        in>>ob.p;
        in>>ob.cantitate>>ob.d.zi>>ob.d.luna>>ob.d.an>>ob.pret;
        return in;
    }

    friend ostream& operator<<(ostream& out,const lot& ob)
    {
        out<<ob.p<<" Cantitate: "<<ob.cantitate<<"  Data intrarii in magazin: "<<ob.d.zi<<'.'<<ob.d.luna<<'.'<<ob.d.an<<" Pret: "<<ob.pret<<'\n';
        return out;
    }

    data get_data()
    {
        return d;
    }

    float get_cantitate()
    {
        return cantitate;
    }

    int get_valabilitate()
    {
        return p.get_perisabil();
    }
    float get_pret()
    {
        return pret;
    }
    produs get_produs()
    {
        return p;
    }

};


void add_produs(int index,produs& p,vector <pair<int,produs> > &P)
{
    P.push_back({index,p});
}


void afis_produse_comercializate(vector <pair<int,produs> > prod)
{
    for(auto i : prod)
    {
        cout<<i.second<<'\n';
    }
}

void add_lot(const lot& L,vector <lot>& loturi)
{
    loturi.push_back(L);
}

int cmp_date(data d1,data d2)
{
    if(d1.an>d2.an)return -1;
    else if(d1.an<d2.an)return 1;
         else
         {
             if(d1.luna>d2.luna)return -1;
             else if(d1.luna<d2.luna)return 1;
                  else
                  {
                      if(d1.zi>d2.zi)return -1;
                      else if(d1.zi<d2.zi)return 1;
                           else return 0;
                  }
         }
}

void afis_loturi_intre_2_date(data d1,data d2, vector <lot> loturi)
{
    for(auto i : loturi)
        if(cmp_date(d1,i.get_data())>=0 && cmp_date(i.get_data(),d2)>=0)
            cout<<i<<'\n';
}

void afis_loturi(vector <lot> loturi)
{
    for(auto i : loturi)
            cout<<i<<'\n';
}

void afis_lot_ce_poate_fi_comercializat(data curenta,vector <lot> loturi)
{
    for(auto i : loturi)
    {
        if(i.get_cantitate()!=0)   //daca sunt nevide
        {
            int valab=i.get_valabilitate();
            if(valab!=0)//produsul nu e perisabil
            {
                //calculam data expirarii
                data d=i.get_data();
                if(d.zi+valab<=30)d.zi=d.zi+valab;
                else
                {
                    int luni=valab/30;
                    if(d.luna+luni<=12)d.luna+=luni;
                    else
                    {
                        int ani=(d.luna+luni)/12;
                        d.an+=ani;

                    }
                }

                if(cmp_date(d,curenta)<=0)cout<<d.zi<<'.'<<d.luna<<'.'<<d.an<<' '<<i;
            }
            else cout<<i;
        }
    }
}

void vinde(vector <pair<int,produs> > P,vector <lot> L,produs prod,data curenta,float cantitate)
{
    float pret_minim=10000000;
    int pozitie=-1;
    vector <pair <float,float> > disponibil;
    for(int i=0;i<P.size();i++)
        if(P[i].second==prod && P[i].first!=-1)  //!=-1 adica avem un lot din acel produs
    {

        //calculam daca produsul nu e expirat
        int valab=P[i].second.get_perisabil();
        data d;
        if(valab!=0)//produsul nu e perisabil
        {
            //calculam data expirarii
            d=L[P[i].first].get_data();
            if(d.zi+valab<=30)d.zi=d.zi+valab;
            else
            {
                int luni=valab/30;
                if(d.luna+luni<=12)d.luna+=luni;
                else
                {
                    int ani=(d.luna+luni)/12;
                    d.an+=ani;

                }
            }

        }
        if(L[P[i].first].get_cantitate()>=cantitate && (valab==0 || cmp_date(d,curenta)<=0))
        {
            if(L[P[i].first].get_pret()<=pret_minim)
            {
                pret_minim=L[P[i].first].get_pret();
                pozitie=P[i].first;
            }
        }
        else if(valab==0 || cmp_date(d,curenta)<=0)
        disponibil.push_back({L[P[i].first].get_cantitate(),L[P[i].first].get_pret()});
    }

    if(pozitie!=-1)
    {
        cout<<"\nExista un lot disponibil. Pretul total este: ";
        produs x=L[pozitie].get_produs();
        float disc=x.get_discount();
        if(disc==0)cout<<L[pozitie].get_pret()*cantitate;
        else cout<<L[pozitie].get_pret()*cantitate*(1-disc);   //calculeaza cu tot cu discount
    }
    else
    {
        for(int i=0;i<disponibil.size();i++)
            cout<<"\nCantitate "<<disponibil[i].first<<" Pret "<<disponibil[i].second<<'\n';
    }

    if(!disponibil.size())cout<<"\nNu se poate vinde nimic.";

}
int main()
{
    produs p1,p2("cirese","bucata",30,0.1),p3=p2,p4=p1,p5;
    p5=p2;
    //cout<<p1<<p2<<p3<<p4<<p5;
    lot l1,l2("cirese","kg",30,0.3,300,{12,6,2018},15),l3=l2,l4;
    l4=l1;
   // cout<<l1<<l2<<l3<<l4;*/

    vector <pair<int,produs> > prod;
    vector <lot> loturi;

    int n;
    fin>>n;
    loturi.resize(n);
    for(int i=0;i<n;i++)
    {
        fin>>loturi[i];
      //  cout<<loturi[i];
        add_produs(i,(produs&)loturi[i],prod);
    }
    add_produs(-1,p2,prod);
   // afis_produse_comercializate(prod);
    add_lot(l2,loturi);
    afis_loturi(loturi);
    cout<<"__________"<<'\n';
    //afis_loturi_intre_2_date({23,1,2019},{23,6,2019},loturi);


    fin.close();
   // afis_lot_ce_poate_fi_comercializat({3,6,2019},loturi);
   produs p10=loturi[1].get_produs();
   vinde(prod,loturi,p10,{3,6,2019},30);
    return 0;
}
