#include <iostream>
#include "graphreader.h"
#include "GeneticAlgorithm.h"

using namespace std;

GraphReader reader;
GeneticAlgorithm  GA(120.0,0.01,0.9,5000, 1);

int main()
{
   string loc;
   cin>>loc;
   if(reader.ReadFromFile(loc))
   {
      srand(time(NULL));
      GA.SetMatrix(reader.getMacierz(), reader.getNodeNum());
      GA.StartAlgorithm();
   }
   return 0;
}
