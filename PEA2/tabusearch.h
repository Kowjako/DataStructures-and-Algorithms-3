#ifndef TABUSEARCH_H
#define TABUSEARCH_H

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <stdlib.h>
#include "move.h"

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
      void PrintSolution();

      vector<int> CreateRandomPermutation(int permSize);
      vector<int> CreateStartPath();
      vector<Move> BannedMoves;
      vector<int> FindNextMove(vector<int> path, int pathLength);

      int CountPathLength(vector<int> path);

      /** Results **/
      vector<int> finalPath;
      int finalPathLength;
      double finalTime;

   protected:

   private:
      int** macierz;
      int nodeNum;
      int startNode, finishNode;  /* poczatek i koniec ostatniego lepszego ruchu */
      int frequency;
      double stopTime;
};

#endif // TABUSEARCH_H
