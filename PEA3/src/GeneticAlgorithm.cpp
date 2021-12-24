#include "GeneticAlgorithm.h"

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
                element.at(i).reverse(element.at(i).begin() + i, j - i);
            }
            else
            {
                element.at(i).reverse(element.at(i).begin() + j, i - j);
            }
        }
    }
}

