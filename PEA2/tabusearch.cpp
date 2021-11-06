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
