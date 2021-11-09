#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("f.in");
struct nod
{
    int vf;
    nod *st,*dr;
};

void inserareNod(nod *&rad,int x)
{
    if(rad==NULL)
    {
        rad=new nod;
        rad->vf=x;
        rad->st=NULL;
        rad->dr=NULL;
    }
    else
    {
        if(x<rad->vf)inserareNod(rad->st,x);
        else inserareNod(rad->dr,x);
    }
}

void creareABC(nod *&rad)
{
    rad=NULL;
    int x;
    while(fin>>x)
           inserareNod(rad,x);
}


int maxim(nod *rad)
{
    while(rad->dr!=NULL)
        rad=rad->dr;
    return rad->vf;
}

int cautare(nod *rad,int x)
{
    //cauta valoarea x in abc-ul de radacina rad
    if(rad!=NULL)
    {
        if(rad->vf==x)return 1;
        else if(rad->vf>x)return cautare(rad->st,x);
        return cautare(rad->dr,x);
        return 0;
    }
}
//AFISARI

void afisareSRD(nod *rad)
{
    if(rad!=NULL)
    {
        afisareSRD(rad->st);
        cout<<rad->vf<<' ';
        afisareSRD(rad->dr);
    }
}


void afisareRSD(nod *rad)
{
    if(rad!=NULL)
    {
        cout<<rad->vf<<' ';
        afisareRSD(rad->st);
        afisareRSD(rad->dr);
    }
}


void afisareSDR(nod *rad)
{
    if(rad!=NULL)
    {
        afisareSDR(rad->st);
        afisareSDR(rad->dr);
        cout<<rad->vf<<' ';
    }
}

int main()
{
    nod *rad;
    creareABC(rad);
    afisareSRD(rad);
    cout<<"\nmaxim="<<maxim(rad);
    cout<<"\ncautare de 24 e "<<cautare(rad,24);
    return 0;
}
