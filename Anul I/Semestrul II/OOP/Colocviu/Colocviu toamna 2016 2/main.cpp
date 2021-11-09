#include <iostream>
#include <string>

using namespace std;

///neterminat


class utilizator
{

};
class cerere
{
protected:

    bool video;
    bool ecran;
    bool tabla;
    int numar;
    static int nr_cerere;

public:
    cerere(bool v=0,bool e=0,bool t=0) : video(v), ecran(e), tabla(t) {nr_cerere++; numar=nr_cerere;}
    cerere( const cerere& ob)
    {
        nr_cerere++;
        numar=nr_cerere;
        video=ob.video;
        ecran=ob.ecran;
        tabla=ob.tabla;
    }
    cerere& operator=( const cerere& ob)
    {
        if(this==&ob)return (*this);
        video=ob.video;
        ecran=ob.ecran;
        tabla=ob.tabla;
        return (*this);
    }
    virtual void citire(istream& in)
    {
        in>>video>>ecran>>tabla;
    }

    friend istream& operator>>(istream& in, cerere& ob)
    {
        ob.citire(in);
        return in;
    }
    bool get_video() const
    {
        return video;
    }
    bool get_tabla() const
    {
        return tabla;
    }
    bool get_ecran() const
    {
        return ecran;
    }

};
int cerere::nr_cerere = 0;
class home: virtual public cerere
{
public:
    home(bool v=0,bool e=0,bool t=0) : cerere(v,e,t) {}
    home(const home& ob) : cerere(ob) {}
    home& operator=(const home& ob) { cerere::operator=(ob);}

    void citire(istream& in)
    {
        cerere::citire(in);
    }

    void home_porneste(string dispozitiv)
    {
        if(dispozitiv=="tabla")tabla=1;
        else if(dispozitiv=="video")video=1;
             else if(dispozitiv=="ecran")ecran=1;
                  else
                  {
                      cout << "Numele dispozitivului introdus este incorect\n";
                      ///throw invalid_argument;
                  }
    }

    void home_opreste(string dispozitiv)
    {
        if(dispozitiv=="tabla")tabla=0;
        else if(dispozitiv=="video")video=0;
             else if(dispozitiv=="ecran")ecran=1;
                  else
                  {
                      cout << "Numele dispozitivului introdus este incorect\n";
                      ///throw invalid_argument;
                  }
    }

    string home_verificare()
    {
        if(video*tabla*ecran==1)return "Ok\n";
        else return "Nu am inteles cerinta\n";
    }

    home& operator+(int i)
    {
        video=1;
        return *this;
    }

    home& operator+(char d)
    {
        if(d=='E')ecran=1;
        else if(d=='V')video=1;
             else if(d=='T')tabla=1;
                   else
                   {
                        cout << "Numele dispozitivului introdus este incorect\n";
                        ///throw invalid_argument;
                   }
        cout<<tabla<<' '<<ecran<<' '<<video<<'\n';
    }

};


class education : virtual public cerere
{
public:
    education(bool v=0,bool e=0,bool t=0) : cerere(v,e,t) {}
    education(const education& ob) : cerere(ob) {}
    education& operator=(const education& ob) { cerere::operator=(ob);}

    void citire(istream& in)
    {
        cerere::citire(in);
    }
    void edu_trivia(string site)
    {
        if(tabla==0 && video==1)cout<< "Cautare "+site+"\n";
        else cout<<"Eroare componenta hardware\n";
    }
    string edu_lectie(string curs,string nr)
    {
        if(tabla==0 && video==1)return "Download "+curs+" - Curs "+nr;
        else return "Eroare componenta hardware\n";
    }
};
int main()
{
    home h1,h2(1),h3(0,0,1);
   // cin>>h1;
    h2.home_opreste("tabla");
    home h4(h2),h5=h2;
    h4=h4+1;
    h4=h4+'E';
   /* cout<<h1.home_verificare()<<h2.home_verificare()<<h4.home_verificare();


    education e1,e2(1),e3(1,1,0),e4(e3);
  //  cin>>e1;
    cout<<endl<<e4.edu_lectie("Algebra","4")<<endl;
    e2.edu_trivia("data_structures");
    cout<<e2.edu_lectie("poo","2");
   // cout<<h4.get_video()<<' '<<h4.get_ecran()<<' '<<c[i.get_tabla()<<endl;
    cout<<endl;
    cerere *c=new cerere[4];
    c[0]=h3;
    c[1]=h4;
    c[2]=e3;
    c[3]=e4;

    for(int i=0;i<4;i++)
        cout<<c[i].get_video()<<' '<<c[i].get_ecran()<<' '<<c[i].get_tabla()<<endl;*/
    return 0;
}
