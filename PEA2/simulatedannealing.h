#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <stdlib.h>

using namespace std;

class SimulatedAnnealing
{
   public:
      SimulatedAnnealing();
      virtual ~SimulatedAnnealing();

      void SetMatrix(int** matrixCopy, int nodenum);
      void PrintMatrix();
      void SetStopTime(double time);
      void SetFreezingLevel(double freezing);
      void StartAlgorithm();
      void PrintSolution();

      vector<int> CreateStartPath();
      vector<int> CreateRandomPermutation(int permSize);

      int CountPathLength(vector<int> path);

      double CountStartTemperature(); /* obliczanie temperatury startu */
      int CountMaxRepeat(); /* dlugosc epoki - ilosc prob znalezenia rozwiazania */

   protected:

   private:
      int** macierz;
      int nodeNum;
      double stopTime;
      double temperature;
      int freezingLevel;
};

#endif // SIMULATEDANNEALING_H
