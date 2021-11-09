#include <iostream>

using namespace std;
template <class T>
class nod
{
public:
    T info;
    nod * next;

    nod(T info = 0 ,nod *next=NULL):
        info(info), next (next){}
};

template <class T>
class lista
{
private:
    nod<T> * prim;  ///!!!
public:
    lista(): prim(NULL){}
    void add(T i)
    {
        prim=new nod<T>(i,prim);
    }

    void afisare()
    {
        nod<T> *p=prim;
        while(p)
        {
            cout<<p->info<<' ';
            p=p->next;
        }
        cout<<'\n';
    }
};
class numar
{
    int x;
public:
    numar(int x): x(x){}

    friend std::ostream& operator<<(std::ostream& out,const numar& ob)
    {
        return out<<ob.x;
    }

    int operator++ ()
    {
        ++x;
        return x;
    }

    int operator++(int )//adica operatorul e postfixat
    {
        int aux=x;
        ++x;
        return aux;
    }
};

class item
{
    //trebuie sa implementeze toti operatorii care apar in lista si nod
    int x;
public:
    void afisare()
    {
        cout<<x<<endl;
    }
    item(int x): x(x){}

    operator bool ()
    {
        return x%2==0;
    }

    operator numar()
    {
        return numar(x);//face un nr cu val lui x
    }
    friend std::ostream& operator<<(std::ostream& out,const item& ob)
    {
        return out<<ob.x;
    }
};




template <class T>
class pointer
{
    T * p;
public:
    pointer(T val)
    {
        p=new T(val);
    }

    ~pointer()
    {
        delete p;
    }

    T * operator->()
    {
        return p;
    }

    T& operator * ()
    {
        return *p;
    }
};

class valid
{

};

int main()
{
  /*  pointer<int> p(5); //am facut un pointer care piinteaza la valoarea 5
    cout<<*p<<endl;
    *p=7;
    cout<<*p<<endl;*/


    /*pointer <item> pp(item(9));
    pp->afisare();*/

    item i(5);
    item ii(6);
    if(i)
    {
        cout<<"Da"<<endl;
    }
    if(ii)
        cout<<"Da2"<<endl;

      /*  numar n =(numar) i;
        cout<<n;*/

    //item * pi;  asta putem face
   // pi->
    /*lista<int> l;
    l.add(6);
    l.add(5);
    l.add(1);
    l.afisare();

    lista<double> d;
    d.add(32.43);
    d.add(-4.5);
    d.afisare();


    lista<item> i;
    i.add(item(7));
    i.afisare();
    numar n(5);
    cout<<n<<'\n';
    cout<<++n<<'\n';
    cout<<n++<<'\n';
    cout<<n<<'\n';*/
    return 0;
}
