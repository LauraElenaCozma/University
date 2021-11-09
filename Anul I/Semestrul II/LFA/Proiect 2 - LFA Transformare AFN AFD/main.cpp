#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define MAX_NFA_STATES 65 //litere mici+litere mari+cifre de la 0 la 9
#define MAX_ALPHABET_SIZE 100 //numar caractere de pe tastatura

class Automat
{
        string alfabet;

        int nr_stari;
        string stari[MAX_NFA_STATES];

        string stare_initiala;

        int nr_stari_finale;
        string stari_finale[MAX_NFA_STATES];

        string a[MAX_NFA_STATES][MAX_ALPHABET_SIZE]; //structura automatului

    public:


        void citire();
        void afisare();

        void initializare_matrice();


        string reuniune_stari(string s,int poz);
        void determinare_stari_finale(string s[],int nrs,string f[],int &nrf);

        void transformareAFD(Automat & A);

       // int caut_stare(string v[],int n,char s);
        int caut_stare_in_vector_de_stari(string s[],int n,string stare);


};



int Automat::caut_stare_in_vector_de_stari(string s[],int n,string stare)
{
    //cauta o stare de tip string intr-un vector de stringuri
    for(int i=0;i<n;i++)
        if(s[i]==stare)
           return i;
    return -1;        //starea nu s-a gasit in vectorul de stari
}

void Automat::initializare_matrice()
{
    //se initializeaza fiecare element al matricii a cu valoarea '\0'
    int lung=alfabet.length();
    for(int i=0;i<nr_stari;i++)
        for(int j=0;j<lung;j++)
        {
            a[i][j][0]='\0';
        }

}


void Automat::citire()
{
    ifstream fin("date_automat.in");
    //citim alfabetul
    fin>>alfabet;

    //citim starile, dupa care etichetele starilor
    fin>>nr_stari;
    for(int i=0;i<nr_stari;i++)
        fin>>stari[i];

    fin>>stare_initiala;
    //citirea starilor finale si a numarului lor
    fin>>nr_stari_finale;
    for(int i=0;i<nr_stari_finale;i++)
        fin>>stari_finale[i];

    initializare_matrice();

    string x,y;
    char lit;
    while(fin>>x>>y>>lit)
    {
        //de la x la y merge o muchie etichetata cu lit
        //determinam linia pe care adaugam in matrice, adica indicele starii citite

        int lin=caut_stare_in_vector_de_stari(stari,nr_stari,x);

        //cautam pozitia literei lit in alfabet pentru a sti pe ce coloana adaugam in matrice

        int col=alfabet.find_first_of(lit);  //determina prima aparitie a acelei litere in alfabet

        if(lin!=string::npos && col!=string::npos) //s-au gasit datele in vectorul de stari, respectiv alfabet
            a[lin][col]=a[lin][col]+y;        //concatenam y
    }


    fin.close();
}

void Automat::afisare()
{
    cout<<"Alfabetul este: "<<alfabet<<'\n';
    cout<<"Cele "<<nr_stari<<" stari sunt: ";
    for(int i=0;i<nr_stari;i++)
        cout<<stari[i]<<' ';
    cout<<"\nStarea initiala e: "<<stare_initiala<<'\n';

    cout<<"Sunt "<<nr_stari_finale<<" stari finale: ";
    for(int i=0;i<nr_stari_finale;i++)
        cout<<stari_finale[i]<<' ';

    cout<<"\nStructura automatului:\n";
    int lung=alfabet.length();
    for(int i=0;i<nr_stari;i++) //pe linii sunt starile
        for(int j=0;j<lung;j++)  //pe coloane sunt simbolurile din alfabet
            {
                if(a[i][j]=="\0")cout<<stari[i]<<' '<<alfabet[j]<<" -\n";
                else cout<<stari[i]<<' '<<alfabet[j]<<' '<<a[i][j]<<'\n';
            }
    cout<<'\n';
}


void Automat::determinare_stari_finale(string s[],int nrs,string f[],int &nrf)
{
    //s- vectorul de stari ale automatului pentru care determinam starile finale
    //nrs- nr de stari sle afd-ului
    //f- vectorul cu starile finale
    //nrf - nr de stari finale

    nrf=0;

    for(int i=0;i<nrs;i++)
    {
        //parcurgem starile afd-ului si vedem care din ele sunt finale
        int ok=0;
        for(int j=0;j<nr_stari_finale && !ok;j++) //parcurgem starile finale ale afn-ului
            if(string::npos!=s[i].find(stari_finale[j]))//daca am gasit in starea i indicele unei stari finale
            {                                           //stari_finale[j] au doar un caracter
                ok=1;
                f[nrf]=s[i];  //adaugam s[i] la starile finale ale afd-ului
                nrf++;
            }
    }
}



string Automat::reuniune_stari(string s,int poz)//poz e coloana pe care cautam
{
    string rez="";        //initializam cu sirul vd, pentru orice eventualitate
    int lung=s.length();
    for(int i=0;i<lung;i++)                   //parcurgem caracterele lui s
        {
            string stare_cautata="";          //facem dintr-un caracter un sir de caractere
            stare_cautata=stare_cautata+s[i]; //facem un string ce contine doar caracterul s[i]

            int linie=caut_stare_in_vector_de_stari(stari,nr_stari,stare_cautata);//caut_stare(stari,nr_stari,s[i]);
            //aici am cautat printre starile afn-ului
            if(a[linie][poz]!="\0")           //ca sa nu concatenam \0 in interiorul sirului de stari
            {
                int lung2=a[linie][poz].length();
                for(int j=0;j<lung2;j++)
                    if(string::npos==rez.find_first_of(a[linie][poz][j]))
                        //caracterele din noua stare trebuie sa fie distincte. verificam pentru fiecare caracter al starii a[linie][poz] daca se gaseste in rez.
                        rez.append(1,a[linie][poz][j]);     //daca nu s-a gasit starea, il adaugam la rez
            }
        }
    sort(rez.begin(), rez.end());  //sortam caracterele din sir, deoarece 132 si 231 e aceeasi stare si nu trebuie facuta o distinctie
    return rez;
}



void Automat::transformareAFD(Automat & A)
{
    A.nr_stari=1;
    A.stari[0]=stare_initiala;   //am adaugat in starile noului automat starea initiala a afn-ului

    A.stare_initiala=stare_initiala;

    A.nr_stari_finale=0;
    A.alfabet=alfabet;

    int p=0,u=0;
    while(p<=u)    //cat timp coada e nevida
    {
        string s=A.stari[p];                    //selectam starea de pe linia curenta din afd

        for(int i=0;i<alfabet.length();i++)     //parcurgem coloanele
            {
                A.a[p][i]=reuniune_stari(s,i);   //p reprezinta linia curenta din matricea noului automat
                //am vazut in ce stari de duce starea s pentru al i-lea caracter din alfabet

                int poz=caut_stare_in_vector_de_stari(A.stari,A.nr_stari,A.a[p][i]);
                //in vectorul de stari avem starile distincte. vedem daca starea din urma reuniunii e noua
                if(poz==-1 && A.a[p][i]!="\0")
                {
                    //daca starea e noua si nu e una vida o adaugam la stari
                    A.stari[++u]=A.a[p][i];

                    A.nr_stari++;
                }


            }
        //trecem la urmatoarea stare din vector
        p++;
    }

    //dupa ce am determinat starile, vedem care din ele sunt finale
    determinare_stari_finale(A.stari,A.nr_stari,A.stari_finale,A.nr_stari_finale);

}

int main()
{
    Automat A,B;
    A.citire();
    A.afisare();
    A.transformareAFD(B);
    B.afisare();
    return 0;
}


/*
Exemple:
1.
ab
5
0 1 2 3 4
0
2
0 2
0 0 b
0 1 a
0 3 b
1 2 a
1 4 b
2 2 a
2 2 b
3 0 b
4 0 a
4 2 a
4 3 a


2.
01
5
a b c d e
a
1
e
a a 0
a c 0
a b 0
a e 0
a e 1
a d 0
a d 1
d e 0
b c 0
c b 1
b e 1

3.
ab
3
0 1 2
0
1
2
0 0 a
0 0 b
0 1 a
1 2 b

4.
01
3
1 2 3
1
1
3
1 3 0
2 1 1
2 3 1
3 2 0
3 1 0
3 1 1


Raspuns
1 0 3
1 1 -
3 0 12
3 1 1
12 0 3
12 1 13
13 0 123
13 1 1
123 0 123
123 1 13

*/
