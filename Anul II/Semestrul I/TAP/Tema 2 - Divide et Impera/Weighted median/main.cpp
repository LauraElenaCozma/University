#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;
ifstream fin("f.in");

void read(vector <int> &v , int &lengthV , vector <float> &w)
{
    fin>>lengthV;
    v.resize(lengthV);
    w.resize(lengthV);
    for(int i=0 ; i<lengthV ; i++)
        fin>>v[i];
    for(int i=0 ; i<lengthV ; i++)
        fin>>w[i];

}


int pivot(vector <int> &v , int lengthV , vector <float> &w , int left , int right , float &sumLeft , float &sumRight)
{
    int p = left;
    int q = right;
    int index = rand() % (right -left + 1) + left;

    swap(v[p] , v[index]);
    swap(w[p] , w[index]);
    int val = v[p];
    float weight = w[p];

    sumLeft = 0;
    sumRight = 0;
    while(p<q)
    {
        while(p < q && val < v[q])
        {

            q--;
        }
        v[p] = v[q];
        w[p] = w[q];
        while(p < q && val > v[p])
        {
            p++;
        }
        v[q] = v[p];
        w[q] = w[p];
    }
    v[p] = val;
    w[p] = weight;

    return p;

}

int divide(vector <int> &v , int lengthV , vector <float> &w , int left , int right)
{
    if(left <= right)
    {
        float sumLeft = 0, sumRight = 0;
        int p = pivot(v , lengthV , w , left , right , sumLeft , sumRight);

        for(int i = 0 ; i < p ; i++)
            sumLeft += w[i];

        for(int i = p+1 ; i < lengthV ; i++)
            sumRight += w[i];

        if(sumLeft < 0.5)
            if(sumRight <= 0.5)
                return v[p];
            else return divide(v , lengthV , w , p+1 , right);
        else return divide(v , lengthV , w , left , p);
    }
}
int main()
{
    vector <int> v;
    vector <float> w;
    int lengthV;
    read(v , lengthV , w);
    cout<<divide(v , lengthV , w , 0 ,lengthV - 1);

    return 0;
}
