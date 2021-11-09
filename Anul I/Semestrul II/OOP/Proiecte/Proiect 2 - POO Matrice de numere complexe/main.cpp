#include <iostream>
#include "Complex.h"
#include "Matrice.h"
#include "Matrice_oarecare.h"
#include "Matrice_patratica.h"
#include <fstream>
#include <typeinfo>
using namespace std;
ifstream fin("date.in");
int main()
{
    Matrice **a;
    int n;
    cout<<"Numarul de matrice citite este: ";
    cin>>n;
    a=new Matrice*[n];
    for(int i=0;i<n;i++)
        if(i%2==0)a[i]=new Matrice_oarecare;  //pe pozitiile pare avem matrice oarecare, pe impare patratice
        else a[i]=new Matrice_patratica;
    for(int i=0;i<n;i++)
    {
        fin>>*(a[i]);
        cout<<'\n'<<typeid(*a[i]).name()<<'\n';

        (a[i])->diagonala();
        cout<<*(a[i])<<'\n';
    }


    for(int i=0;i<n;i++)
            delete a[i];
    delete[] a;
    fin.close();
    return 0;
}
