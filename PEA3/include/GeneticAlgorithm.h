#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <random>
using namespace std;

class GeneticAlgorithm
{
    public:
        GeneticAlgorithm();
        virtual ~GeneticAlgorithm();

        void SetMatrix(int** matrixCopy, int nodenum);
        void SetStopTime(double time);  /* czas stopu */

        void StartAlgorithm();

        int CountPathLength(vector<int> path);
        void PrintSolution();


    protected:

    private:
        int** macierz;
        int nodeNum;
        double stopTime;

        /* Rozwiazanie */
        vector<int> solutionPath;
        int solutionLength;
};

#endif // GENETICALGORITHM_H
