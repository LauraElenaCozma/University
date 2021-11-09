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

void afisareSRD(nod *rad)
{
    if(rad!=NULL)
    {
        afisareSRD(rad->st);
        cout<<rad->vf<<' ';
        afisareSRD(rad->dr);
    }
}

void caut(nod *rad, int k1,int k2)
{
    if(rad!=NULL)
    {
        if(rad->vf<=k1)   //daca nodurile cautate sunt mai mari decat radacina
            caut(rad->dr,k1,k2);
        else if(rad->vf>=k2) //daca nodurile cautate sunt mai mici decat radacina
                caut(rad->st,k1,k2);
             else if(rad->vf>k1 && rad->vf<k2)  //daca printre nodurile cautate se afla si radacina
             {
                 caut(rad->st,k1,k2);
                 cout<<rad->vf<<' ';
                 caut(rad->dr,k1,k2);
             }
    }
}
int main()
{
    nod *rad;
    creareABC(rad);
    afisareSRD(rad);
    cout<<'\n';
    caut(rad,-1,5);
    return 0;
}
