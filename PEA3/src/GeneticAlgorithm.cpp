#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{
    //default constructor
}

GeneticAlgorithm::GeneticAlgorithm(double time, float mutationLevel, float crossoverLevel)
{
    this->stopTime = time;
    this->mutationLevel = mutationLevel;
    this->crossoverLevel = crossoverLevel;
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
                reverse(tmp.begin() + i, tmp.begin() + j + 1);
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
    this->nodeNum = 9;

    vector<int> firstNew(this->nodeNum), secondNew(this->nodeNum);  /* tworzymy wyjsciowych osobnikow */
    //auto i = 0, j = 0;
//    while(i == j)   /* losujemy indeksy do obszaru zamiany */
//    {
//        i = rand() % this->nodeNum;
//        j = rand() % this->nodeNum;
//    }
//
//    i = i > j ? j : i;  /* Ustawiamy i jako mniejszy indeks aby bylo latwiej */
//    j = i > j ? i : j;
    int i = 2, j = 5;

    copy(first.begin() + i, first.begin() + j + 1, secondNew.begin() + i); /* przenosimy obszar z pierwszego do drugiego nowego */
    copy(second.begin() + i, second.begin() + j + 1, firstNew.begin() + i); /* przenosimy obszar z drugiego do pierwszego nowego */

    for(auto x = 0; x < this->nodeNum; x++)
    {
        if(x >= i && x < j + 1) continue;  /* nie rozpatrywamy zmieniane obszaru na poczatku */
        PMX(firstNew, second, first, i, j + 1, x, x);
        PMX(secondNew, first, second, i, j + 1, x, x);
    }

    first = firstNew;   /* ustawiamy nowych osobnikow */
    second = secondNew;
}

void GeneticAlgorithm::PMX(vector<int> &solution, vector<int> &first, vector<int> &second, int start, int finish, int actualPos, int changePos)
{
    auto assigned = true;
    for(int i = start; i < finish; i++)
    {
        if(first[i] == second[actualPos])
        {
            assigned = false;
            PMX(solution, first, second, start, finish, i, changePos);
            break;
        }
    }

    if(assigned) solution[changePos] = second[actualPos];
}

