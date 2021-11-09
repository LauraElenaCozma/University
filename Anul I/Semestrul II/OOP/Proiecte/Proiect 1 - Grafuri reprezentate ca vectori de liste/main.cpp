#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("date.in");

class Graf;

class nod
{
       int val;
       nod * urm;
       friend class Graf;


   public:

       friend ostream& operator<<(ostream& f,const Graf& G);
       friend istream& operator>>(istream& f, Graf &G);

       nod * operator=(const nod *& n);
};



class Graf
{

       nod **v;     // vector de liste. pe v[i]->val se afla nr de muchii care pleaca/intra in i, dar in nodurile urmatoare etichetele nodurilor muchiilor
       int nr_noduri;   //numar de noduri ale grafului

  public:
        Graf()          //constructor de initializare. Daca declaram un obiect si nu il citim, atunci cand facem destructorul nr_noduri=0 si nu va intra in for pentru ca nu are nimic de dezalocat
        {
            nr_noduri=0;
            v=NULL;
        }

        Graf(const Graf& G)
        {
            nr_noduri=G.nr_noduri;
            v=new nod*[G.nr_noduri];
            for(int i=0;i<nr_noduri;i++)
            {
                v[i]=new nod;
                v[i]->val=G.v[i]->val;
                v[i]->urm=NULL;

                for(nod *q=G.v[i]->urm;q;q=q->urm)
                    adaug_inceput(i,q->val);
            }
        }
        ~Graf()
        {
               for(int i=0;i<nr_noduri;i++)
                 {
                     nod *p,*q;
                     p=v[i]->urm;   //incepem stergerea cu primul element care are etichetele nodurilor
                     if(p!=NULL)    //daca lista e vida nu avem cum sa mergem pe null->urm
                    {
                         q=p->urm;

                         while(p!=NULL)
                             {
                                 p->urm=NULL;
                                 delete p;              //dezalocam
                                 p=q;
                                 if(q!=NULL)q=q->urm;   //daca q e null, nu putem face q->urm
                             }

                         v[i]=NULL;

                    }

                }

                 delete[] v;

        }

        friend istream& operator>>(istream& f, Graf &G);
        friend ostream& operator<<(ostream& f,const Graf& G);

        Graf& operator+(const Graf& G);
        Graf& operator=(const Graf& G);


        void adaug_inceput(int poz,int valoare); //functie care adauga pe v[poz]->urm elementul val



        void parcurgere_adancime(int nod_plecare,int val[],int &nr_elemente,int viz[]);
        void parcurgere_latime(int nod_plecare,int val[],int &nr_elemente);

        void DFS_cu_afisare(int nod_plecare);
        void BFS_cu_afisare(int nod_plecare);


        void MatriceaExistenteiDrumurilor();

        int ComponenteConexe(int);
        void Conex();

        friend void afisare_vector(int v[],int nr_elem);   //ne ajuta la afisarea drumurilor la bfs si dfs
        bool CautValoare(int ,int );

};


istream& operator>>(istream& f, Graf &G)
{
    //functie de citire a unui graf
    f>>G.nr_noduri;
    int x,y;

    G.v=new nod*[G.nr_noduri];

    for(int i=0;i<G.nr_noduri;i++)
    {
        f>>x>>y;
        G.v[x]=new nod;
        G.v[x]->val=y; //numarul de legaturi
        G.v[x]->urm=NULL;

        for(int j=0;j<G.v[x]->val;j++)
        {
            f>>y;                 //muchie intre i si y
            G.adaug_inceput(x,y);
        }

    }
    return f;
}

ostream& operator<<(ostream& f, const Graf &G)
{
    //functie de afisare a unui graf
    cout<<G.nr_noduri<<'\n';

    for(int i=0;i<G.nr_noduri;i++)
    {
       cout<<i<<' ';

     for(nod *p=G.v[i];p!=NULL;p=p->urm)
        cout<<p->val<<' ';
       cout<<'\n';
    }

    return f;
}

void Graf::adaug_inceput(int poz,int valoare)
{
    //functie care adauga la inceput un nod in lista corespunzatoare lui v[poz] dupa v[poz]
    nod *p;
    p=new nod;
    p->val=valoare;

    p->urm=v[poz]->urm;
    v[poz]->urm=p;   //inseram dupa v[poz]


}


void afisare_vector(int v[],int nr)
{
    //functie care afiseaza un vector de n elemente
    for(int i=0;i<nr;i++)
        cout<<v[i]<<' ';
    cout<<'\n';
}


void Graf::parcurgere_adancime(int nod_plecare,int val[],int &nr_elemente,int viz[])
{
    val[nr_elemente++]=nod_plecare;   //punem in vectorul val elementele din parcurgere incepand cu nodul de plecare
    viz[nod_plecare]=1;               //vizitam nodul
    for(nod *p=v[nod_plecare]->urm;p!=NULL;p=p->urm)   //vecinii nodului curent
        if(!viz[p->val])
            parcurgere_adancime(p->val,val,nr_elemente,viz);

}


void Graf::parcurgere_latime(int nod_plecare,int *val,int &nr_elemente)
{
    int *c,*viz;

    c=new int[1000];
    viz=new int[nr_noduri];
    for(int i=0;i<nr_noduri;i++)
        viz[i]=0;

    int p=0,u=0;
    viz[nod_plecare]=1;
    c[p]=nod_plecare;
    while(p<=u)                                          //cat timp coada nu e goala
    {
        nod_plecare=c[p++];
        val[nr_elemente++]=nod_plecare;
        for(nod *p=v[nod_plecare]->urm;p!=NULL;p=p->urm)  //vecinii nodului curent
            if(!viz[p->val])
            {
                c[++u]=p->val;
                viz[p->val]=1;

            }
    }
    delete[] c;
}




void Graf::DFS_cu_afisare(int nod_plecare)
{
    //functie care apeleaza parcurgerea in adancime si afiseaza elementele in ordinea parcurgerii, conform optiunii
    if(!(nod_plecare>=0 && nod_plecare<nr_noduri)){ cout<<"\nDate invalide\n";return;}
    int *viz,*val,nr_elem=0;

    viz=new int[nr_noduri];
    val=new int[nr_noduri];

    for(int i=0;i<nr_noduri;i++)
        viz[i]=0;

    parcurgere_adancime(nod_plecare,val,nr_elem,viz);

    cout<<"Elementele in ordinea parcurgerii pornind din nodul "<<nod_plecare<<" sunt : ";
    afisare_vector(val,nr_elem);

    delete[] viz;
    delete[] val;

}

void Graf::BFS_cu_afisare(int nod_plecare)
{
    //functie care apeleaza parcurgerea in latime si afiseaza elementele in ordinea parcurgerii, conform optiunii
    if(!(nod_plecare>=0 && nod_plecare<nr_noduri)){ cout<<"\nDate invalide\n";return;}
    int *val,nr_elem=0;
    val=new int[nr_noduri];
    parcurgere_latime(nod_plecare,val,nr_elem);

    cout<<"Elementele in ordinea parcurgerii pornind din nodul "<<nod_plecare<<" sunt : ";
    afisare_vector(val,nr_elem);
    delete[] val;

}


int Graf::ComponenteConexe(int ok)
{
    //daca ok=1 atunci afisam componentele conexe. daca e 0 nu le afisam
    int *viz,nr=0,*val,nr_elem=0;
    viz=new int[nr_noduri];
    val=new int[nr_noduri];

    for(int i=0;i<nr_noduri;i++)
        viz[i]=0;

    for(int i=0;i<nr_noduri;i++)
        if(!viz[i])  //daca nu e vizitat nodul, inseamna ca e o noua componenta conexa
    {
        nr++;
        parcurgere_adancime(i,val,nr_elem,viz);

        if(ok)      //ok==1 inseamna ca e selectata optiunea de afisare a componentelor conexe. ok=0 inseamnca ca verificam daca graful e conex si nu trebuie sa mai afisam componentele conexe
           afisare_vector(val,nr_elem);
        nr_elem=0;
    }
    delete[] viz;
    delete[] val;
    return nr;
}



void Graf::Conex()
{
    //verificare daca graful e conex
    int nr=ComponenteConexe(0);
    if(nr!=1)cout<<"\nGraful nu e conex!\n";
    else cout<<"\nGraful e conex!\n";
}

void Graf::MatriceaExistenteiDrumurilor()
{
    //construirea matricii drumurilor
    int **d;

    d=new int*[nr_noduri];

    for(int i=0;i<nr_noduri;i++)
    {
        d[i]=new int[nr_noduri];
        for(int j=0;j<nr_noduri;j++)
            d[i][j]=0;
    }


    for(int i=0;i<nr_noduri;i++)
    {
        for(nod *p=v[i]->urm;p!=NULL;p=p->urm)
            d[i][p->val]=1;
    }

    for(int i=0;i<nr_noduri;i++)
        for(int j=0;j<nr_noduri;j++)
            for(int k=0;k<nr_noduri;k++)
              if(i!=j && i!=k && k!=j && d[i][k] && d[k][j])
                d[i][j]=1;    //daca e drum de la i la k si de la k la j inseamnca ca e si de la i la j
    for(int i=0;i<nr_noduri;i++)
    {
        for(int j=0;j<nr_noduri;j++)
            cout<<d[i][j]<<' ';
        cout<<'\n';
    }

    //dezalocarea matricii d
    for(int i=0;i<nr_noduri;i++)
        delete[] d[i];
    delete[] d;


}

nod* nod:: operator=(const nod *& n)
{
    //supraincarcarea operatorului egal pentru nod
    val=n->val;
    urm=n->urm;
    return (this);
}

Graf& Graf::operator=(const Graf & G)
{
    //supraincarcarea operatorului egal pentru graf
    nr_noduri=G.nr_noduri;
    v=new nod*[nr_noduri];
    for(int i=0;i<nr_noduri;i++)
    {
        v[i]=new nod;
        v[i]->urm=NULL;
        v[i]->val=G.v[i]->val;
        for(nod *p=G.v[i]->urm;p;p=p->urm)
            adaug_inceput(i,p->val);
    }


    return (*this);   //returnam obiectul curent
}

bool Graf::CautValoare(int poz,int x)
{
    //cauta in lista corespunzatoare pozitiei poz elementul x. Returneaza ultimul element din lista sau NULL daca s-a gasit.
    nod * p;
    for(nod *p=v[poz]->urm;p;p=p->urm)
    {
       //trebuie sa supraincarcam operatorul = pt nod
        if(p->val==x)return true;
    }

    return false;
}

Graf& Graf::operator+(const Graf& G)
{
    //facem reuniunea muchiilor
   Graf *S;
   S=new Graf;
   (*S)=G;
   for(int i=0;i<nr_noduri;i++)
   {

       for(nod *p=v[i]->urm;p;p=p->urm)
       {

           bool gasit=S->CautValoare(i,p->val);
           if(gasit==false)   //daca muchia cautata nu e deja in graful S o adaugam
           {
               S->v[i]->val++;  //marim numarul de muchii
               S->adaug_inceput(i,p->val);
           }

       }
   }

   return (*S);
}



int main()
{
    Graf *G;
    int n,poz;
    fin>>n;
    G=new Graf[n];
    cout<<"\nLa inceputul acestui program se vor citi "<<n<<" obiecte de tip graf\n";

    for(int i=0;i<n;i++)
    {
        fin>>G[i];
        cout<<G[i]<<'\n';
    }

    cout<<"\nCerintele se vor aplica pentru graful cu numarul :";
    cin>>poz;
    cout<<"\nConfiguratia grafului ales este : \n";
    cout<<G[poz];

    Graf B(G[poz]);
    cout<<"\n\n\nCOPY CONSTRUCTOR\n\n\n"<<B;

    int opt,start;
    do
    {
        cout<<"\n0 : Iesire\n1 : Parcurgere DFS\n2 : Parcurgere BFS\n3 : Construirea matricii existentei drumurilor\n4 : Determinarea componentelor conexe\n5 : Verificare daca graful e conex\n6 : Supraincarcarea operatorului + : reuniunea muchiilor a doua grafuri";
        cout<<"\nOptiunea dumnevoastra este : ";
        cin>>opt;

        switch(opt)
        {
           case 1:
                  cout<<"\nNodul de plecare este : ";
                  cin>>start;
                  G[poz].DFS_cu_afisare(start);
                  break;
           case 2:
                  cout<<"\nNodul de plecare este : ";
                  cin>>start;
                  G[poz].BFS_cu_afisare(start);
                  break;

           case 3:G[poz].MatriceaExistenteiDrumurilor();
                  break;
           case 4: G[poz].ComponenteConexe(1);
                   break;
           case 5: G[poz].Conex();
                   break;
           case 6: Graf S;
                   int poz2;
                   cout<<"\nAl doilea graf ales pentru adunare este :";
                   cin>>poz2;
                   S=G[poz]+G[poz2];
                   cout<<S;
                   break;


        }
    }
    while(opt!=0);

    delete [] G;
    return 0;
}



/*
4
6
0 1 3
1 1 2
2 1 1
3 2 0 4
4 1 3
5 0

6
0 2 1 5
1 3 0 3 5
2 0
3 2 1 4
4 2 3 5
5 3 1 4 0

6
0 0
1 1 2
2 1 1
3 0
4 0
5 0

6
0 3 1 5 2
1 3 0 3 5
2 1 0
3 2 1 4
4 2 3 5
5 3 1 4 0

*/
