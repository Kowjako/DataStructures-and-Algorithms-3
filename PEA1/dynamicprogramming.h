#ifndef DYNAMICPROGRAMMING_H
#define DYNAMICPROGRAMMING_H

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <bitset>

using namespace std;
class DynamicProgramming
{
   public:
      DynamicProgramming();
      virtual ~DynamicProgramming();

      void PrintGraph();
      void PrintSolution();

      void InitializePathArray();
      void Start();

      void ClearValues();
      bool ReadFromFile(string filename);

   protected:

   private:
	  vector<vector<int>> d; /* mozliwe drogi */
	  vector<vector<int>> track; /* tracking drogi */
     int node_num = 0;
	  int** macierz;

	  int lastNode;
	  void SetMatrixValue(int i, int j, int value);

};

#endif // DYNAMICPROGRAMMING_H
