#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Gramatica
{
    vector < char > N; //vector ce contine neterminalele
    int nr_n;        //numarul de neterminale
    vector < char > T; //vector ce contine terminalele
    int nr_t;        //numarul de terminale

    vector < vector <string> > s; //structura gramaticii
    vector <string> rezultat;

public:
    Gramatica()
    {
        nr_n=nr_t=0;
    }
    void citire(int &n);
    void afisare();
    void afisare_rezultat();
    int caut_neterminal(char net);

    string concatenare(string initial, string concat,int poz_in_vector,int poz_in_string);

    void generare(int poz_in_vector, int poz_in_string, string cuv,int n);



};

void Gramatica::citire(int &n)
{
    ifstream fin("date_gramatica.in");
    fin>>nr_n;
    N.resize(nr_n);
    for(int i=0;i<nr_n;i++)
    {
        fin>>N[i];
    }


    fin>>nr_t;
    T.resize(nr_t);
    for(int i=0;i<nr_t;i++)
        fin>>T[i];

    char stanga;
    string dreapta;
    int nr_linii;

    fin>>nr_linii;

    s.resize(nr_n);
    for(int i=0;i<nr_linii;i++)
    {
        fin>>stanga>>dreapta;
        unsigned int poz=caut_neterminal(stanga);

        if(poz!=-1)  //daca s-a gasit neterminalul respectiv printre multimea de neterminale
            s[poz].push_back(dreapta);
    }

    fin>>n;

    T.push_back('~'); //am adaugat in coada simbolul corespunzator lui lambda pentru a-l recunoaste drept neterminal
    fin.close();
}

void Gramatica::afisare()
{
    for(int i=0;i<nr_n;i++)
    {
        cout<<N[i]<<": ";
        for(string sir : s[i])
            cout<<sir<<' ';
        cout<<'\n';
    }
}

int Gramatica::caut_neterminal(char net)
{
    //metoda care cauta neterminalul net in vectorul de neterminale N.
    for(int i=0;i<nr_n;i++)
        if(net==N[i])return i;
    return -1;     //daca nu s-a gasit returneaza -1
}


int cautare(string s, vector <string> v)
{
    for(string c : v)
        if(c==s)return 0;
    return 1;
}
string Gramatica::concatenare(string initial, string concat,int poz_in_vector,int poz_in_sir)
{
    //functie care concateneazã pe pozitia poz sirul concat, eliminand neterminalul
    //acest caz este special pentru momentul de intrare cand cuvantul curent e vid si totusi neterminalul e S
    if(poz_in_sir==-1)
        return concat;
    char aux[1000];            //am folosit un vector de tip char pentru ca numai asa accepta ca parametru
    string s1,s2;
    initial.copy(aux,poz_in_sir,0);   //copiem caracterele de la inceputul sirului initial pana la neterminal
    aux[poz_in_sir]='\0';
    s1=aux;

    initial.copy(aux,initial.size()-poz_in_sir-1,poz_in_sir+1);   //copiem caracterele de dupa neterminal pana la sfarsitul sirului initial
    aux[initial.size()-poz_in_sir-1]='\0';
    s2=aux;

    if(concat=="~")s1=s1+s2;   //daca ar trebui sa concatenam in interiorul cuvantului lambda
    else s1=s1+concat+s2;
    if(s1=="")return "~";
    return s1;

}

void Gramatica::generare(int poz_in_vector, int poz_in_string, string cuv,int n)
{
    for(int i=0;i<s[poz_in_vector].size();i++) //parcurg linia poz_in_vector a matricii s
    {
        if(cuv.size()-1+s[poz_in_vector][i].size()<=n+5)  //daca eliminand un caracter din cuv si apoi introducand s[poz_in_vector][i] nu depasim n+1 continuam
        {
            //n+5 deoarece putem sa avem neterminale care se duc in lambda si atunci sunt eliminate. se accepta maxim 5 neterminale in membrul drept

            string sir=this->concatenare(cuv,s[poz_in_vector][i],poz_in_vector,poz_in_string);

            int ok=0;
            for(int j=0;j<sir.size();j++)
            {   //cautam neterminalele din noul cuvant
                int poz=caut_neterminal(sir[j]);
                if(poz!=-1)
                {
                    ok=1;
                    generare(poz,j,sir,n);
                    //la primul neterminal gasit intram in recursie
                }
            }
            if(!ok && (sir.size()<=n || sir=="~"))
                if(cautare(sir,rezultat))rezultat.push_back(sir);

          // !ok inseamna ca nu am gasit neterminale, deci cuvantul poate fi afisat


        }
    }

}

void Gramatica::afisare_rezultat()
{
    for(string s : rezultat)
        cout<<s<<'\n';
}
int main()
{
    Gramatica g;
    int n;
    g.citire(n);
    g.generare(0,-1,"",n);

    g.afisare_rezultat();
    return 0;
}


/*
2
S A
2
a b
4
S bSbb
S A
A aA
A ~
5

2
S T
3
0 1 a
5
S 1S
S 0T
S ~
T 1T
T 0S
2


3
S C D
2
0 1
5
S CD
C 0C
C ~
D 1D
D ~
0

Foi seminar:
3
S A B
3
a c b
5
S AB
A aaAccc
A aaccc
B bB
B b
12


L7
2
S A
4
a b c d
5
S aSd
S ad
S aAd
A bAcc
A ~
12

L10
4
S A B C
5
a b c d e
9
S AB
S ~
A aAbb
A ~
B cBeee
B ~
B dC
C dC
C ~
5

*/
