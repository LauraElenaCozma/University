#include <iostream>

using namespace std;
/*template <class T>
class Singleton
{
    static T* inst;
    Singleton() {}
public:
    static T* instance();
};

template <class T>
T* Singleton<T>::inst=0;

template <class T>
T* Singleton<T>::instance()
{
    if(!Singleton<T>::inst)
        Singleton<T>::inst=new Singleton<T>;
    return Singleton<T>::inst;
}
*/

template <class T> class Singleton {
  public:
    static T *instance();
  private:
    Singleton(){}
    static T *instance_;
};

// Initialize the static instance pointer
template <class T>
  T *Singleton<T>::instance_ = 0;

// Global access point
template <class T>
T *Singleton<T>::instance() {
  // check for existing instance
  if (Singleton<T>::instance_ == 0) {
    // may want a try/catch here
    Singleton<T>::instance_ =
      new T;
  }
  return Singleton<T>::instance_;
};

class A
{

};

int main()
{
   A *a=Singleton<A>::instance();
   A *b=Singleton<A>::instance();
   cout<<a<<' '<<b;
   // class Singleton<int> *b;
   // b=b->instance();
    return 0;
}
