#include "tabusearch.h"

TabuSearch::TabuSearch()
{
   //ctor
}

TabuSearch::~TabuSearch()
{
   //dtor
}

void TabuSearch::SetMatrix(int** copyMatrix, int nodenum)
{
   this->macierz = copyMatrix;
   this->nodeNum = nodenum;
}

void TabuSearch::PrintMatrix()
{
   for(auto i =0;i<this->nodeNum;i++)
   {
      for(auto j = 0;j<this->nodeNum;j++)
         cout<<this->macierz[i][j]<<" ";
      cout<<endl;
   }
}

void TabuSearch::SetStopTime(double time)
{
   this->stopTime = time;
}

vector<int> TabuSearch::CreateRandomPermutation(int permSize)
{
   vector<int> permutation;
   permutation.resize(this->nodeNum, 0);
   for(auto i = 0; i<this->nodeNum;i++)
   {
      permutation[i] = i;
   }

   srand(time(NULL));  /* zeby uniknac generowania tego samego poprzez random_shuffle */

   random_shuffle(permutation.begin(), permutation.end());
   return permutation;
}

int TabuSearch::CountPathLength(vector<int> path)
{
   auto length = 0;
   for(auto i = 0;i<path.size() - 1;i++)
   {
      length += this->macierz[path[i]][path[i + 1]]; /*obliczanie drogi pomiedzy kolejnymi wierzcholkami w sciezce */
   }
   length += this->macierz[path[this->nodeNum - 1]][0]; /* dodanie odleglosci do poczatkowego */
   return length;
}

vector<int> TabuSearch::FindPath()
{
   vector<int> minPath = CreateRandomPermutation(this->nodeNum);
   vector<int> actualPath(minPath);

   auto minPathLength = CountPathLength(minPath);
   auto actualLength = minPathLength - 1;             /*odejmujemy 1 aby przynajmniej jeden raz sprobowac znalezc najlepsza sciezke */

   while(actualLength < minPathLength)
   {
      actualLength += 1;                              /* dodajemy z powrotem 1, jezeli nie bedzie lepsza sciezka to skonczymy petle */
      for(auto i = 0;i<this->nodeNum;i++)
         for(auto j = 0;j<this->nodeNum;j++)
            if(i!=j) /* czy nie rozpatrywamy ten sam wierzcholek */
            {
               auto tmpPathLength = 0;
               vector<int> tmpPath(actualPath);
               swap(tmpPath(i), tmpPath(j)); /* zamieniamy miejscami wierzcholki */
               tmpPathLength = CountPathLength(tmpPath); /*obliczamy dlugosc drogi*/
               if(tmpPathLength < actualLength) /* jezeli jest lepsza */
               {
                  actualPath = tmpPath;
                  actualLength = tmpPathLength;
               }
            }

      minPath = actualPath;            /* nowa minimalna sciezka */
      minPathLength = actualLength;    /* nowa dlugosc minimalnej sciezki */
   }

   return minPath;
}
