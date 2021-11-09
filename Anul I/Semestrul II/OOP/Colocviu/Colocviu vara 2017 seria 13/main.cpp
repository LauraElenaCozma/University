#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <sstream>
using namespace std;
ifstream fin("date.in");

class student
{
protected:
    static int nr_student;
    int nr_inregistrare;
    string cod_inregistrare;

    string nume;
    string CI;
    float medie_bac;
    float nota_proba;

    float medie_admitere;

public:
    virtual void calcul_medie() = 0;

    student(string n="",string C="",float bac=0, float np=0)
    {
        nr_student++;
        nr_inregistrare=nr_student;

        nume=n;
        CI=C;
        medie_bac=bac;
        nota_proba=np;
    }

    virtual void citire(istream& in)
    {
        getline(in,nume);
        in>>CI;
        in>>medie_bac>>nota_proba;
    }
    virtual void afisare(ostream& out) const
    {
        out<<cod_inregistrare<<' '<<nume<<' '<<CI<<" Medie bac: "<<medie_bac<<" Nota proba: "<<nota_proba<<" Medie admitere: "<<medie_admitere<<' ';
    }
    friend istream& operator>>(istream& in,student& ob)
    {
        ob.citire(in);
        return in;
    }

    friend ostream& operator<<(ostream& out,const student& ob)
    {
        ob.afisare(out);
        return out;
    }
    float get_medie_admitere()
    {
        return medie_admitere;
    }
};

int student::nr_student;


class prima_fac : public student
{
public:

    prima_fac(string n="",string C="",float bac=0, float np=0) :student(n,C,bac,np) {}

    void citire(istream& in)
    {
        student::citire(in);
    }
    void afisare(ostream& out) const
    {
        student::afisare(out);
    }
};



class ID_prima : public prima_fac
{
    float nota_mate;

public:
    void calcul_medie()
    {
        medie_admitere=0.6*nota_proba+0.4*nota_mate;
    }
    ID_prima(string n="",string C="",float bac=0, float np=0,float nota_mat=0) : prima_fac(n,C,bac,np) , nota_mate(nota_mat)
    {
        calcul_medie();
        string nr;
        ostringstream temp;
        temp<<nr_inregistrare;
        nr=temp.str();
        cod_inregistrare="ID_"+nr;
    }
    void citire(istream& in)
    {
        student::citire(in);
        in>>nota_mate;
        calcul_medie();
    }
    void afisare(ostream& out) const
    {
        student::afisare(out);
        out<<" Nota mate: "<<nota_mate;
    }


};

class IF_prima : public prima_fac
{
public:

    void calcul_medie()
    {
        medie_admitere=0.8*nota_proba+0.2*medie_bac;
    }

    IF_prima(string n="",string C="",float bac=0, float np=0) : prima_fac(n,C,bac,np)
    {
        ostringstream temp;
        temp<<nr_inregistrare;
        cod_inregistrare=temp.str();
        calcul_medie();
    }

    void citire(istream& in)
    {
        prima_fac::citire(in);
        calcul_medie();
    }

    void afisare(ostream& out) const
    {
        prima_fac::afisare(out);
    }

};


class a_doua_facultate : public student
{
    float medie_absolvire;
public:
    void calcul_medie()
    {
        medie_admitere=0.6*nota_proba+0.6*medie_absolvire;
    }
    a_doua_facultate(string n="",string C="",float bac=0, float np=0,float med_absolv=0) :student(n,C,bac,np) ,medie_absolvire(med_absolv) {}
    void citire(istream& in)
    {
        student::citire(in);
        in>>medie_absolvire;
    }
    void afisare(ostream& out) const
    {
        student::afisare(out);
        out<<" Medie absolvire: "<<medie_absolvire;
    }

};


class ID_a_doua : public a_doua_facultate
{
public:
    void calcul_medie()
    {
        a_doua_facultate::calcul_medie();
    }
    ID_a_doua(string n="",string C="",float bac=0, float np=0,float med_absolv=0) : a_doua_facultate(n,C,bac,np,med_absolv)
    {
        calcul_medie();

        ostringstream temp;
        temp<<nr_inregistrare;
        string s=temp.str();
        cod_inregistrare="ID2_"+s;
    }

    void citire(istream& in)
    {
        a_doua_facultate::citire(in);
        calcul_medie();
    }

    void afisare(ostream& out) const
    {
        a_doua_facultate::afisare(out);
    }

};

class IF_a_doua : public a_doua_facultate
{
public:
    void calcul_medie()
    {
        a_doua_facultate::calcul_medie();
    }
    IF_a_doua(string n="",string C="",float bac=0, float np=0,float med_absolv=0) : a_doua_facultate(n,C,bac,np,med_absolv)
    {
        calcul_medie();

        ostringstream temp;
        temp<<nr_inregistrare;
        string s=temp.str();
        cod_inregistrare="ID2_"+s;
    }

    void citire(istream& in)
    {
        a_doua_facultate::citire(in);
        calcul_medie();
    }

    void afisare(ostream& out) const
    {
        a_doua_facultate::afisare(out);
    }

};

void afis_admisi(vector <student*> S,int nr_s)
{
    for(int i=0;i<nr_s;i++)
        if(S[i]->get_medie_admitere()>=5)cout<<*(S[i])<<'\n';
}

int main()
{
    vector <student *> S;
    int nr_s;
    fin>>nr_s;
    S.resize(nr_s);
    string tip;
    for(int i=0;i<nr_s;i++)
    {
        fin>>tip;
        fin.get();
        if(tip=="ID1") S[i]=new ID_prima;
        else if(tip=="IF1") S[i]=new IF_prima;
             else if(tip=="ID2") S[i]=new ID_a_doua;
                  else if(tip=="IF2")S[i]=new IF_a_doua;

        fin>>*(S[i]);

    }

    for(int i=0;i<nr_s;i++)
        cout<<*(S[i])<<'\n';

    cout<<'\n';
    afis_admisi(S,nr_s);
    return 0;
}
