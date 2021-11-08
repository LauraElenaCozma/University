#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>


using namespace std;
ifstream fin("data.in");
class state
{
public:

	int cost;   //cost until current level
	int level;  //the current level
	int lastNode; //the number of the node of the state
	vector<bool> used;  //which nmaodes were used
	state* parent;
	vector < vector < int > > matrix;

	state(vector < bool > &used , int cost = 0 , state* parent = NULL)
	{
		this->cost = cost;
		this->parent = parent;
		this->used = used;
		lastNode = 0;
		level = 1;
	}

};

struct customCmp
{
	bool operator()(const state* a, const state* b)
	{
		return a->cost > b->cost;
	}
};


void print_sol(state* st)
{
	if (st == NULL)
		return;

	print_sol(st->parent);
	cout <<st->lastNode + 1 << " ";
}

int reduction(vector<vector<int>>& matrix)
{
	int n = matrix.size() , reducted = 0;
	for (int i = 0; i < n; i++)
	{
	    //find the minimum from i line
		int min = -1;
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] != -1 && (matrix[i][j] < min || min == -1))
			{
				min = matrix[i][j];
			}
		}

        //all the values from this line are -1 = infinity
		//nothing to do
		if (min <= 0)
			continue;

		reducted += min;
		for (int j = 0; j < n; j++)
		{
		    //reduce the line i
			if (matrix[i][j] != -1)
				matrix[i][j] -= min;
		}
	}

	for (int i = 0; i < n; i++)
	{
	    //find the minimum from column i
		int min = -1;
		for (int j = 0; j < n; j++)
		{
			if (matrix[j][i] != -1 && (matrix[j][i] < min || min == -1))
			{
				min = matrix[j][i];
			}
		}

        //all the values were -1
		if (min <= 0)
			continue;

        //the cost of the matrix += the minimum value substracted
		reducted += min;
		for (int j = 0; j < n; j++)
		{
		    //reduce the column i
			if (matrix[j][i] != -1)
				matrix[j][i] -= min;
		}
	}

	return reducted;
}

void salesmanProblem()
{
    //build a min heap with elements of type state *
	priority_queue <state* , vector <state*> , customCmp> min_heap;

	vector < vector < int > > matrix;
	int n, reductedSum;
	fin >> n;
	matrix.resize(n);

	//read adjacent matrix
	for (int i = 0; i < n; i++)
	{
		matrix[i].resize(n);

		for (int j = 0; j < n; j++)
		{
			int x;
			if (i == j)
				matrix[i][j] = -1;
			else
			{
				fin >> x;
				matrix[i][j] = x;
			}
		}
	}

	//reduction
	reductedSum = reduction(matrix);

	vector<bool> used(n, 0);
	used[0] = 1;
	//add initial state to min_heap
	//create the first node. Only the first node is used,
	//the matrix is the adj. matrix after reduction and
	//cost is the red obtained from reduction
	state* initialState = new state(used);
	initialState->matrix = matrix;
	initialState->cost = reductedSum;


	min_heap.push(initialState);

	//used after finding solutions
	int bestSol = -1; //the cost of the best solution found by now
	state* bestState = NULL;

	//Extract states one by one
	while (!min_heap.empty())
	{
		//take best state out
		//it is the state with the minimum cost
		state* selectedState = min_heap.top();
		min_heap.pop();

		//popped bad node
		//we found a path with a cost = best_sol so it is inefficient to check if another path has a cost < bestSol if it has already a cost > bestSol
		if (selectedState->cost > bestSol && bestSol != -1)
		{
		    //already exists a path with a cost < the cost of the selected state
			delete(selectedState);
			continue;
		}

		//compute all of its children that can yield solutions and add them to min_heap
		for (int i = 1; i < n; i++)
		{
			//jump over used nodes
			if (selectedState->used[i])
				continue;

            //a node which was not used
            //selectedState is his parent
            //the vector used is the same as it's parent +  used[i] = 1
			state* child = new state(selectedState->used , selectedState->cost , selectedState);
			child->level = selectedState->level + 1; //one level deeper
			child->matrix = selectedState->matrix;
			child->lastNode = i;

			//last level node, we can compute real cost and add as solution
			//node i is a leaf in this path
			if (selectedState->level == n - 1)
			{
			    //it's the last node, we don't have to reduce the matrix
				child->cost += child->matrix[selectedState->lastNode][i] + child->matrix[i][0];
            	//child->matix[i][0] = the cost between the last node and the first node

				if (child->cost < bestSol || bestSol == -1)
				{
					bestSol = child->cost;
					bestState = child;
				}
			}
			else
			{
				//line i is -1
				for (int j = 0; j < n; j++)
					child->matrix[selectedState->lastNode][j] = -1;

				//column j is -1selectedState
				for (int j = 0; j < n; j++)
					child->matrix[j][i] = -1;

				//put -1 on the matrix not to go back if not all the nodes were used
				child->matrix[i][0] = -1;

				//reduce matrix
				child->cost += reduction(child->matrix);

				//not last level node, we compute cost and insert it in min_heap
				//matrix[selectedState->lastNode][i] = the cost between the child i and the parent lastNode
				child->cost += selectedState->matrix[selectedState->lastNode][i];

				//check if child can make a better solution
				//if not, delete it
				if (child->cost >= bestSol && bestSol!=-1)
				{
					delete(child);
					continue;
				}
                //if the child can make a better solution, we add it to the min-heap
				child->used[i] = true;
				//push the child into the min heap
				min_heap.push(child);
			}
		}

	}

	//print solution
	cout <<"Cost minim:"<< bestSol << endl;
	print_sol(bestState);
	cout << "1"<<endl;

}

int main()
{
	salesmanProblem();
	return 0;
}
