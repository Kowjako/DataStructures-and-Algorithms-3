#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "node.h"

using namespace std;

class BruteForce
{
   public:
      BruteForce();
      virtual ~BruteForce();
      bool ReadFromFile(string filename);

      void PrintGraph();
      void PrintSolution();
      void Start();
      void StartBrute(int nodeNumber);

   protected:

   private:
      int node_num = 0;
      int** macierz;  /* macierz sasiedztwa */
      int* finalPermutation, tmpPermutation;
      void SetValueForMatrix(int i, int j, int value);
};

#endif // BRUTEFORCE_H
