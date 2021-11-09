#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("date.in");



class nod
{
       int val;
       nod * urm;
       friend class Graf;


   public:
       int get_val(){ return val; }
       nod * get_urm() { return urm; }
      // friend ostream& operator<<(ostream& f,const Graf& G);

       nod * operator=(const nod *& n);
};



class Graf
{

       nod *v[100];
       int nr_legaturi[100];
       int nr_noduri;
  public:
//      Graf()
//      {
//          cout<<"ca"<<'\n';
//      }
        friend istream& operator>>(istream& f, Graf &G);
        friend ostream& operator<<(ostream& f,const Graf& G);
        friend operator+(const Graf& G);

        friend void afisare_vector(int v[],int nr_elem);

        void adaug_final(int poz,int valoare); //functie care adauga pe v[poz] in vector elementul val la finalul listei respective
        void parcurgere_adancime(int nod_plecare,int val[],int &nr_elemente,int viz[]);
        void parcurgere_latime(int nod_plecare,int val[],int &nr_elemente);

        void DFS_cu_afisare(int nod_plecare);
        void BFS_cu_afisare(int nod_plecare);

        void MatriceaExistenteiDrumurilor();
        int ComponenteConexe(int);
        void Conex();

        bool CautValoare(int ,int );
        Graf& operator+(const Graf& G);
        Graf& operator=(const Graf& G);

};


istream& operator>>(istream& f, Graf &G)
{
    f>>G.nr_noduri;
    int x,y;

    for(int i=0;i<G.nr_noduri;i++)
    {
        f>>x>>y;
        G.v[x]=NULL;
        G.nr_legaturi[x]=y;

        for(int j=0;j<G.nr_legaturi[x];j++)
        {
            f>>y;
            G.adaug_final(x,y);
        }

    }
    return f;
}

ostream& operator<<(ostream& f, const Graf &G)
{
    cout<<G.nr_noduri<<'\n';

    for(int i=0;i<G.nr_noduri;i++)
    {
        nod *p=G.v[i];
        cout<<i<<' '<<G.nr_legaturi[i]<<' ';
        while(p!=NULL)
        {
            cout<<p->get_val()<<' ';
            p=p->get_urm();
        }
        cout<<'\n';


     /*  varianta 2 pentru functie friend in clasa nod
      for(nod *p=G.v[i];p!=NULL;p=p->urm)
        cout<<p->val<<' ';*/
    }

    return f;
}

void Graf::adaug_final(int poz,int valoare)
{

    nod *p;
    p=new nod;
    p->urm=NULL;
    p->val=valoare;

    if(v[poz]==NULL)v[poz]=p;
    else
    {
       nod *q=v[poz];
       while(q->urm!=NULL)q=q->urm;
       q->urm=p;
    }


}


void Graf::parcurgere_adancime(int nod_plecare,int val[],int &nr_elemente,int viz[])
{
    val[nr_elemente++]=nod_plecare;
    viz[nod_plecare]=1;
    for(nod *p=v[nod_plecare];p!=NULL;p=p->urm)
        if(!viz[p->val])
            parcurgere_adancime(p->val,val,nr_elemente,viz);

}


void Graf::parcurgere_latime(int nod_plecare,int val[],int &nr_elemente)
{
    int c[10000],viz[100];

    for(int i=0;i<nr_noduri;i++)
        viz[i]=0;

    int p=0,u=0;
    viz[nod_plecare]=1;
    c[p]=nod_plecare;
    while(p<=u)
    {
        nod_plecare=c[p++];
        val[nr_elemente++]=nod_plecare;
        for(nod *p=v[nod_plecare];p!=NULL;p=p->urm)
                   if(!viz[p->val])
        {
            c[++u]=p->val;
            viz[p->val]=1;

        }
    }
}


void afisare_vector(int v[],int nr)
{
    for(int i=0;i<nr;i++)
        cout<<v[i]<<' ';
    cout<<'\n';
}

void Graf::DFS_cu_afisare(int nod_plecare)
{
    int viz[100],val[100],nr_elem=0;
    for(int i=0;i<nr_noduri;i++)
        viz[i]=0;
    parcurgere_adancime(nod_plecare,val,nr_elem,viz);

    cout<<"Elementele in ordinea parcurgerii pornind din nodul "<<nod_plecare<<" sunt : ";
    afisare_vector(val,nr_elem);

}

void Graf::BFS_cu_afisare(int nod_plecare)
{
    int val[100],nr_elem=0;
    parcurgere_latime(nod_plecare,val,nr_elem);

    cout<<"Elementele in ordinea parcurgerii pornind din nodul "<<nod_plecare<<" sunt : ";
    afisare_vector(val,nr_elem);

}


int Graf::ComponenteConexe(int ok)
{
    //daca ok=1 atunci afisam componentele conexe. daca e 0 nu le afisam
    int viz[100],nr=0,val[100],nr_elem=0;
    for(int i=0;i<nr_noduri;i++)
        viz[i]=0;

    for(int i=0;i<nr_noduri;i++)
        if(!viz[i])
    {
        nr++;
        parcurgere_adancime(i,val,nr_elem,viz);

        if(ok)
           afisare_vector(val,nr_elem);
        nr_elem=0;
    }
    return nr;
}



void Graf::Conex()
{
    int nr=ComponenteConexe(0);
    if(nr!=1)cout<<"\nGraful nu e conex";
    else cout<<"\nGraful e conex";
}

void Graf::MatriceaExistenteiDrumurilor()
{

    int d[100][100];
    for(int i=0;i<nr_noduri;i++)
        for(int j=0;j<nr_noduri;j++)
            d[i][j]=0;

    for(int i=0;i<nr_noduri;i++)
    {
        for(nod *p=v[i];p!=NULL;p=p->urm)
            d[i][p->val]=1;
    }

    for(int i=0;i<nr_noduri;i++)
        for(int j=0;j<nr_noduri;j++)
            for(int k=0;k<nr_noduri;k++)
              if(i!=j && i!=k && k!=j && d[i][k] && d[k][j])
                d[i][j]=1;
    for(int i=0;i<nr_noduri;i++)
    {
        for(int j=0;j<nr_noduri;j++)
            cout<<d[i][j]<<' ';
        cout<<'\n';
    }


}

nod* nod:: operator=(const nod *& n)
{
    val=n->val;
    urm=n->urm;
    return (this);
}

Graf& Graf::operator=(const Graf & G)
{
    nr_noduri=G.nr_noduri;
    for(int i=0;i<nr_noduri;i++)
    {
        nr_legaturi[i]=G.nr_legaturi[i];
        v[i]=NULL;
        for(nod *p=G.v[i];p;p=p->urm)
            adaug_final(i,p->val);
    }


    return (*this);
}

bool Graf::CautValoare(int poz,int x)
{
    //cauta in lista corespunzatoare pozitiei poz elementul x. Returneaza ultimul element din lista sau NULL daca s-a gasit.
    nod * p;
    for(nod *p=v[poz];p;p=p->urm)
    {
       //trebuie sa supraincarcam operatorul = pt nod
        if(p->val==x)return true;
    }

    return false;
}

Graf& Graf::operator+(const Graf& G)
{
   Graf *S;
   S=new Graf;
   (*S)=G;
   for(int i=0;i<nr_noduri;i++)
   {

       for(nod *p=v[i];p;p=p->urm)
       {

           bool gasit=S->CautValoare(i,p->val);
           if(gasit==false)
           {
               S->nr_legaturi[i]++;
               S->adaug_final(i,p->val);
           }

       }
   }
  // cout<<(*S) ;
   return (*S);
}



int main()
{
    Graf G;
    fin>>G;
    cout<<G;

    int opt,start;
    do
    {
        cout<<"\n1 : Parcurgere DFS\n2  : Parcurgere BFS\n3 : Construirea matricii existentei drumurilor\n4 : Determinarea componentelor conexe\n5 : Verificare daca graful e conex\n6 : Supraincarcarea operatorului + : reuniunea muchiilor a doua grafuri";
        cout<<"\nOptiunea dumnevoastra este : ";
        cin>>opt;

        switch(opt)
        {
           case 1:
                  cout<<"\nNodul de plecare este : ";
                  cin>>start;
                  G.DFS_cu_afisare(start);
                  break;
           case 2:
                  cout<<"\nNodul de plecare este : ";
                  cin>>start;
                  G.BFS_cu_afisare(start);
                  break;

           case 3:G.MatriceaExistenteiDrumurilor();
                  break;
           case 4: G.ComponenteConexe(1);
                   break;
           case 5: G.Conex();
                   break;
           case 6: Graf A,S;
                   fin>>A;
                   S=A+G;
                   cout<<S;

        }
    }
    while(opt!=0);
    return 0;
}
