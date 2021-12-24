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
        GeneticAlgorithm(double time, float mutationLevel, float crossoverLevel);

        virtual ~GeneticAlgorithm();

        void SetMatrix(int** matrixCopy, int nodenum);

        void StartAlgorithm();

        /* Krzyzowania */
        void CrossoverOX(vector<int> &first, vector<int> &second);  /* ustawiamy typ referencyjny */
        void CrossoverSXX(vector<int> &first, vector<int> &second);

        /* Mutacja*/
        void MutationInversion(vector<vector<int>> &element);   /* wektor populacji */

        int CountPathLength(vector<int> path);
        void PrintSolution();


    protected:

    private:
        int** macierz;
        int nodeNum;
        double stopTime;

        float mutationLevel, crossoverLevel;

        /* Rozwiazanie */
        vector<int> solutionPath;
        int solutionLength;
};

#endif // GENETICALGORITHM_H
