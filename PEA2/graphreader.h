#ifndef GRAPHREADER_H
#define GRAPHREADER_H

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <stdlib.h>

using namespace std;

class GraphReader
{
   public:
      GraphReader();
      virtual ~GraphReader();

      bool ReadFromFile(string file);
      void PrintGraph();

      int** getMacierz();
      int getNodeNum();

   protected:

   private:
      int** macierz;
      int nodeNum;

      void ClearValues();
};

#endif // GRAPHREADER_H
