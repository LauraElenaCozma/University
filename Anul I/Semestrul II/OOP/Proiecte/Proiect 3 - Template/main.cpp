#include <iostream>
#include <cstring>
using namespace std;

template <class T> class vector;
template <class T> ostream& operator<<(ostream& ,const vector<T> & ob);
template <class T> istream& operator>> (istream& in, vector<T> & ob);


template <class T>
class vector
{

    T* a;
    int nr_elem ;   //cate elemente avem in total
    int dim ;       //cat am alocat

public:

    class iterator
    {
        /*
        iteratorii sunt folositi pentru a parcurge elementele dintr-o lista / dintr-un vector
        */
        T* element;
    public:
        iterator(T* el) : element(el) {};

        //muta iteratorul mai la stanga

        iterator& operator++()
        {
            ///prefixat
            this->element++;
            return (*this);
        }

        iterator operator++(int )
        {
            ///postfixat
            iterator aux=*this;
            this->element++;
            return aux;
        }

        iterator& operator--()
        {
            ///prefixat
            this->element--;
            return (*this);
        }

        iterator operator--(int )
        {
            ///postfixat
            iterator aux=*this;
            this->element--;
            return aux;
        }


        //== si != pentru a compara doi iteratori

        bool operator==(const iterator& ob)
        {
            if(element==ob.element)return 1;
            return 0;
        }

        bool operator!=(const iterator& ob)
        {
            if(element!=ob.element)return 1;
            return 0;
        }


        // operatorul * pentru a accesa elementul din vector (sa pot scrie *it in loc de *it.element)
       T& operator*()
       {
           return (*element);
       }


       T* operator->()
       {
           ///la ce il folosesc?
           return element;
       }

    };

    // orice clasa care implementeaza iteratori are o metoda begin, care intoarce un iterator la primul element
    iterator begin() const { return iterator(a); }


    // si o metoda end, care intoarce un iterator catre elementul de dupa ultimul element
    iterator end() const { return iterator(a + nr_elem); }


    vector();
    vector(int nr, T val);
    vector(const vector& ob);
    ~vector();

    vector& operator=(const vector& ob);

    void push_back(T x);
    void pop_back();
    void insert(T val,int poz);
    void remove(int poz);

    T& operator[](int poz);
    operator bool() const;
    operator int() const;
    friend istream& operator>> < > (istream& in, vector<T> & ob);
    friend ostream& operator << < > (ostream& ,const vector<T> & ob);

};

template <class T>
vector<T>::vector()
{

    nr_elem=0;
    dim=0;
    a=NULL;
}

template <class T>
vector<T>::vector(int nr,T val)
{

    a=new T[nr];
    nr_elem=dim=nr;
    for(vector::iterator i = this->begin(); i!= this->end(); ++i)
        (*i)=val;
}

template <class T>
vector<T>::vector(const vector& ob)
{
    a=new T[ob.dim];
    nr_elem=ob.nr_elem;
    dim=ob.dim;
    vector::iterator j=this->begin();
    for(vector::iterator i = ob.begin(); i!= ob.end(); ++i,++j)
        (*j)=(*i);


}

template <class T>
vector<T>::~vector()
{
    delete[] a;
    dim = 0;
    nr_elem = 0;
}

template <class T>
vector<T>& vector<T>::operator=(const vector& ob)
{
    delete []a;
    a=new T[ob.dim];
    nr_elem=ob.nr_elem;
    dim=ob.dim;
    vector::iterator j=this->begin();
    for(vector::iterator i = ob.begin(); i!= ob.end(); ++i,++j)
        (*j)=(*i);

    return (*this); ///de verificat

}

template <class T>
void vector<T>::push_back(T x)
{
    vector aux=(*this);
    delete[] a;
    if(dim<nr_elem+1)dim=2*dim;
    if(dim==0)dim=1;
    nr_elem++;
    a=new T[dim];
    vector::iterator j=this->begin() , i=aux.begin();
    for(; i!=aux.end() ; ++i , ++j)
        (*j)=(*i);

    (*j)=x;


}
template <class T>
void vector<T>::pop_back()
{
    try
    {
        if(nr_elem==0)
            throw 1;
        nr_elem--;
    }
    catch(int)
    {
        cout<<"\nNu avem ce sa stergem deoarece vectorul e vid.";
    }

}

template <class T>
void vector<T>::insert(T val,int poz)
{
    try
    {
        if(nr_elem<poz || poz<0)
            throw 1;

        vector aux=(*this);
        nr_elem++;
        if(dim<nr_elem+1)dim*=2;
        if(dim==0)dim=1;

        a=new T[dim];
        vector::iterator i=aux.begin() , j=this->begin();
        for( ; i!=aux.a+poz ; i++,j++)
            (*j)=(*i);
        (*j)=val;
        j++;
        for( ; i!=aux.end();i++,j++)
            (*j)=(*i);
    }
    catch(int)
    {
        cout<<"Pozitia pe care se doreste inserarea depaseste numarul de elemente ale vectorului.\n";
    }


}

template <class T>
void vector<T>::remove(int poz)
{
    try
    {
        if(nr_elem<=poz || poz<0)   //elementele sunt de pe pozitiile 0 ... nr_elem deci ce depaseste nu exista
            throw 1;
        if(nr_elem==0)
            throw 'a';

        vector::iterator i=a+poz , j=a+poz+1;
        if(i!=end())
        {   //daca a+poz+1 nu depaseste vectorul

            while(j!=end())
            {
                (*i)=(*j);
                i++;
                j++;
            }
        }
        nr_elem--;

    }

    catch(int)
    {
        cout<<"Pozitia de pe care se doreste stergerea depaseste numarul de elemente ale vectorului.\n";
    }
    catch(char)
    {
        cout<<"Nu mai sunt elemente in vector. Nu se mai poate elimina.\n";
    }

}
template <class T>
T& vector<T>::operator[](int poz)
{
    try
    {
        if(poz>=nr_elem || poz<0)
            throw 1;


    }
    catch(int )
    {
        cout<<"Nu se poate accesa elementul. Se iese din dimensiunea vectorului. \n";
    }
    return *(a+poz);

}

template <class T>
vector<T>::operator bool() const
{
    if(nr_elem==0)return false;
    return true;
}

template <class T>
vector<T>::operator int() const
{
    ///size=dimensiune sau nr elemente?
    return dim;
}

template <class T>
ostream& operator << (ostream& f,const vector<T> & ob)
{

   for(typename vector<T>::iterator b = ob.begin(); b != ob.end(); ++b)
            f<<*b<<' ';
    cout<<'\n';
    return f;

}


template <class T>
istream& operator>> (istream& in, vector<T> & ob)
{
    delete[] ob.a;
    cout<<"\nNumarul de elemente: ";
    in>>ob.nr_elem;
    cout<<"\nDimensiunea alocata: ";
    in>>ob.dim;

    try
    {
        if(ob.dim<ob.nr_elem)
            throw 1;
            ob.a=new T[ob.dim];
            for(int i=0;i<ob.nr_elem;i++)
                in>>ob.a[i];
            return in;
    }
    catch(int)
    {
        cout<<"\nDatele de intrare sunt incorecte. Trebuie sa citim o dimensiune mai mare.\n";
    }


}


template < > class vector<char*>;
template< > ostream& operator << (ostream& f,const vector<char*> & ob);
template< > istream& operator>> (istream& in, vector<char*> & ob);
/// Specializare pentru char*
template < >
class vector <char * >
{

    char **a;
    int nr_elem ;   //cate elemente avem in total
    int dim ;       //cat am alocat

public:

    class iterator
    {
        /*
        iteratorii sunt folositi pentru a parcurge elementele dintr-o lista / dintr-un vector
        */
        char ** element;
    public:
        iterator(char ** el) : element(el)
            {
            }

        //muta iteratorul mai la stanga

        iterator& operator++()
        {
            ///prefixat
            this->element++;
            return (*this);
        }

        iterator operator++(int )
        {
            ///postfixat
            iterator aux=*this;
            this->element++;
            return aux;
        }

        iterator& operator--()
        {
            ///prefixat
            this->element--;
            return (*this);
        }

        iterator operator--(int )
        {
            ///postfixat
            iterator aux=*this;
            this->element--;
            return aux;
        }


        //== si != pentru a compara doi iteratori

        bool operator==(const iterator& ob)
        {
            if(element==ob.element)return 1;
            return 0;
        }

        bool operator!=(const iterator& ob)
        {
            if(element!=ob.element)return 1;
            return 0;
        }


        // operatorul * pentru a accesa elementul din vector (sa pot scrie *it in loc de *it.element)
       char*& operator*()
       {
           return (*element);
       }


       char** operator->()
       {
           ///la ce il folosesc?
           return element;
       }

    };

    // orice clasa care implementeaza iteratori are o metoda begin, care intoarce un iterator la primul element
    iterator begin() const { return iterator(a); }


    // si o metoda end, care intoarce un iterator catre elementul de dupa ultimul element
    iterator end() const { return iterator(a + nr_elem); }


    vector();
    vector(int nr, char* val);
    vector(const vector& ob);
    ~vector();

    vector& operator=(const vector& ob);

    void push_back(char* x);
    void pop_back();
    void insert(char* val,int poz);
    void remove(int poz);

    char*& operator[](int poz);
    operator bool() const;
    operator int() const;
    friend istream& operator>>(istream& in, vector<char*> & ob);
    friend ostream& operator << (ostream& ,const vector<char*> & ob);

};



vector<char*>::vector()
{

    nr_elem=0;
    dim=0;
    a=NULL;
}


vector<char*>::vector(int nr,char* val)
{

    a=new char*[nr];
    nr_elem=dim=nr;
    for(vector<char*>::iterator i = this->begin(); i!= this->end(); ++i)
        {
            (*i)=new char[strlen(val)+1];
            strcpy((*i),val);
        }
}


vector<char*>::vector(const vector& ob)
{

    a=new char*[ob.dim];
    nr_elem=ob.nr_elem;
    dim=ob.dim;
    vector::iterator j=this->begin();
    for(vector::iterator i = ob.begin(); i!= ob.end(); ++i,++j)
        {
            (*j)=new char[strlen(*i)+1];
            strcpy((*j),(*i));
        }

}


vector<char*>::~vector()
{
    for(int i=0;i<nr_elem;i++)
        delete[] a[i];
    delete[] a;
    dim = 0;
    nr_elem = 0;
}


vector<char*>& vector<char*>::operator=(const vector<char*>& ob)
{
    for(vector::iterator i = this->begin(); i!= this->end(); ++i)
        delete[] (*i);
    delete []a;
    a=new char*[ob.dim];
    nr_elem=ob.nr_elem;
    dim=ob.dim;
    vector::iterator j=this->begin();
    for(vector::iterator i = ob.begin(); i!= ob.end(); ++i,++j)
        {

            (*j)=new char[strlen(*i)+1];
            strcpy((*j),(*i));
        }

    return (*this); ///de verificat

}


void vector<char*>::push_back(char* x)
{
    vector aux=(*this);
    delete[] a;
    if(dim<nr_elem+1)dim=2*dim;
    if(dim==0)dim=1;
    nr_elem++;
    a=new char*[dim];
    vector::iterator j=this->begin() , i=aux.begin();
    for(; i!=aux.end() ; ++i , ++j)
        {
            (*j)=new char[strlen(*i)+1];
            strcpy((*j),(*i));
        }

    (*j)=new char[strlen(x)+1];
    strcpy((*j),x);


}

void vector<char*>::pop_back()
{
    nr_elem--;
}


void vector<char*>::insert(char* val,int poz)
{
    try
    {
        if(nr_elem<poz || poz<0)
            throw 1;

        vector aux=(*this);
        nr_elem++;
        if(dim<nr_elem)dim*=2;
        if(dim==0)dim=1;
        for(vector::iterator i=this->begin();i!=this->end();i++)
            delete[] (*i);
        delete[ ] a;
        a=new char*[dim];
        vector<char*>::iterator i=aux.begin() , j=this->begin();
        for( ; i!=aux.a+poz ; i++,j++)
            {
                (*j)=new char[strlen(*i)+1];
                strcpy((*j),(*i));
            }
        (*j)=new char[strlen(val)+1];
        strcpy((*j),val);
        j++;
        for( ; i!=aux.end();i++,j++)
            {
                (*j)=new char[strlen(*i)+1];
                strcpy((*j),(*i));
            }
    }
    catch(int)
    {
        cout<<"Pozitia pe care se doreste inserarea depaseste numarul de elemente ale vectorului.\n";
    }


}



void vector<char*>::remove(int poz)
{
    try
    {
        if(nr_elem<=poz || poz<0)   //elementele sunt de pe pozitiile 0 ... nr_elem deci ce depaseste nu exista
            throw 1;
        if(nr_elem==0)
            throw 'a';

        vector::iterator i=a+poz , j=a+poz+1;
        if(i!=end())
        {   //daca a+poz+1 nu depaseste vectorul

            while(j!=end())
            {
                (*i)=new char[strlen(*j)+1];
                strcpy((*i),(*j));
                i++;
                j++;
            }
        }
        nr_elem--;

    }

    catch(int)
    {
        cout<<"Pozitia de pe care se doreste stergerea depaseste numarul de elemente ale vectorului.\n";
    }
    catch(char)
    {
        cout<<"Nu mai sunt elemente in vector. Nu se mai poate elimina.\n";
    }

}

char*& vector<char*>::operator[](int poz)
{
    try
    {
        if(poz>=nr_elem || poz<0)
            throw 1;


    }
    catch(int )
    {
        cout<<"Nu se poate accesa elementul. Se iese din dimensiunea vectorului. \n";
    }
    return *(a+poz);

}


vector<char*>::operator bool() const
{
    if(nr_elem==0)return false;
    return true;
}


vector<char*>::operator int() const
{
    ///size=dimensiune sau nr elemente?
    return dim;
}


ostream& operator << (ostream& f,const vector<char*> & ob)
{

   for(typename vector<char*>::iterator b = ob.begin(); b != ob.end(); ++b)
            f<<*b<<' ';
    cout<<'\n';
    return f;

}



istream& operator>> (istream& in, vector<char*> & ob)
{
    //for(vector<char*>::iterator i=ob.begin();i!=ob.end();++i)
    //    delete[] (*i);
    delete[] ob.a;
    cout<<"\nNumarul de elemente: ";
    in>>ob.nr_elem;
    cout<<"\nDimensiunea alocata: ";
    in>>ob.dim;
    try
    {
        if(ob.dim<ob.nr_elem)
            throw 1;
        ob.a=new char*[ob.dim];
        for(int i=0;i<ob.nr_elem;i++)
        {
        char cuv[100];
        in>>cuv;
        ob.a[i]=new char[strlen(cuv)+1];
        strcpy(ob.a[i],cuv);
        }

        return in;
    }
    catch(int)
    {
        cout<<"\nDatele de intrare sunt incorecte. Trebuie sa citim o dimensiune mai mare.\n";
    }

}




int main()
{
    int opt;
    char val[100];
    int poz;
    vector <char *> v;
    do
    {
        cout<<"\n0 : Iesire. ";
        cout<<"\n1 : Push back. ";
        cout<<"\n2 : Pop_back. ";
        cout<<"\n3 : Insert. ";
        cout<<"\n4 : Remove. ";
        cout<<"\n5 : Modifica valoarea unui element accesandu-l prin pozitie. ";
        cout<<"\n6 : Verifica daca mai sunt elemente in vector. ";
        cout<<"\n7 : Afiseaza dimensiunea vectorului. ";
        cout<<"\n8 : Citeste vectorul. ";
        cout<<"\n9 : Afiseaza vectorul. ";
        cout<<"\n       Optiunea ta este: ";
        cin>>opt;

        switch(opt)
        {
        case 1:
            cout<<"\nCiteste valoarea adaugata: ";
            cin>>val;
            v.push_back(val);
            break;
        case 2:
            v.pop_back();
            break;
        case 3:
            cout<<"\nCiteste valoarea adaugata si pozitia: ";
            cin>>val>>poz;
            v.insert(val,poz);
            break;
        case 4:
            cout<<"\nCiteste pozitia de pe care se sterge: ";
            cin>>poz;
            v.remove(poz);
            break;
        case 5:
            cout<<"\nCiteste pozitia: ";
            cin>>poz;
            cout<<"\nCiteste noua valoare: ";
            cin>>val;
            v[poz]=val;
            break;
        case 6:
            if(v)cout<<"\nMai sunt elemente in vector.\n";
            else cout<<"\nNu mai sunt elemente in vector.\n";
            break;
        case 7:
            cout<<(int)v<<'\n';
            break;
        case 8:cin>>v;
            break;
        case 9:
            cout<<"\n"<<v;
            break;
        }
    }
    while(opt!=0);


    return 0;
}
