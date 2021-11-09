#include <iostream>

using namespace std;

void inserareMinHeap(int v[],int n,int x)
{
    //inseram valoarea x intr-un minheap
    n++;
    int i=n/2,j=n;
    while(i>=1 && x<v[i])
    {
        v[j]=v[i];
        j/=2;
        i/=2;
    }
    v[j]=x;
}


void creareMinHeap(int v[],int &n)
{
    cin>>n;
    int x;
    cin>>x;
    v[1]=x;
    for(int i=2;i<=n;i++)
    {
        cin>>x;
        inserareMinHeap(v,i-1,x);
    }
}

int extractMin(int v[])
{
    return v[1];
}


/*void minHeapify(int v[],int n)
{
    //extragerea radacinii si restabilirea heapului
    v[1]=v[n];
    int x=v[1];
    n--;
    int poz;
    int i=1;
    while(i<=n)
    {

        if(2*i<=n)
        {
            if(x>=v[2*i])
                {
                    if(2*i+1<=n)
                    {
                       if(v[2*i]<v[2*i+1])poz=2*i; //fiul stang e mai mic ca cel drept
                       else poz=2*i+1;
                    }
                    else poz=2*i;// fiul drept nu exista
                }
            else
                {
                    if(2*i+1<=n)
                    {
                       if(x>=v[2*i+1])poz=2*i+1;
                       else return;
                    }
                    else return;

                }
        }
        else return ;
        swap(v[i],v[poz]);
        i=poz;
    }
}

*/


void minHeapify(int v[],int n)
{
    //eliminare radacina si reechilibrare heap
    v[1]=v[n];
    n--;
    int tata=1;
    int fiu=2;
    while(fiu<=n)
    {
        if(fiu<n)//exista si fiu drept
        {
            if(v[fiu+1]<v[fiu])fiu++;
        }
        if(v[tata]>v[fiu])
        {
            swap(v[tata],v[fiu]);
            tata=fiu;
            fiu=fiu*2;
        }
        else return ;
    }
}


void heapSort(int v[],int n)
{
    creareMinHeap(v,n);
    for(int i=n;i>=1;i--)
    {
        int minim=extractMin(v);
        cout<<minim<<' ';
        minHeapify(v,i);
    }


}
int main()
{
    int n,v[100];
    heapSort(v,n);

    return 0;
}
