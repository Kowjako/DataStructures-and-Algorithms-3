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
        GeneticAlgorithm(double time, float mutationLevel, float crossoverLevel, int popSize, int selectedCrossover);

        virtual ~GeneticAlgorithm();

        void SetMatrix(int** matrixCopy, int nodenum);

        /* Krzyzowania */
        void Crossover(vector<vector<int>> &pop, vector<vector<int>> &tmpPop);
        void CrossoverOX(vector<int> &first, vector<int> &second);  /* ustawiamy typ referencyjny */
        void CrossoverPMX(vector<int> &first, vector<int> &second);

        /* Mutacja - inversion*/
        void MutationInversion(vector<vector<int>> &element);   /* wektor populacji */

        /* Selekcja turniejowa*/
        void TournamentSelection(vector<vector<int>> &population, int tournamentLength);

        void FindBestCitizen(vector<vector<int>> pop);

        void StartAlgorithm();

        int CountPathLength(vector<int> path);
        void PrintSolution();


    protected:

    private:
        void PMX(vector<int> &solution, vector<int> &first, vector<int> &second,int start, int finish, int x1, int x2);

        int** macierz;
        int nodeNum, populationSize, selectedCrossover;
        double stopTime;
        float mutationLevel, crossoverLevel;

        /* Rozwiazanie */
        vector<int> solutionPath;
        int solutionLength = INT_MAX;
};

#endif // GENETICALGORITHM_H
