#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("date_automat.in");

struct automat
{
    char d[100];
    int nr;     //numarul literelor
};


///sau direct matrice tridimensionala de tip char

void initializare_automat(automat **&a,int dim)
{
    a=new automat*[dim];
    int i,j;
    for(i=0;i<dim;i++)
    {
        a[i]=new automat[dim];
        for(j=0;j<dim;j++)
           {
               a[i][j].nr=0;
               a[i][j].d[0]='\0';
           }
    }

}


void citire(char cuv[],automat **&a,int &nr_stari,int &q0,int *&finale,int &nr_finale)
{
    /*citim pe rand
    -numarul starilor
    -starea initiala
    -numarul starilor finale
    -starile finale

    -nr muchii
    -munchii

    -cuvant

    */
    int i;
    //citeste numarul starilor pentru a putea determina dimensiunile marticii de tip structura a[][]
    fin>>nr_stari;
    //citeste starea initiala
    fin>>q0;
    //citeste numarul starilor finale dupa care starile finale propriu zise(cu valori intre 0 si nr_stari-1)
    fin>>nr_finale;
    finale=new int[nr_finale];
    for(i=0;i<nr_finale;i++)
        fin>>finale[i];


    //initializam matricea cu valoarea NULL pe fiecare element
    initializare_automat(a,nr_stari);

    int stare1,stare2,nr_muchii;
    char litera;
    //citeste numarul muchiilor dupa care nr muchii sub formatul stare1 stare2 litera_de_pe_muchie
    fin>>nr_muchii;
    for(i=0;i<nr_muchii;i++)
    {
        fin>>stare1>>stare2>>litera;
        a[stare1][stare2].d[a[stare1][stare2].nr]=litera;
        a[stare1][stare2].nr++;
        a[stare1][stare2].d[a[stare1][stare2].nr]='\0';

    }

    cuv[0]='\0'; //in cazul in care nu exista niciun cuvant la finalul fisierului inseamna ca citim cuvantul vid
    fin>>cuv;

}


/*void afisare(automat **a,int dim)
{
    int i,j;
    for(i=0;i<dim;i++)
    {
        for(j=0;j<dim;j++)
            if(a[i][j].nr!=0)
                 cout<<i<<' '<<j<<' '<<a[i][j].d<<'\n';
    }
}*/


int gasit(int *v,int nr_elemente,int x)
{
    //functie care verifica daca o stare este stare finala. Ea verifica la modul general daca un element este in vector
    int i;
    for(i=0;i<nr_elemente;i++)
    {
         if(x==v[i])return 1;
    }

    return 0;
}


void validare(char cuv[],int pozitie_cuvant,int starea_curenta,automat **a,int nr_stari,int finale[],int nr_finale,int &valid)
{
    //daca am ajuns la finalul cuvantului
    if(cuv[pozitie_cuvant]=='\0')
    {
        //daca starea in care am ajuns este una finala, cuvantul e valid
        if(gasit(finale,nr_finale,starea_curenta))
               valid=1;

    }
    else
    {
        int i,j;
        //parcurgem matricea de tip automat
        for(i=0;i<nr_stari;i++)
        {
            for(j=0;j<a[starea_curenta][i].nr;j++)
                if(a[starea_curenta][i].nr!=0 && cuv[pozitie_cuvant]==a[starea_curenta][i].d[j])
                    //daca din starea curenta porneste o muchie cu aceeasi litera cu litera curenta, mergem in recursie
                    validare(cuv , pozitie_cuvant+1 , i , a , nr_stari , finale , nr_finale , valid);

        }
    }
}

void afisare_rezultat(char cuv[],int valid)
{
    if(cuv[0]=='\0')
        cout<<"Cuvantul vid";
    else cout<<cuv;

    if(valid)cout<<" apartine lui L(A)";
    else cout<<" nu apartine lui L(A)";
}

int main()
{
    automat **a;
    int nr_stari,q0,*finale,nr_finale,valid=0;
    char cuv[100];

    citire(cuv , a , nr_stari , q0 , finale , nr_finale);

    validare(cuv , 0 , q0 , a , nr_stari , finale , nr_finale , valid);

    afisare_rezultat(cuv,valid);

    //dezalocarea memoriei
    delete finale;
    for(int i=0;i<nr_stari;i++)
        delete a[i];
    delete a;
    return 0;
}







/*
EXEMPLE:
4
0
1
3
8
0 0 b
0 1 a
1 1 a
1 2 b
2 0 b
2 3 a
3 3 a
3 3 b
baabbbaaababbababb -val.
bbbaba             -val.
bbbabb             -inv.



3
0
2
0 1
6
0 0 b
0 1 a
1 0 b
1 2 a
2 2 a
2 2 b
bbababbbaa -inv.
bbababbba  -val.

6
0
1
5
6
0 1 b
1 2 b
2 3 a
3 3 a
1 4 b
4 5 a
bba        -val.



*/
