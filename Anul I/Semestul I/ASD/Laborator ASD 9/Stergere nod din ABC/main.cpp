#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("f.in");

struct nod
{
    nod *st;
    nod *dr;
    int vf;
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


nod * CelMaiStangDinDreapta(nod * rad)
{
    rad=rad->dr;
    while(rad->st!=NULL)
        rad=rad->st;
    return rad;
}


nod * stergere(nod *rad,int x)
{
    if(rad==NULL)
    {
        return NULL;
    }
    else if(x<rad->vf)
        rad->st=stergere(rad->st,x);//radacina arborelui din stanga
    else if(x>rad->vf)
        rad->dr=stergere(rad->dr,x);//radacina arborelui din dr
    else  //am ajuns pe nodul cautat
    {
        //caz 1: nu are niciun fiu
        if(rad->st==NULL && rad->dr==NULL)
        {
            delete rad;
            rad=NULL;
        }
        //caz 2:are doar fiu drept
        else if(rad->st==NULL)
        {
            nod * aux=rad;
            rad=rad->dr;
            delete aux;
        }
        else if(rad->dr==NULL)
        {
            nod * aux=rad;
            rad=rad->st;
            delete aux;
        }
        //caz 3: are 2 fii
        else
        {
            nod * aux=CelMaiStangDinDreapta(rad);
            rad->vf=aux->vf;
            rad->dr=stergere(rad->dr,aux->vf);
        }
    }


    return rad;
}

void afisareSRD(nod *rad)
{
    if(rad!=NULL)
    {
        afisareSRD(rad->st);
        cout<<rad->vf<<' ';
        afisareSRD(rad->dr);
    }
}


int main()
{
    nod *rad;
    creareABC(rad);
    stergere(rad,6);
    inserareNod(rad,13);
    afisareSRD(rad);
    return 0;
}
