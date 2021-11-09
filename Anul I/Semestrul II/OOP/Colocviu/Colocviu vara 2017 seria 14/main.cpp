#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;
ifstream fin("date.in");
struct data
{
    int zi,luna,an;
};

const data curenta={12,5,2019};


class date_participant
{
    char* nume;
    char* CNP;
    int varsta;

public:
    date_participant() { nume=new char[1]; nume[0]='\0';CNP=new char[1]; CNP[0]='\0';varsta=0; }
    date_participant(char* n, char* c)
    {
        strcpy(nume,n);
        strcpy(CNP,c);
        varsta=calcul_varsta();
    }

    date_participant(const date_participant& ob)
    {
        nume=new char[strlen(ob.nume)+1];
        strcpy(nume,ob.nume);
        CNP=new char[strlen(ob.CNP)+1];
        strcpy(CNP,ob.CNP);
        varsta=ob.varsta;
    }

    date_participant& operator=(const date_participant& ob)
    {
        nume=new char[strlen(ob.nume)+1];
        strcpy(nume,ob.nume);
        CNP=new char[strlen(ob.CNP)+1];
        strcpy(CNP,ob.CNP);
        varsta=ob.varsta;
        return (*this);
    }


    int calcul_varsta()
    {

        data d;
        d.zi=(CNP[5]-'0')*10+(CNP[6]-'0');
        d.luna=(CNP[3]-'0')*10+(CNP[4]-'0');
        if(CNP[0]=='1' || CNP[0]=='2')d.an=1900;
        else d.an=2000;
        d.an+=(CNP[1]-'0')*10+(CNP[2]-'0');

        int varsta=curenta.an-d.an;

        if(d.luna>curenta.luna)varsta--;
        else if(d.luna==curenta.luna && d.zi>curenta.zi)varsta--;

        return varsta;

    }

    friend istream& operator>>(istream& in,date_participant& ob)
    {
        char nume[100],cnp[20];
        in.getline(nume,100);
        ob.nume=new char[strlen(nume)+1];
        strcpy(ob.nume,nume);
        in.getline(cnp,15);
        ob.CNP=new char[strlen(cnp)+1];
        strcpy(ob.CNP,cnp);
        ob.varsta=ob.calcul_varsta();

        return in;
    }

    friend ostream& operator<<(ostream& out, const date_participant & ob)
    {
        out<<ob.nume<<' '<<ob.CNP<<' '<<ob.varsta<<'\n';
        return out;
    }

    char * get_nume()
    {
        return nume;
    }

    int get_varsta()
    {
        return varsta;
    }
};


class activitate
{
protected:

    char* denumire;
    data inceput;
    int nr_participanti;
    vector <date_participant> participant;
    vector <int> rezultate;


public:
    activitate()
    {
        denumire=new char[1]; denumire[0]='\0';
        inceput.zi=0; inceput.luna=0; inceput.an=0; nr_participanti=0;
    }

    activitate(char* denum, data inc,int nrp, vector <date_participant> P,vector <int>rez)
    {
        strcpy(denumire,denum);
        inceput=inc;
        participant=P;
        nr_participanti=nrp;
        rezultate=rez;
    }

    virtual void citire(istream& in) =0;

    friend istream& operator>>(istream& in, activitate & ob)
    {
        ob.citire(in);
        return in;
    }

    virtual void afisare(ostream& out) const = 0;

    friend ostream& operator<<(ostream& out,const activitate& ob)
    {
        ob.afisare(out);
        return out;
    }

    void adaug_participant(const date_participant& p)
    {
        nr_participanti++;
        participant.push_back(p);
    }

    data get_data()
    {
        return inceput;
    }
    int get_nr_participanti()
    {
        return nr_participanti;
    }

    vector <date_participant> get_participant()
    {
        return participant;
    }

    vector <int> get_rezultate()
    {
        return rezultate;
    }


};

void activitate::afisare(ostream& out) const
    {
        out<<"Denumire "<<denumire<<" Data inceput "<<inceput.zi<<'.'<<inceput.luna<<'.'<<inceput.an<<" Nr participanti "<<nr_participanti<<'\n';
        for(int i=0;i<nr_participanti;i++)
           {
               out<<participant[i]<<rezultate[i]<<'\n';
           }
    }

void activitate::citire(istream& in)
{
        char denum[100];
        in.getline(denum,100);
        strcpy(denumire,denum);
        in>>inceput.zi>>inceput.luna>>inceput.an;
        in>>nr_participanti;
        in.get();
        participant.resize(nr_participanti);
        rezultate.resize(nr_participanti);
        for(int i=0;i<nr_participanti;i++)
            in>>participant[i];
         for(int i=0;i<nr_participanti;i++)
                in>>rezultate[i];
        in.get();

}

class curs: public activitate
{
    bool profesor;
    int nr_credite;
    int durata;

public:
    curs()  : activitate()
    {
        profesor=0;
        nr_credite=0;
        durata=0;
    }
    curs(bool p,int nrc,int dur,char* denum, data inc,int nrp, vector <date_participant> P,vector <int>rez) : activitate(denum,inc,nrp,P,rez)
    {
        profesor=p;
        nr_credite=nrc;
        durata=dur;
    }

    curs(const curs& ob) : activitate((const activitate&)ob)
    {
        profesor=ob.profesor;
        nr_credite=ob.nr_credite;
        durata=ob.durata;
    }

    curs& operator=(const curs& ob)
    {
        activitate::operator=(ob);
        profesor=ob.profesor;
        nr_credite=ob.nr_credite;
        durata=ob.durata;
        return (*this);
    }

    void citire(istream& in)
    {
        activitate::citire(in);
        in>>profesor>>nr_credite>>durata;
    }

    void afisare(ostream& out) const
    {
        activitate::afisare(out);
        out<<" Nr credite "<<nr_credite<<" durata "<<durata;
        out<<'\n';
    }
};


class concurs : public activitate
{
    int nr_premianti;
    vector <date_participant> premiant;

public:
    concurs()   :activitate()
    {
        nr_premianti=0;
    }
    concurs(char* denum, data inc,int nrp, vector <date_participant> P, int nrprem, vector <date_participant> L,vector<int> rez)   : activitate(denum,inc,nrp,P,rez)
    {
        nr_premianti=nrprem;
        premiant=L;
    }


    concurs(const concurs& ob) : activitate((const activitate&)ob)
    {
        nr_premianti=ob.nr_premianti;
        premiant=ob.premiant;
    }

    concurs& operator=(const concurs& ob)
    {
        activitate::operator=(ob);
        nr_premianti=ob.nr_premianti;
        premiant=ob.premiant;
        return (*this);
    }

    virtual void citire(istream& in)
    {
        activitate:: citire(in);
        nr_premianti=0;
    }

    virtual void afisare(ostream& out) const
    {
        activitate::afisare(out);
        out<<"Premianti:\n";
        for(int i=0;i<nr_premianti;i++)
            out<<premiant[i]<<'\n';
    }

    void set_nr_premianti(int x)
    {
        nr_premianti=x;
    }

    void adaug_premiant(date_participant p)
    {
        premiant.push_back(p);
    }

    vector <date_participant> get_premiant()
    {
        return premiant;
    }
    int get_nr_premianti()
    {
        return nr_premianti;
    }
};

class concurs_online:public concurs
{
    string site;
    int durata;

public:
    concurs_online() : concurs()
    {
        durata=0;
    }

    concurs_online(string s,int d,char* denum, data inc,int nrp, vector <date_participant> P, int nrprem, vector <date_participant> L,vector <int> rez) : concurs(denum,inc,nrp,P,nrprem,L,rez)
    {
        site=s;
        durata=d;
    }

    concurs_online(const concurs_online& ob)  : concurs((const concurs&)ob)
    {
        site=ob.site;
        durata=ob.durata;
    }

    concurs_online& operator=(const concurs_online& ob)
    {
        concurs::operator=(ob);
        site=ob.site;
        durata=ob.durata;
        return (*this);
    }

    void citire(istream& in)
    {
        concurs::citire(in);
        in>>site;
        in>>durata;
    }

    void afisare(ostream& out) const
    {
        concurs::afisare(out);
        out<<" Site ul este: "<<site<<" durata concursului online este: "<<durata;
    }
};

class concurs_offline : public concurs
{
public:
    void citire(istream& in)
    {
        concurs::citire(in);
    }

    void afisare(ostream& out) const
    {
        concurs::afisare(out);
    }

};
void citire_activitati(int &n,vector <pair<char ,activitate *> > &A)
{
    fin>>n;
    fin.get();
    A.resize(n);
    char tip;
    for(int i=0;i<n;i++)
    {
        fin>>tip;
        fin.get();
        /// u = curs n=concurs online f=concurs offline
        if(tip=='u')A[i].second=new curs;
        else if(tip=='n')A[i].second=new concurs_online;
             else A[i].second=new concurs_offline;
        fin>>*(A[i].second);
        A[i].first=tip;
    }


}

bool cmp(date_participant a,date_participant b)
{
    string na=a.get_nume();
    string nb=b.get_nume();
    return (nb>na);
}

void afis_participanti_in_zi_data(data d,vector <pair<char ,activitate *> > A,int n)
{
    vector <date_participant > aux;
    for(int i=0;i<n;i++)
        {
            data date=(A[i].second)->get_data();
            if(date.zi==d.zi && date.an==d.an && date.luna==d.luna)
                {
                    int nrp=(A[i].second)->get_nr_participanti();
                    vector <date_participant> p=((activitate*)A[i].second)->get_participant();
                   for(int j=0;j<nrp;j++)
                     {
                         aux.push_back(p[j]);
                     }
                }
        }


    sort(aux.begin(),aux.end(),cmp);

    for(int i=0;i<aux.size();i++)
        cout<<aux[i]<<'\n';

}


void afis_pe_activitate(char tip,vector <pair<char ,activitate *> > A,int n)
{
    vector <date_participant > aux;


    for(int i=0;i<n;i++)
        if(A[i].first==tip)
    {
        vector <date_participant> p=(A[i].second)->get_participant();

        for(int j=0;j<p.size();j++)
            aux.push_back(p[j]);
    }

    sort(aux.begin(),aux.end(),cmp);
    for(int i=0;i<aux.size();i++)
        cout<<aux[i]<<'\n';
}
//lipseste rezolvarea ultimei cerinte, intrucat am uitat sa fac pun si optiunea daca e profesor sau nu

bool cmp_rezultat(int r1,int r2)
{
    return (r1>r2);
}

void afis_premianti(vector <pair<char ,activitate *> > A, int n)
{
    vector <date_participant > prof;
    for(int i=0;i<n;i++)
    {
        vector <date_participant> p=(A[i].second)->get_participant();
        vector <int> r=(A[i].second)->get_rezultate();

        for(int j=0;j<p.size();j++)
        {
            int varsta=p[j].get_varsta();
            if(varsta>18 && A[i].first=='u')  prof.push_back(p[j]);
        }

        for(int j=0;j<p.size()-1;j++)
            for(int k=j+1;k<p.size();k++)
                if(r[j]<r[k]){swap(r[j],r[k]); swap(p[j],p[k]);}

        int dim=(p.size()<4)?p.size():4;

        if(A[i].first=='n' || A[i].first=='f')
        {
            for(int j=0;j<dim;j++)
            {

                ((concurs *)A[i].second)->adaug_premiant(p[j]); //nu functioneaza
                cout<<p[j]<<' '<<r[j]<<'\n';

            }
            ((concurs *)A[i].second)->set_nr_premianti(dim);

        }

    }

    sort(prof.begin(),prof.end(),cmp);

    cout<<"__Profesori__\n";
    for(int i=0;i<prof.size();i++)
        cout<<prof[i]<<' ';

}
int main()
{
    vector <pair<char ,activitate *> > A;
    int n;
    cout<<"------------AFISAREA ACTIVITATILOR TOTALE-----------\n";
    citire_activitati(n,A);
    for(int i=0;i<n;i++)
        cout<<A[i].first<<' '<<*(A[i].second)<<'\n';

    int opt, nr_act;
    do
    {
        cout<<"\n1 : Adauga participanti.\n";
        cout<<"\n2 : Afiseaza activitate specifica.\n";
        cout<<"\n3 : Afiseaza alfabetic pe activitati\n";
        cout<<"\n4 : Afiseaza la o anumita data\n";
        cout<<"\n5 : Afiseaza premianti si profesori\n";
        cout<<"\n Optiunea: ";
        cin>>opt;

        switch(opt)
        {
        case 1:
            cout<<"\nLa ce activitate adaugi participanti? Index: ";

            cin>>nr_act;
            int nr_participanti;
            cout<<"\nCati participanti adaug? ";
            cin>>nr_participanti;
            cin.get();
            for(int i=0;i<nr_participanti;i++)
                {
                    date_participant p;
                    cin>>p;
                    (A[nr_act].second)->adaug_participant(p);
                }
            break;
        case 2: cout<<"Nr activitatii pe care doresti sa o afisezi este: ";
                cin>>nr_act;
                cout<<*(A[nr_act].second);
                break;
        case 3: cout<<"Curs:\n";
                afis_pe_activitate('u',A,n);
                cout<<"Concurs on-line:\n";
                afis_pe_activitate('n',A,n);
                cout<<"Concurs off-line:\n";
                afis_pe_activitate('f',A,n);
                break;
        case 4: data d;
                cout<<"Data: ";
                cin>>d.zi>>d.luna>>d.an;
                afis_participanti_in_zi_data(d,A,n);
                break;
        case 5: afis_premianti(A,n);
                break;

        default: break;
        }
    }
    while(opt!=0);
    return 0;
}
