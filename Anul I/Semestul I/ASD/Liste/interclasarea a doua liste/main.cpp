#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("f.in");
struct nod
{
    int val;
    nod *next;
};
void adaug_final(nod *&prim,nod *&ult,int x)
{
    nod *p;
    p=new nod;
    p->val=x;
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


void creare_lista(nod *&prim,nod *&ult,int &n)
{
    //cream o lista de n elemente
    prim=ult=NULL;
    int x;
    fin>>n;
    for(int i=1;i<=n;i++)
    {
        fin>>x;
        adaug_final(prim,ult,x);
    }
}
void afisare(nod *prim)
{
    nod *p;
    for(p=prim;p!=NULL;p=p->next)
        cout<<p->val<<' ';
    cout<<'\n';
}

void interclasare(nod *prim1,nod *prim2,nod *&prim3)
{
    nod *r,*p1,*p2;
    p1=prim1;
    p2=prim2;
    if(p1->val<p2->val)
    {
      r=prim3=p1;
      p1=p1->next;
    }
    else
    {
      r=prim3=p2;
      p2=p2->next;
    }
    while(p2!=NULL && p1!=NULL)
    {
        if(p1->val<p2->val)
        {
            r->next=p1;
            r=p1;
            p1=p1->next;
        }
        else
        {
            r->next=p2;
            r=p2;
            p2=p2->next;
        }
    }
    if(p1==NULL)r->next=p2;
    else r->next=p1;

}
int main()
{
    nod *prim1,*ult1,*prim2,*ult2,*prim3;
    int n,m;
    creare_lista(prim1,ult1,n);
    creare_lista(prim2,ult2,m);
    interclasare(prim1,prim2,prim3);
    afisare(prim3);
    return 0;
}
