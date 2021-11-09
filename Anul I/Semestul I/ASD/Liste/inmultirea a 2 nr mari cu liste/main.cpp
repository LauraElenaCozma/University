#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("f.in");
struct nod
{
    int val;
    nod *next;
};
void adaug_inceput(nod *&prim,nod *&ult,int x)
{
    nod *p;
    p=new nod;
    p->val=x;
    if(prim==NULL)
    {
        prim=ult=p;
        ult->next=NULL;
        p->next=NULL;
    }
    else
    {
        p->next=prim;
        prim=p;
    }
}


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
        adaug_inceput(prim,ult,x);
    }
}


void inmultire(nod *prim1,nod *prim2,nod *&prim3,nod *&ult3)
{
    nod *indice1, *indice3;
    nod *q1,*q2,*q3;
    indice1=prim1; //indice dupa care parcurgem primul nr
    prim3=ult3=NULL;
    adaug_final(prim3,ult3,0);//am facut o lista cu un singur element care va avea valoarea 0
    indice3=prim3;
    while(indice1!=NULL)
    {

        q3=indice3;
        for(q2=prim2;q2!=NULL;q2=q2->next) //parcurgem al doilea nr de atatea ori cate cifre are primul nr
             {
                 int x=q2->val*indice1->val;
                 if(q3==NULL)
                       {adaug_final(prim3,ult3,0);
                       q3=ult3;
                       if(indice3==NULL)indice3=q3;//ca sa nu dea eroare cu null urmator
                       }
                 q3->val+=x;
                 q3=q3->next;
             }
        indice1=indice1->next;
        indice3=indice3->next;
        /*afisare(prim3);
        cout<<'\n';*/
    }
    //am format o lista cu produsele partiale
    //vrem sa mutam transportul de pe un produs pe urmatorul
    int t=0;
    for(nod *p=prim3;p!=NULL;p=p->next)
    {
        int a=p->val+t;
        t=a/10;
        p->val=a%10;
    }
    while(t)
    {
        adaug_final(prim3,ult3,t%10);
        t/=10;
    }

}


void afisare_recursiva(nod *prim)
{
    if(prim!=NULL)
    {
        afisare_recursiva(prim->next);
        cout<<prim->val;
    }
}


int main()
{
    nod *prim1,*ult1,*prim2,*ult2,*prim3,*ult3;
    int n,m;
    creare_lista(prim1,ult1,n);
    creare_lista(prim2,ult2,m);
    ///ATENTIE. PROGRAMUL NU REALIZEAZA INMULTIRE CU 0(va afisa 00000) ASA CA TREBUIE PUS UN TEST SEPARAT
    if((n==1 && prim1->val==0) || (m==1 && prim2->val==0))cout<<0;
    else
    {
       inmultire(prim1,prim2,prim3,ult3);
       afisare_recursiva(prim3);
    }
    return 0;
}
