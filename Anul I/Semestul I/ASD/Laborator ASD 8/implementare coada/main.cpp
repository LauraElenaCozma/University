#include <iostream>

using namespace std;

struct nod
{
    int vf;
    nod *next;
};

void push(nod *&prim,nod *&ult, int x)
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


int pop(nod *&prim)
{
    if(prim==NULL)return -1;
    else
    {
        nod *p;
        p=prim;
        prim=prim->next;
        int valoare;
        valoare=p->vf;
        delete p;
        return valoare;
    }
}

int peek(nod *prim)
{
    if(prim==NULL)return -1;
    return prim->vf;
}

bool emptyQueue(nod *prim)
{
    return (prim==NULL);
}

void afisare(nod *prim)
{
    if(prim==NULL)cout<<"Coada vida\n";
    else
    {
        nod *p;
        cout<<"out ";
        for(p=prim;p;p=p->next)
            cout<<p->vf<<' ';
        cout<<"in\n";
    }
}

int searchElementInQueue(nod *prim,int x)
{
    int k=1;
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
    nod *prim,*ult;
    prim=ult=NULL;
    afisare(prim);
    push(prim,ult,1);
    cout<<'\n';
    push(prim,ult,2);
    cout<<'\n';
    push(prim,ult,3);
    cout<<'\n';
    afisare(prim);
    cout<<searchElementInQueue(prim,2)<<'\n';
    cout<<searchElementInQueue(prim,4)<<'\n';
    cout<<emptyQueue(prim)<<'\n';
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
    cout<<emptyQueue(prim)<<'\n';
    return 0;
}
