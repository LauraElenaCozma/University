#include <iostream>

using namespace std;
struct nod
{
    int val;
    nod * next;
}*prim,*ult;

void afisare()
{
    //afisam lista care incepe de la prim
    if(prim==NULL)cout<<"Lista vida!";
    else
    {
        nod *p;
        for(p=prim;p!=NULL;p=p->next)
            cout<<p->val<<' ';
    }
    cout<<'\n';
}

void ad_inc(int x)
{
    nod *p;
    p=new nod;
    p->val=x;
    if(prim==NULL)//lista e vida
    {
        prim=ult=p;
        ult->next=NULL;
    }
    else
    {
        p->next=prim;
        prim=p;
    }
}

void ad_sf(int x)
{
    nod *p;
    p=new nod;
    p->val=x;
    p->next=NULL;
    if(prim==NULL)//lista vida
        prim=ult=p;
    else
    {
        ult->next=p;
        ult=p;
    }

}

int caut_val(int x)
{
    nod *p;
    int k=1;
    for(p=prim;p!=NULL;p=p->next)
        {
            if(p->val==x)return k;
            k++;
        }
    return -1;
}

int caut_poz(int poz)
{
    nod *p;
    int k=1;
    for(p=prim;p!=NULL;p=p->next)
        {
            if(k==poz)return p->val;
            k++;
        }
    return -1;

}

void insert_af_val(int x,int y)
{
    //inseram dupa prima aparitie a elem x un nou nod cu valoarea y
    nod *p;
    int ok=0;//nu am gasit inca elem x
    for(p=prim;p!=NULL && !ok;p=p->next)
        if(p->val==x)
        {
            ok=1;
            if(p->next==NULL)//daca x se afla in ultimul nod trebuie sa actualizam ult
                 ad_sf(y);
            else
            {
                nod *q;
                q=new nod;
                q->next=p->next;
                p->next=q;
                q->val=y;
            }
        }

}

void insert_poz(int poz,int y)
{
    //inseram pe pozitia poz un nou nod cu valoarea y
    nod *q;
    q=new nod;
    q->val=y;
    if(poz==1 && prim==NULL)  //lista e vida
    {
        q->next=NULL;
        prim=ult=q;
    }
    else
    {
        nod *p;
        for(p=prim;p!=NULL && poz!=1;p=p->next,poz--);
        if(p!=NULL && poz==1 )
        {
            q->next=p->next;
            p->next=q;
            if(q->next==NULL)ult=q;
        }
    }
}

void stergere_val(int x)
{
    //stergem elem x

    if(prim->val==x)//trebuie sters primul
    {
        nod *q;
        q=prim;
        prim=prim->next;
        delete q;
    }
    else if(prim==ult) //lista are doar un element
    {
        prim=ult=NULL;
    }
         else
         {
             nod *ant=prim; //retinem nodul anterior
             nod *p;
             int ok=0;
             for(p=prim->next;p!=NULL && !ok;p=p->next,ant=ant->next)
                  if(p->val==x)
             {
                 ok=1;
                 if(p->next==NULL)//trebuie sters ultimul
                 {
                     nod * q=ult;
                     ant->next=NULL;
                     ult=ant;
                     delete q;
                 }
                 else
                 {
                     //stergem un nod din interiorul listei
                     nod *q;
                     q=p;
                     ant->next=p->next;
                     delete q;

                 }

             }
         }
}


void stergere_poz(int poz)
{
    if(poz==1)
    {
        if(prim==ult)//lista are un singur element
            prim=ult=NULL;
        else
        {
            nod *q;
            q=prim;
            prim=prim->next;
            delete q;
        }
    }
    else
    {
        nod *ant=prim;
        nod *p=prim->next;
        int k=2; //am verificat deja pt pozitia 1
        while(p!=NULL && k<=poz)
        {
            if(k==poz)
            {
                if(p->next==NULL)//trebuie sa il stergem pe ultimul
                {
                    nod *q=ult;
                    ant->next=NULL;
                    ult=ant;
                    delete q;
                }
                else
                {
                     nod *q;
                     q=p;
                     ant->next=p->next;
                     delete q;
                }
            }
            k++;
            p=p->next;
            ant=ant->next;
        }
    }
}
int main()
{
    prim=ult=NULL;
    afisare();
    ad_inc(1);
    ad_inc(2);
    ad_inc(3);
    afisare();
    ad_sf(4);
    afisare();
    cout<<caut_val(5)<<'\n';
    cout<<caut_val(1)<<'\n';
    cout<<caut_poz(5)<<'\n';
    cout<<caut_val(3)<<'\n';
    stergere_poz(1);
    afisare();
    stergere_poz(1);
    afisare();
    stergere_val(4);
    afisare();
    ad_sf(5);
    afisare();
    stergere_val(1);
    stergere_poz(1);
    afisare();
    ad_sf(8);
    afisare();
    insert_af_val(8,7);
    insert_poz(2,3);
    insert_poz(1,1);
    afisare();
    return 0;
}
