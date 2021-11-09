#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
ifstream fin("f.in");

struct nod
{
    char vf[21];
    nod *st,*dr;
};

void inserare(nod *&rad,char s[])
{
    if(rad==NULL)
    {
        rad=new nod;
        rad->st=NULL;
        rad->dr=NULL;
        strcpy(rad->vf,s);
    }
    else
    {
        if(strcmp(s,rad->vf)>0)
            inserare(rad->dr,s);
        else if(strcmp(s,rad->vf)<0)
            inserare(rad->st,s);
    }
}

void creare(nod *&rad,int &n)
{
    fin>>n;
    fin.get();
    int i;
    char s[21];
    rad=NULL;
    for(i=1;i<=n;i++)
    {
         fin>>s;
         inserare(rad,s);
    }
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
    int n;
    creare(rad,n);
    afisareSRD(rad);
    return 0;
}
