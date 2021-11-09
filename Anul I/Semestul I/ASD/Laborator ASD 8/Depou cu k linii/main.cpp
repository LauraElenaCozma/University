#include <iostream>
#include <fstream>
#include <climits>
using namespace std;
ifstream fin("f.in");

/*****    Exemple

11
5
6 11 9 4 7 5 1 2 3 10 8

8
4
7 3 1 2 8 5 6 4





*****/

struct nod
{
    int vf;
    nod *next;
};

struct lista
{
    nod *prim;
    nod *ult;
};

void adaugare(nod *&prim,nod *&ult, int x)
{
    nod *p;
    p=new nod;
    p->vf=x;
    if(prim==NULL)
    {
        prim=ult=p;
        p->next=NULL;
    }
    else
    {
        ult->next=p;
        p->next=NULL;
        ult=p;
    }
}

int stergere(nod *&prim,lista v[],int poz)
{
    if(prim==NULL)return -1;
    else
    {
        nod *p;
        p=prim;
        prim=prim->next;
        v[poz].prim=prim;
        int valoare;
        valoare=p->vf;
        delete p;
        return valoare;
    }
}


void initializare(lista v[],int k)
{
    for(int i=1;i<=k;i++)
       {
           v[i].prim=NULL;
           v[i].ult=NULL;
       }
}


void afisareCoada(nod *prim)
{
    nod *p;
    for(p=prim;p!=NULL;p=p->next)
        cout<<p->vf<<' ';
    cout<<'\n';
}

void afisareLista(lista v[],int k)
{
    cout<<'\n';
    for(int i=1;i<=k;i++)
    {
        cout<<i<<' ';
        cout<<"  ";
        afisareCoada(v[i].prim);
    }
    cout<<'\n';
}

int pozitieAmplasare(lista v[],int k,int x)
{
    int pozNULL=-1;
    int poz=-1;
    int mini=INT_MAX;

    for(int i=1;i<=k;i++)

        if(v[i].prim==NULL)

        {
            if(pozNULL==-1)
               pozNULL=i;
        }

        else
        {
            int dif=x-v[i].ult->vf;
            if(dif>0)
            {
                if(dif<mini)
                {
                    mini=dif;
                    poz=i;
                }
            }
        }

    if(poz!=-1)
        return poz;
    if(pozNULL!=-1)
        return pozNULL;
    return -1;
}

int citireSiAsezarePeLinii(int n,lista v[],int k)
{
    int x;
    while(n)
    {
        fin>>x;

        int poz=pozitieAmplasare(v,k,x);
        if(poz==-1)return -1;  //nu exista nicio configuratie corecta. nu putem aseza pe liniile depoului

        adaugare(v[poz].prim,v[poz].ult,x);

        n--;
    }
}


void scoateDePeLinii(int n,lista v[],int k)
{

    int posibil=citireSiAsezarePeLinii(n,v,k);

    afisareLista(v,k);

    if(posibil==-1)
        cout<<"Nu exista nicio configuratie";
    else
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=k;j++)
                if(v[j].prim->vf==i)
            {
                cout<<i<<' ';
                stergere(v[j].prim,v,j);
                break;
            }
        }
    }
}
int main()
{
    lista v[100];
    int k,n;
    fin>>n>>k;
    initializare(v,k);

    scoateDePeLinii(n,v,k);

    afisareLista(v,k);
    return 0;
}
