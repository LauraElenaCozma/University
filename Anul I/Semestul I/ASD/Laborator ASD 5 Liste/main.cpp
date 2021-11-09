#include <iostream>

using namespace std;
struct nod
{
    nod *next;
    int val;
};

void ad_inc(nod *&prim,nod *&ult,int x)
{
    nod *p;
    p=new nod;
    p->next=prim;
    p->val=x;
    prim=p;
    if(ult==NULL)
            ult=prim;//era vida si prin inserare am mai adaugat un element
}

void citire(nod *&prim,nod *&ult,int &n)
{
    int x;
    cin>>n;
    prim=ult=NULL;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        ad_inc(prim,ult,x);
    }
}


void afisare(nod *prim)
{
    for(nod *p=prim;p!=NULL;p=p->next)
        cout<<p->val<<' ';
    cout<<'\n';
}

///Exercitiul 1
void ex1(nod *prim)
{
    nod *ant=prim;
    nod *p;
    for(p=prim->next;p!=NULL;p=p->next,ant=ant->next->next)
    {
        nod *q;
        q=new nod;
        q->val=(p->val+ant->val)/2;
        q->next=p;
        ant->next=q;
    }
}



///Exercitiul 2
void inserare_elem(nod *&prim,nod *&ult,int x)
{
    //inseram nodul cu valoarea x in lista
    nod *p;
    p=new nod;
    p->val=x;
    if(prim==NULL) //daca lista e vida
    {
        p->next=prim;
        prim=ult=p; //primul si ultimul vor fi elementul abia inserat
    }
    else if(prim->val>x)  //inserare la inceput
    {
        p->next=prim;
        prim=p;
    }
    else if(ult->val<=x)
            {
                //inseram la finalul listei
                ult->next=p;
                p->next=NULL;
                ult=p;
            }
        else
        {
            nod *q;
            nod *ant=prim;
            int ok=0;
            for(q=prim->next;q!=NULL && !ok;q=q->next,ant=ant->next)
            {
                if(x>=ant->val && x<=q->val) //il pozitionam intre 2 noduri si vedem daca se potriveste intre ele
                {
                    p->next=q;
                    ant->next=p;
                    ok=1;
                }
            }

        }
}

void creare_ex2(nod *&prim,nod *&ult,int &n)
{
    prim=ult=NULL;
    cin>>n;
    int x;
    for(int i=1;i<=n;i++)
       {
           cin>>x;
           inserare_elem(prim,ult,x);
       }
}


///Exercitiul 3:inversarea legaturilor dintr-o lista
void inversare_leg(nod *&prim)
{
    nod *p,*q,*r;
    p=prim;
    q=prim->next;
    r=(prim->next)->next;
    for(r=prim->next->next;r!=NULL;r=r->next)
    {
        q->next=p;
        p=q;
        q=r;
    }
    //acum q va fi ultimul
    q->next=p; //r e null si se iese din for, dar legatura dintre ultimele 2 nu e realizata inca
    prim->next=NULL;
    prim=q;
}


///Exercitiul 5: Adunarea a 2 numere mari
void adunare(nod *prim1,nod *prim2,nod *&prim3)
{

}



///Exercitiul 6:inmultirea unui nr mare cu un scalar de o cifra


void inmultire_scalar(nod *&prim,nod *&ult,int &x)
{
    int t=0,a;
    cout<<"Scalarul cu care inmultim este:";
    cin>>x;
    for(nod *p=prim;p!=NULL;p=p->next)
    {
        a=x*p->val+t;
        p->val=a%10;
        t=a/10;
    }
    while(t!=0)
    {
        nod *p=new nod;
        p->val=t%10;
        t/=10;
        //daca scalarul are mai mult de o cifra, transportul poate avea si el mai mult de o cifra la final, deci trebuie sa ii punem cate o cifra in fiecare nod al listeo
        ult->next=p;
        p->next=NULL;
        ult=p;
    }
}


void afis_rec(nod *prim)
{
    if(prim!=NULL)
       { afis_rec(prim->next);
         cout<<prim->val;
       }
}


int main()
{
    int n,x;
    nod *prim,*ult;
    citire(prim,ult,n);
    afisare(prim);
    inmultire_scalar(prim,ult,x);
    afis_rec(prim);
    return 0;
}
