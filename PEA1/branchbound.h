#ifndef BRANCHBOUND_H
#define BRANCHBOUND_H

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "node.h"

using namespace std;

class BranchBound
{
       public:
              BranchBound();
              virtual ~BranchBound();
              void PrintGraph();
              void PrintSolution();
              void SolveTSP();
              void HighLimit(Node node);
              int LowLimit(Node node, int next);
              void Start(Node node);

              bool ReadFromFile(string filename);


       protected:

       private:
              int node_num = 0;

              int ograniczenieGorne = INT_MAX;

              stack<int> actualPath;
              stack<int> finalPath;

              int* minimumTab;
              int** macierz;  /* macierz sasiedztwa */
              bool* checked;

              void SetValueForMatrix(int i, int j, int value);

};

#endif // BRANCHBOUND_H
