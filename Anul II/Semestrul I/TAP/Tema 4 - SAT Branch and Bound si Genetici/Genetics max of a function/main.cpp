#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

int interv_min, interv_max;
double coeficient;

//-x^2 + x + 2
double fitnessFunction(double val)
{
    return -(val * val) + val + 2;
//  return 5 * (val * val * val) - 7 * (val * val) - 6 * val + 8;
}

class Chromosome
{
public:
    vector<bool> data;
    double value,fitness,prob_select;

    Chromosome(int size)
    {
        data.resize(size);
        for (int i = 0; i < size; i++)
        {
            data[i] = rand() % 2;
        }
        value = fitness = prob_select = 0;
    }

    void findValueAndFitness(double minim, double coef)
    {
        //compute value; chromosome coding in the interval
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i] == true)
                value += (double)pow(2, data.size() - (i + 1));
        }



        value = coef * value + (double)minim;

        double val = value;
        //compute fitness
        this->fitness = fitnessFunction(val);
    }

    void computeProbSelection(double sum_fitness)
    {
        prob_select = (double) ((double)fitness / (double)sum_fitness);

    }

    bool operator!=(const Chromosome& other)
    {
        for (int i=0; i < data.size(); i++)
        {
            if (data[i] != other.data[i])
                return true;
        }
        return false;
    }

    void print_data() const
    {
        for (bool b : data)
            cout<<b;
        cout<<" ";
    }
};

void printChromosomes(vector<Chromosome>& chromosomes)
{

    for(int i = 0 ; i < chromosomes.size() ; i++)
    {
        //print id
        cout<<i+1<<": ";
        //print binary value
        for (bool b : chromosomes[i].data)
            cout<<b;
        //print actual value
        //printf(" x=%.6Lf", chromosomes[i].value);
        cout<<"  x= " <<chromosomes[i].value<<" ";
        //print fitness
        cout<<"  f= " << chromosomes[i].fitness<<endl;
        //printf(" f= %.10Lf\n", chromosomes[i].fitness);
    }
}

vector<Chromosome> evolution(vector<Chromosome> &lastGeneration, double prob_crossover, double prob_mutate)
{
    std::default_random_engine generator;
    generator.seed(time(NULL));
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    int pop_size = lastGeneration.size();
    double total_fitness = 0;

    //COMPUTE PROB OF SELECTION
    for (int i = 0; i < pop_size; i++)
    {
        total_fitness += lastGeneration[i].fitness;
    }
    for (int i = 0; i < pop_size; i++)
    {
        lastGeneration[i].computeProbSelection(total_fitness);
    }

    //CALCULATE ROULETTE INTERVALS
    vector<double> selectionInterval;
    selectionInterval.push_back(lastGeneration[0].prob_select);

    for (size_t i = 1; i < pop_size; ++i)
    {
        selectionInterval.push_back(selectionInterval[i - 1] + lastGeneration[i].prob_select);
    }

    //CREATE NEW GENERATION
    vector<Chromosome> nextGeneration;

    //SELECTION
    for (int i = 0; i < pop_size; ++i) {
        double number = distribution(generator);

        int index = lower_bound(selectionInterval.begin(), selectionInterval.end(), number) - selectionInterval.begin();
        nextGeneration.push_back(lastGeneration[index]);
    }


    //CROSSOVER
    vector<bool> participate(pop_size, false);

    for (int i = 0; i < pop_size; ++i)
    {
        double number = distribution(generator);

        if (number < prob_crossover)
        {
            participate[i] = true;
        }
    }

    //the choromosomes that will participate compute crossover
    for (int i = 0; i < pop_size; i++)
    {
        if (participate[i])
        {
            for (int j = i + 1; j < pop_size; j++)
            {
                if (participate[j] && nextGeneration[i] != nextGeneration[j])
                {
                    //generate a random index for crossover
                    int split = rand() % nextGeneration[0].data.size();
                    bool aux;

                    for (int k = 0; k <= split; k++)
                    {
                        aux = nextGeneration[i].data[k];
                        nextGeneration[i].data[k] = nextGeneration[j].data[k];
                        nextGeneration[j].data[k] = aux;
                    }

                    participate[i] = participate[j] = false;
                    nextGeneration[i].findValueAndFitness(interv_min, coeficient);
                    nextGeneration[j].findValueAndFitness(interv_min, coeficient);
                    break;
                    //chromosome i participated. it can't participate again
                }
            }
        }
    }

    //MUTATION
    for (int i = 0; i < pop_size; i++)
    {
        bool mutated = false;
        for (int j = 0; j < nextGeneration[i].data.size(); j++)
        {
            double number = distribution(generator);
            if (number < prob_mutate)
            {
                mutated = true;
                nextGeneration[i].data[j] = !nextGeneration[i].data[j];
            }
        }
        if (mutated)
        {
            nextGeneration[i].findValueAndFitness(interv_min, coeficient);
        }
    }

    return nextGeneration;
}

double findMaximumValue(vector<Chromosome> chromosomes)
{
    //function that finds the maximum value of a function in a generation
    double maxx = chromosomes[0].fitness;

    for (int i = 1; i < chromosomes.size(); i++)
    {
        if (chromosomes[i].fitness > maxx)
            maxx = chromosomes[i].fitness;
    }

    return maxx;
}

double findAverage(vector<Chromosome> chromosomes)
{
    double sum =0;
    //function that finds the average value of perfomancy
    for (int i = 0; i < chromosomes.size(); i++)
    {
        sum+=chromosomes[i].fitness;
    }

    return sum/ chromosomes.size();
}

int main()
{

    //input
    int pop_size, precizion , max_generations;
    double prob_crossover , prob_mutate;
    default_random_engine generator;
    generator.seed(time(NULL));

    uniform_real_distribution<double> distribution(0.0, 1.0);
    srand(time(NULL));
    //read input data

    ifstream fin("data.in");
    fin >> pop_size;
    fin >> interv_min >> interv_max;
    fin >> precizion;
    fin >> prob_crossover >> prob_mutate;
    fin >> max_generations; //number of steps of the algorithm

    //calculate binary positions needed. Length of the chromosome
    int bin_size = log2((interv_max - interv_min) * pow(10, precizion)) + 1;


    //calculate coeficient
    coeficient = (double)interv_max - (double)interv_min;
    coeficient = (double)((double) coeficient / (double)(pow(2, bin_size) - 1));

    //chromosomes
    vector<Chromosome> chromosomes;
    double total_fitness = 0;
    //generate the chromosomes
    for (int i = 0; i < pop_size; i++)
    {
        Chromosome cr(bin_size);    //generate a chromosome with the length bin_size
        cr.findValueAndFitness(interv_min,coeficient);   //initialize the correspondent value of the chromosome in the interval and the
        total_fitness += (double)cr.fitness;
        chromosomes.push_back(cr);
    }

    for (int i = 0; i < pop_size; i++)
    {
        chromosomes[i].computeProbSelection(total_fitness);
    }

    //print initial chromosomes
    cout <<endl<< "Populatia initiala" << endl;
    printChromosomes(chromosomes);

    //print initial selection probabilities
    cout << endl << "Probabilitati de selectie" << endl;
    for (int i = 0; i < pop_size; i++)
    {
    cout<<"Cromozomul " << i+1 << " are probabilitatea " <<chromosomes[i].prob_select<<"\n";
    }

    //calculate intervals
    //roulette
    vector<double> selectionInterval;
    selectionInterval.push_back(chromosomes[0].prob_select);

    cout <<endl<< "Intervale probabilitati de selectie"<<endl;
    cout << "0\n" << selectionInterval[0]<<"\n";

    for (size_t i = 1; i < pop_size; ++i)
    {
        selectionInterval.push_back(double(selectionInterval[i - 1] + chromosomes[i].prob_select));
        cout << selectionInterval[i] << "\n";
    }

    //start working on next generation
    vector<Chromosome> nextGeneration;

    //SELECTION
    cout << endl << "Selectie" << endl;
    for (int i = 0; i < pop_size; ++i)
    {
        //give a number between 0 and 1
        double number = distribution(generator);
        //find the first number which is greater than number. returns an iterator
        //find the interval in which number fits
        int index = lower_bound(selectionInterval.begin(), selectionInterval.end(), number) - selectionInterval.begin();
        nextGeneration.push_back(chromosomes[index]);

        cout<< "u= " <<number <<" selectam cromozomul " << index + 1<<"\n";
    }

    printf("\nDupa selectie:\n");
    printChromosomes(nextGeneration);

    //CROSSOVER

    //vector de marcare
    vector<bool> participate(pop_size, false);

    for (int i = 0; i < pop_size; ++i)
        {
        double number = distribution(generator);

        if (number < prob_crossover)
        {
            participate[i] = true;
            cout<<i+1 <<": cromozomul participa       u= "<< number <<" < " << prob_crossover<<endl;
        }
        else
        {
            cout<<i+1 <<": cromozomul nu participa    u= "<< number <<endl;
        }
    }


    //compute crossover
    for (int i = 0; i < pop_size; i++)
    {
        if (participate[i])
        {
            for (int j = i+1; j < pop_size; j++)
            {
                if (participate[j] && nextGeneration[i] != nextGeneration[j])
                {
                    cout<<"\nRecombinare dintre cromozomul "<<i + 1<<" cu cromozomul "<<j + 1<<":\n";
                    int split = rand() % bin_size;
                    bool aux;

                    nextGeneration[i].print_data();
                    nextGeneration[j].print_data();
                    printf("punct %d\n", split);
                    //crossing with one break point
                    for (int k = 0; k <= split; k++)
                    {
                        aux = nextGeneration[i].data[k];
                        nextGeneration[i].data[k] = nextGeneration[j].data[k];
                        nextGeneration[j].data[k] = aux;
                    }
                    participate[i] = participate[j] = false;
                    nextGeneration[i].findValueAndFitness(interv_min,coeficient);
                    nextGeneration[j].findValueAndFitness(interv_min, coeficient);
                    printf("Rezultat:\n");
                    nextGeneration[i].print_data();
                    nextGeneration[j].print_data();
                    break;
                }
            }
        }
    }

    cout<<"\nDupa recombinare:\n";
    printChromosomes(nextGeneration);

    //MUTATION
    cout<<"\nProbabilitate de mutatie pentru fiecare gena "<< prob_mutate<<"\n";
    cout<<"Au fost modificati cromozomii: ";
    for (int i = 0; i < pop_size; i++)
    {
        bool mutated = false;
        for (int j = 0; j < nextGeneration[i].data.size(); j++)
        {
            double number = distribution(generator);
            if (number < prob_mutate)
            {
                mutated = true;
                nextGeneration[i].data[j] = !nextGeneration[i].data[j];
            }
        }
        if (mutated)
        {
            printf("%d ", i + 1);
            nextGeneration[i].findValueAndFitness(interv_min, coeficient);
        }

    }
    cout<<"\nDupa mutatie:\n";
    printChromosomes(nextGeneration);

    cout<<"Valori maxime si valori medii ale performantei: \n";
    cout << "0: " <<findMaximumValue(chromosomes)<< " " <<findAverage(chromosomes)<<endl;
    cout <<"1: " <<findMaximumValue(nextGeneration)<<" " <<findAverage(nextGeneration)<< endl;
    for (int i = 2; i < max_generations; i++)
    {
        nextGeneration = evolution(nextGeneration, prob_crossover, prob_mutate);

        cout <<i+1<<":" << " "<< findMaximumValue(nextGeneration) << " "<<findAverage(nextGeneration) << endl;
    }
    return 0;
}
