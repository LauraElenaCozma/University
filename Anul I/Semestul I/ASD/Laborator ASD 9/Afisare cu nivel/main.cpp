#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("f.in");


struct nod
{
    int vf;
    nod *st,*dr;
};


void inserare(nod *&rad,int x)
{
    if(rad!=NULL)
    {
        if(x>rad->vf)inserare(rad->dr,x);
        else inserare(rad->st,x);
    }
    else
    {
        rad=new nod;
        rad->vf=x;
        rad->st=NULL;
        rad->dr=NULL;
    }
}


void creare(nod *&rad)
{
    rad=NULL;
    int x;
    while(fin>>x)
    {
        inserare(rad,x);
    }
}

void afisareNivel(nod * rad,int nivel)
{
    if(rad!=NULL)
    {
        int i;
        for(i=1;i<=nivel;i++)
            cout<<' ';
        cout<<rad->vf<<'\n';
        afisareNivel(rad->st,nivel+1);
        afisareNivel(rad->dr,nivel+1);
    }
}
int main()
{
    nod * rad;
    creare(rad);
    afisareNivel(rad,0);
    return 0;
}
