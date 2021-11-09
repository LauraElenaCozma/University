#include <iostream>

using namespace std;


template <class T>
class Singleton
{
    static T* inst1;
    static T* inst2;
    Singleton(){}
public:
    static T* instance()
    {
        if(!inst1)
            inst1=new T;
        else if(!inst2)
                {inst2=new T; return inst2;}
        return inst1;
    }
    ~Singleton()
    {
        delete inst1;
        delete inst2;
    }
};
template <class T>
T* Singleton<T>::inst1=0;
template <class T>
T* Singleton<T>::inst2=0;
int main()
{
    int *a=Singleton<int> :: instance();
    int *b=Singleton<int> :: instance();
    int *c=Singleton<int> :: instance();
    cout<<a<<' '<<b<<' '<<c;
    return 0;
}
