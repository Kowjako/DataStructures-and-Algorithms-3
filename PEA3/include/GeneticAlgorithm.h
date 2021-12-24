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
        void CrossoverPMX(vector<int> &first, vector<int> &second);

        /* Mutacja*/
        void MutationInversion(vector<vector<int>> &element);   /* wektor populacji */

        /* Selekcja turniejowa*/
        void TournamentSelection(vector<vector<int>> population, int tournamentLength);

        void StartAlgorithm();

        int CountPathLength(vector<int> path);
        void PrintSolution();


    protected:

    private:
        void PMX(vector<int> &solution, vector<int> &first, vector<int> &second,
                 int start, int finish, int x1, int x2);

        int** macierz;
        int nodeNum, populationSize;
        double stopTime;
        float mutationLevel, crossoverLevel;

        /* Rozwiazanie */
        vector<int> solutionPath;
        int solutionLength;
};

#endif // GENETICALGORITHM_H
