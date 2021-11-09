#include <iostream>
#include <vector>
using namespace std;

class comanda
{
    string nume;
    string sursa;
    string destinatia;
public:
    comanda(string n="",string s="",string d="") : nume(n) , sursa(s) , destinatia(d) {}

};

class precomanda : public comanda
{
    int zi,luna,an;
    string ora;
public:
    precomanda(string n="",string s="",string d="",int z=0,int l=0,int a=0,string o="") : comanda(n,s,d) , zi(z) ,luna(l) , an(a) , ora(o) {}

};

class comanda_rent_leasing : public comanda
{
public:
    comanda_rent_leasing(string n="",string s="",string d="") : comanda(n,s,d) {}
};

class rent_a_car : public comanda_rent_leasing
{
    int zi_inc,luna_inc,an_inc;
    string ora_inc;
    int zi_fin,luna_fin,an_fin;
    string ora_fin;

public:
};

class leasing_operational : public comanda_rent_leasing
{
    bool RCA;
    bool rovigneta;
    bool schimb_anvelope;

public:

};

class comanda_control_designated : public comanda
{

};

class cost_control : public comanda_control_designated
{

};

class designated_driver : public comanda_control_designated
{
    string nume1;
    string nume2;
    string nr_lic1;
    string nr_lic2;
};

class companie
{
    vector <comanda> C;
    string nume;
    string cod_fiscal;
    int tarif_per_km;

public:
    companie() { tarif_per_km=0;}
    companie(vector <comanda> Com,string n,string cod,int tarif) :C(Com), nume(n) ,cod_fiscal(cod) , tarif_per_km(tarif) {}
};

class companie_precomanda : public companie
{
    vector <precomanda> P;
public:
    companie_precomanda() : companie() {}
    companie_precomanda(vector <comanda> Com,string n,string cod,int tarif ,vector <precomanda> pr) : companie(Com,n,cod,tarif) , P(pr) {}

};
class companie_cost_designated : public companie
{

};
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
