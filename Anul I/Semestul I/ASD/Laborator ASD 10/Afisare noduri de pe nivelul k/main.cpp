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


void afisNivel(nod *rad,int nivel,int k)
{
    if(rad!=NULL)
    {
    if(nivel==k)
    cout<<rad->vf<<' ';
    else
    {
        afisNivel(rad->st,nivel+1,k);
        afisNivel(rad->dr,nivel+1,k);
    }
    }

}

int main()
{
    nod *rad;
    int k;
    cout<<"k=";
    cin>>k;
    creareABC(rad);
    afisNivel(rad,1,k);
    return 0;
}
