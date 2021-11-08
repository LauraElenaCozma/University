#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cstdlib>
using namespace std;
ifstream fin("data.in");


class var
{
public:
    bool used;
    bool negated;

    var(bool U = false, bool N = false)
    {
        used = U;
        negated = N;
    }
};

class clause
{
public:
    vector <var> variables;
    int usedV;

    clause(int n)
    {
        variables.resize(n , 0);
        usedV = 0;
    }
};

int ok;
void checkSAT(int k , list <clause> &E , vector <int> &sol , int n)
{
        //E is empty. Found a solution
    if(E.empty())
    {
        ok = 1;
        cout<<"\nA solution is:\n";
        //k - 1 because k is incremented by 1 for this step
        for(int i = 0 ; i < k - 1 ; i++)
            cout<<sol[i]<<' ';
        return; //we have finised
    }

    //no more variables. The bkt ended, E is not empty and haven't found a solution
    if(k > n)
    {
        return ;
    }

    //save current state
    list <clause> copyE = E;

    list <clause>::iterator it;
    bool valid;
    for(int i = 0 ; i <= 1 ; i++)
    {
        sol[k - 1] = i;
        //we assume that the solution is valid
        valid = true;
        //go through the list E
        it = E.begin();
        while(it != E.end())
        {
            bool erased = false;
            if((*it).variables[k - 1].used) //if variable k is used in clause at iterator it
            {
                if((*it).variables[k - 1].negated != (bool)i)   //if the variable is negated and isn't i
                {
                    //if it is negated and has as value 0
                    //if it is not negated and has as value 1
                    //var is true so clause is true and we can remove it
                    it = E.erase(it);
                    erased = true;
                }
                else
                {
                    //var is false, it is useless so we remove it
                    if ((*it).usedV > 1)
                    {
                        (*it).variables[k - 1].used = false;
                        (*it).usedV--;
                    }
                    else
                    {
                        //empty clause so insatisfialble solution
                        valid = false;
                        break;
                    }
                }
            }

            //don't iterate if we just removed something
			if (!erased)
				it++;

        }
        //advance
		if (valid)
			checkSAT(k + 1 , E , sol , n);

		//reset
		E = copyE;
    }
}

int main()
{
    //n = max number of variables
    //m = no. of clauses
    int n , m;
    fin>>n>>m;

    //expression
    list <clause> E;

    for(int i = 0 ; i < m ;i++)
    {
        clause C(n);

        int noElem; //no of elements in a clause
        fin>>noElem;
        int value;  //the index of the variable
        for(int j = 0 ; j < noElem ; j++)
        {
            fin >> value;
            //we are given indexes like 1, 2, 3 ... (greater than 0) so we substract 1 when we add in the clause
            ///negative value - negated
            if(value > 0)
            {
                C.variables[value - 1].used = true;
            }
            else
            {
                value = -value;
                C.variables[value - 1].used = true;
                C.variables[value - 1].negated = true;
            }
        }
        C.usedV = noElem;
        E.push_back(C);
    }

    vector <int> sol; //here it will be the solution saved

    sol.resize(n , 0);
    checkSAT(1, E , sol , n);
    if(!ok) //is not a sat expression
        cout<<"Not SAT expression";
    return 0;
}
