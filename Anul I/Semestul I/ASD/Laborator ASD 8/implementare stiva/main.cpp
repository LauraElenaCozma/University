#include <iostream>

using namespace std;

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

int peek(nod *prim)
{
    if(prim==NULL)return -1;
    else return prim->vf;
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

int searchElementInStack(nod *prim,int x)
{
    int k=0;
    nod *p;
    for(p=prim;p!=NULL;p=p->next)
    {
        if(x==p->vf)return k;
        k++;
    }
    return -1;
}
int main()
{
    nod *prim;
    prim=NULL;
    afisare(prim);
    push(prim,1);
    cout<<'\n';
    push(prim,2);
    cout<<'\n';
    push(prim,3);
    cout<<'\n';
    afisare(prim);
    cout<<searchElementInStack(prim,2)<<'\n';
    cout<<searchElementInStack(prim,4)<<'\n';
    cout<<emptyStack(prim)<<'\n';
    cout<<pop(prim)<<'\n';
    afisare(prim);
    cout<<peek(prim)<<'\n';
    afisare(prim);
    pop(prim);
    cout<<'\n';
    pop(prim);
    cout<<'\n';
    afisare(prim);
    cout<<pop(prim)<<'\n';
    cout<<emptyStack(prim);
    return 0;
}
