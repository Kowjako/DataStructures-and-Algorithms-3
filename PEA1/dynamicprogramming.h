#ifndef DYNAMICPROGRAMMING_H
#define DYNAMICPROGRAMMING_H

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;
class DynamicProgramming
{
   public:
      DynamicProgramming();
      virtual ~DynamicProgramming();
	  
	  void PrintGraph();
	  void PrintSolution();
	  
	  void Start();
	  
	  bool ReadFromFile(string filename)
	  
   protected:
   
   private:
      int node_num = 0;
	  int** macierz;
	  void SetMatrixValue(int i, int j, int value);
};

#endif // DYNAMICPROGRAMMING_H
