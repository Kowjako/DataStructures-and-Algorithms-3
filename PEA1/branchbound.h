#ifndef BRANCHBOUND_H
#define BRANCHBOUND_H

#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

class BranchBound
{
       public:
              BranchBound();
              virtual ~BranchBound();
              void Print();

              int** GetMacierz();
              bool ReadFromFile(string filename);


       protected:

       private:
              int node_num = 0;
              int** macierz;  /* macierz sasiedztwa */
              void SetValueForMatrix(int i, int j, int value);
};

#endif // BRANCHBOUND_H
