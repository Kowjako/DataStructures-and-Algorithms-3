#ifndef TABUSEARCH_H
#define TABUSEARCH_H

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <stdlib.h>

using namespace std;

class TabuSearch
{
   public:
      TabuSearch();
      virtual ~TabuSearch();

      void SetMatrix(int** matrixCopy, int nodenum);
      void PrintMatrix();
      void SetStopTime(double time);
      void StartAlgorithm();

      vector<int> CreateRandomPermutation(int permSize);
      vector<int> FindPath();
      int CountPathLength(vector<int> path);


   protected:

   private:
      int** macierz;
      int nodeNum;
      double stopTime;
};

#endif // TABUSEARCH_H
