#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("f.in");

struct nod
{
    int vf;
    nod *next;
};

void push(nod *&prim,int x)
{
    nod *p;
    p=new nod;
    p->vf=x;
    if(prim==NULL)
    {
        p->next=NULL;
        prim=p;
    }
    else
    {
        p->next=prim;
        prim=p;
    }
}


int pop(nod *&prim)
{
    if(prim==NULL)return -1;
    else
    {
        nod *p;
        p=prim;
        prim=prim->next;
        int valoare=p->vf;
        delete p;
        return valoare;
    }
}


bool emptyStack(nod *prim)
{
    return (prim==NULL);
}

void afisare(nod *prim)
{
    if(prim!=NULL)
    {
        nod *p;
        cout<<"varf ";
        for(p=prim;p!=NULL;p=p->next)
            cout<<p->vf<<' ';
        cout<<"baza\n";
    }
    else cout<<"Stiva vida\n";
}

bool tarusi(int n)
{
    nod *prim;
    prim=NULL;
    int x,y,i;
    fin>>x;
    push(prim,x);
    for(i=2;i<=n;i++)
    {

        fin>>y;
        if(x!=y || x==-1)
            push(prim,y);
        else
            pop(prim);
        if(prim!=NULL)x=prim->vf;
        else x=-1;
    }
    afisare(prim);
    return emptyStack(prim);
}


int main()
{
   int n;
   fin>>n;
   if(tarusi(n))cout<<"configuratie buna";
   else cout<<"configuratia nu e buna";
    return 0;
}
