#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{
    //default constructor
}

GeneticAlgorithm::GeneticAlgorithm(double time, float mutationLevel, float crossoverLevel, int populationSize, int selectedCrosover)
{
    this->stopTime = time;
    this->mutationLevel = mutationLevel;
    this->crossoverLevel = crossoverLevel;
    this->populationSize = populationSize;
    this->selectedCrossover = selectedCrosover;
}

GeneticAlgorithm::~GeneticAlgorithm()
{
    //dtor
}

void GeneticAlgorithm::SetMatrix(int** matrixCopy, int nodenum)
{
    this->macierz = matrixCopy;
    this->nodeNum = nodenum;
}

int GeneticAlgorithm::CountPathLength(vector<int> path)
{
    auto length = 0;
   for(auto i = 0;i<path.size() - 1;i++)
   {
      length += this->macierz[path[i]][path[i + 1]]; /*obliczanie drogi pomiedzy kolejnymi wierzcholkami w sciezce */
   }
   length += this->macierz[path[this->nodeNum - 1]][path[0]]; /* dodanie odleglosci do poczatkowego */
   return length;
}

void GeneticAlgorithm::PrintSolution()
{
   cout<<"Sciezka: ";
   for(auto i = 0; i<this->nodeNum;i++)
   {
      if(i==this->nodeNum - 1)
      {
         cout<<this->solutionPath[i];
      }
      else
      {
         cout<<this->solutionPath[i]<<"-";
      }
   }
   cout<<"Dlugosc: "<<this->solutionLength<<endl;
}

void GeneticAlgorithm::MutationInversion(vector<vector<int>> &element)
{
    for(auto i=0;i<element.size(); i++)
    {
        vector<int> &tmp = element.at(i);   /* zmienna-referencyjna */
        double p = rand() / (double)RAND_MAX;   /* wspolczynnik czy bedziemy mutowac osobnika */
        if(p < this->mutationLevel) /* mutacja osobnika z okreslonym prawdopodobienstwem */
        {
            /* Algorytm mutacji-inversion */
            auto i=0, j=0;
            while(i==j)
            {
                i = rand() % this->nodeNum;
                j = rand() % this->nodeNum;
            }

            if(i < j)
            {
                reverse(tmp.begin() + i, tmp.begin() + j + 1);  /* reverse kawalku od [i,j] */
            }
            else
            {
                reverse(tmp.begin() + j, tmp.begin() + i + 1);
            }
        }
    }
}

void GeneticAlgorithm::CrossoverOX(vector<int> &first, vector<int> &second)
{
    vector<int> firstNew(this->nodeNum), secondNew(this->nodeNum);  /* tworzymy wyjsciowych osobnikow */
    auto i = 0, j = 0;
    while(i == j)   /* losujemy indeksy do obszaru zamiany */
    {
        i = rand() % this->nodeNum;
        j = rand() % this->nodeNum;
    }

    i = i > j ? j : i;  /* Ustawiamy i jako mniejszy indeks aby bylo latwiej */
    j = i > j ? i : j;

    copy(first.begin() + i, first.begin() + j + 1, secondNew.begin() + i); /* przenosimy obszar z pierwszego do drugiego nowego */
    copy(second.begin() + i, second.begin() + j + 1, firstNew.begin() + i); /* przenosimy obszar z drugiego do pierwszego nowego */

    int position[2] = {j, j};
    for(auto start = j + 1; start < this->nodeNum + j + 1; start++) /* zaczynamy od kolejnego elementu po obszarze zamiany */
    {
        if(find(firstNew.begin() + i, firstNew.begin() + j + 1, first[start % this->nodeNum]) == firstNew.begin() + j + 1)    /* jezeli elementu nie ma w obszarze */
        {
            position[0]++;  /* przechodzimy do kolejnej pozycji w nowym wektorze */
            position[0] = position[0] % this->nodeNum;   /* zeby nie wyjsc za granice vectoru */
            firstNew[position[0]] = first[start % this->nodeNum];
        }
        if(find(secondNew.begin() + i, secondNew.begin() + j + 1, second[start % this->nodeNum]) == secondNew.begin() + j + 1)
        {
            position[1]++;
            position[1] = position[1] % this->nodeNum;
            secondNew[position[1]] = second[start % this->nodeNum];
        }
    }

    first = firstNew;   /* ustawiamy nowych osobnikow */
    second = secondNew;
}

void GeneticAlgorithm::CrossoverPMX(vector<int> &first, vector<int> &second)
{
    vector<int> firstNew(this->nodeNum), secondNew(this->nodeNum);  /* tworzymy wyjsciowych osobnikow */
    auto i = 0, j = 0;
    while(i == j)   /* losujemy indeksy do obszaru zamiany */
    {
        i = rand() % this->nodeNum;
        j = rand() % this->nodeNum;
    }

    i = i > j ? j : i;  /* Ustawiamy i jako mniejszy indeks aby bylo latwiej */
    j = i > j ? i : j;

    copy(first.begin() + i, first.begin() + j + 1, secondNew.begin() + i); /* przenosimy obszar z pierwszego do drugiego nowego */
    copy(second.begin() + i, second.begin() + j + 1, firstNew.begin() + i); /* przenosimy obszar z drugiego do pierwszego nowego */

    for(auto x = 0; x < this->nodeNum; x++)
    {
        if(x >= i && x < j + 1) continue;  /* nie rozpatrywamy zmieniane obszary na poczatku */
        PMX(firstNew, second, first, i, j + 1, x, x);   /* tworzymy pierwszego nowego osobnika */
        PMX(secondNew, first, second, i, j + 1, x, x);  /* i drugiego */
    }

    first = firstNew;   /* ustawiamy nowych osobnikow */
    second = secondNew;
}

void GeneticAlgorithm::PMX(vector<int> &solution, vector<int> &first, vector<int> &second, int start, int finish, int actualPos, int changePos)
{
    auto assigned = true;
    for(int i = start; i < finish; i++)
    {
        /* Znajduje sie w zmienionym obszarze */
        if(first[i] == second[actualPos])
        {
            assigned = false;   /*zeby nie nadpisywac po wyjsciu z rekurencji */
            PMX(solution, first, second, start, finish, i, changePos);
            break;
        }
    }

    /* Jezeli w zmienionym obszarze nie ma to podstawiamy */
    if(assigned) solution[changePos] = second[actualPos];
}

void GeneticAlgorithm::StartAlgorithm()
{
    vector<vector<int>> population, actualPopulation;
    vector<int> citizen;
    int tournamentLength = 8;

    clock_t start;
    double time = 0;

    /* Tworzymy osobnika */
    for(auto i =0;i<this->nodeNum;i++)
    {
        citizen.push_back(i);
    }

    /* Tworzymy populacje */
    for(auto i =0;i<this->populationSize;i++)
    {
        random_shuffle(citizen.begin(), citizen.end());
        population.push_back(citizen);
    }

    start = clock();

    while(time < this->stopTime)
    {
        TournamentSelection(population, tournamentLength);
        actualPopulation = population;  /* populacja po selekcji */
        Crossover(population, actualPopulation); /* krzyzowanie */
        MutationInversion(actualPopulation); /*mutacja*/
        population = actualPopulation;
        actualPopulation.clear();
        FindBestCitizen(population);
        time = (clock() - start) / (double)CLOCKS_PER_SEC;
    }

    PrintSolution();
}

void GeneticAlgorithm::FindBestCitizen(vector<vector<int>> pop)
{
    int minPathLength = INT_MAX, actualPathLength = 0;
    vector<int> bestCitizen;
    for(auto i =0;i<pop.size();i++)
    {
        actualPathLength = CountPathLength(pop[i]);
        if(actualPathLength - minPathLength < 0)
        {
            minPathLength = actualPathLength;
            bestCitizen = pop[i];
        }
    }
    if(minPathLength - this->solutionLength < 0)    /* znalezlismy rozwiazanie lepsze niz dotychczas znane*/
    {
        this->solutionLength = minPathLength;
        this->solutionPath = bestCitizen;
    }
}

void GeneticAlgorithm::Crossover(vector<vector<int>> &pop, vector<vector<int>> &tmpPop)
{
    vector<int> father, mother;
    for(auto i =0;i< pop.size() * this->crossoverLevel;i++)
    {
        auto x=0, y=0;  /* indeksu do losowania osobnikow */
        while(x==y)
        {
            x = rand() % pop.size();
            y = rand() % pop.size();
        }

        father = pop[x];    /* wybieramy pierwszego osobnika */
        mother = pop[y];    /* wybieramy drugiego osobnika */

        switch(this->selectedCrossover)
        {
            case 1:
                CrossoverOX(father, mother);
                break;
            case 2:
                CrossoverPMX(father, mother);
                break;
            default:
                break;
        }

        tmpPop.push_back(father);   /* typy referencyjne beda zmienione w krzyzowaniach */
        tmpPop.push_back(mother);
    }
}

void GeneticAlgorithm::TournamentSelection(vector<vector<int>> pop, int length)
{
    vector<vector<int>> actualPopulation;
    for(auto i =0;i<this->populationSize;i++)
    {
        int bestLength = INT_MAX, citizenIndex, citizenFitness, bestCitizenIndex;
        for(int j=0;j<length;j++)   /* losujemy osobnikow tyle ile wynosi dlugosc turnieju */
        {
            citizenIndex = rand() % pop.size(); /* losowanie osobnika */
            citizenFitness = CountPathLength(pop[citizenIndex]); /* stopien dostosowania */
            if(citizenFitness < bestLength)
            {
                bestCitizenIndex = citizenIndex;
                bestLength = citizenFitness;
            }
        }
        actualPopulation.push_back(pop[bestCitizenIndex]);  /* wstawiamy najlepiej dostosowanego osobnika */
    }
    pop = actualPopulation;
}
