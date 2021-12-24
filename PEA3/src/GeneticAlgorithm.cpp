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


