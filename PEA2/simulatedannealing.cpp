#include "simulatedannealing.h"

SimulatedAnnealing::SimulatedAnnealing()
{
   //ctor
}

SimulatedAnnealing::~SimulatedAnnealing()
{
   //dtor
}

void SimulatedAnnealing::SetMatrix(int** copyMatrix, int nodenum)
{
   this->macierz = copyMatrix;
   this->nodeNum = nodenum;
}

void SimulatedAnnealing::PrintMatrix()
{
   for(auto i =0;i<this->nodeNum;i++)
   {
      for(auto j = 0;j<this->nodeNum;j++)
         cout<<this->macierz[i][j]<<" ";
      cout<<endl;
   }
}

void SimulatedAnnealing::SetStopTime(double time)
{
   this->stopTime = time;
}

vector<int> SimulatedAnnealing::CreateRandomPermutation(int permSize)
{
   vector<int> permutation;
   permutation.resize(this->nodeNum, 0);
   for(auto i = 0; i<this->nodeNum;i++)
   {
      permutation[i] = i;
   }

   random_shuffle(permutation.begin(), permutation.end());
   return permutation;
}

int SimulatedAnnealing::CountPathLength(vector<int> path)
{
   auto length = 0;
   for(auto i = 0;i<path.size() - 1;i++)
   {
      length += this->macierz[path[i]][path[i + 1]]; /*obliczanie drogi pomiedzy kolejnymi wierzcholkami w sciezce */
   }
   length += this->macierz[path[this->nodeNum - 1]][path[0]]; /* dodanie odleglosci do poczatkowego */
   return length;
}

vector<int> SimulatedAnnealing::CreateStartPath()
{
   vector<int> minPath = CreateRandomPermutation(this->nodeNum);
   vector<int> actualPath(minPath);

   auto minPathLength = CountPathLength(minPath);
   auto actualLength = minPathLength - 1;             /*odejmujemy 1 aby przynajmniej jeden raz sprobowac znalezc najlepsza sciezke */

   while(actualLength < minPathLength)
   {
      actualLength += 1;                              /* dodajemy z powrotem 1, jezeli nie bedzie lepsza sciezka to skonczymy petle */
      for(auto i = 0;i<this->nodeNum;i++)
         for(auto j = i;j<this->nodeNum;j++)          /* j = i aby nie powtarzac tych samych permutacji */
            if(i!=j) /* czy nie rozpatrywamy ten sam wierzcholek */
            {
               vector<int> tmpPath(actualPath);
               swap(tmpPath[i], tmpPath[j]); /* zamieniamy miejscami wierzcholki */
               auto tmpPathLength = CountPathLength(tmpPath); /*obliczamy dlugosc drogi*/
               if(tmpPathLength < actualLength) /* jezeli jest lepsza */
               {
                  actualPath = tmpPath;
                  actualLength = tmpPathLength;
               }
            }

      if(actualLength < minPathLength)
      {
         minPath = actualPath;            /* nowa minimalna sciezka */
         minPathLength = actualLength;    /* nowa dlugosc minimalnej sciezki */
         actualLength -= 1;   /* odejmujemy 1 aby znow poszukac lepszej */
      }
   }

   return minPath;
}

double SimulatedAnnealing::CountStartTemperature() /* obliczanie poczatkowej temperatury */
{
   int startNode = 0, finalNode = 0; /* ustawiamy aby przynajmniej jeden raz wylosowac wierzcholki */

   while(startNode == finalNode)
   {
      startNode = rand() % this->nodeNum;
      finalNode = rand() % this->nodeNum;
   }

   vector<int> startPermutation = CreateRandomPermutation(this->nodeNum);
   vector<int> newPermutation(startPermutation);

   swap(newPermutation[startNode], newPermutation[finalNode]);

   return abs((double)(CountPathLength(startPermutation) - CountPathLength(newPermutation)) / log(0.99));  /* T(start) = delta(F) / log(P) */
}

void SimulatedAnnealing::SetFreezingLevel(double level)
{
   this->freezingLevel = level;
}

void SimulatedAnnealing::StartAlgorithm()
{
   this->maxRepeatCount = 100 * this->nodeNum;   /* dlugosc epoki */
   this->temperature = CountStartTemperature();    /* ustawienie poczatkowej temperatury */

   double time = 0;
   double usedTime = 0;
   clock_t start = clock();

   int startNode = 0, finalNode = 0;   /* ustawiamy na zero aby wylosowac do zamiany */

   vector<int> bestPath = CreateStartPath();
   vector<int> actualPath(bestPath);

   int result = INT_MAX;

   while(time < this->stopTime)
   {
      for(auto i =0;i<this->maxRepeatCount;i++)
      {
         startNode = 0; finalNode = 0;
         while(startNode == finalNode) /* losowanie wierzcholkow do zamiany */
         {
            startNode = rand() % this->nodeNum;
            finalNode = rand() % this->nodeNum;
         }
         actualPath = bestPath;
         swap(actualPath[startNode], actualPath[finalNode]);   /* tworzenie nowej sciezki */

         int actualPathLength = CountPathLength(actualPath);
         if(actualPathLength - result < 0)   /* funkcja oceny ruchu */
         {
            result = actualPathLength;       /* ustawiamy biezaca dlugosc */
            this->solutionPath = actualPath; /* ustawiamy biezace najlepsze rozwiazanie */
            usedTime = (clock() - start) / (double)CLOCKS_PER_SEC;
         }

         if(CountPathLength(bestPath) - CountPathLength(actualPath) > 0)
         {
            bestPath = actualPath;
         }
         else
         if((exp(CountPathLength(bestPath) - CountPathLength(actualPath)) / this->temperature) > ((double)rand() / RAND_MAX))
         {
            bestPath = actualPath; /* akceptowanie gorszego rozwiazania z pewnym p */
         }
      }

      this->temperature = this->temperature * this->freezingLevel; /* ochladzamy T = aT*/
      time = (clock() - start) / (double)CLOCKS_PER_SEC;
   }

   this->solutionTime = usedTime; /* ustawianie wartosci rozwiazania */
   this->solutionLength = result;
}

void SimulatedAnnealing::PrintSolution()
{
   cout<<"Sciezka: ";
   for(auto i = 0; i<this->nodeNum;i++)
   {
      if(i==this->nodeNum - 1)
      {
         cout<<this->solutionPath[i];
      }
      else
      {
         cout<<this->solutionPath[i]<<"-";
      }
   }
   cout<<"Dlugosc: "<<this->solutionLength<<endl;
   cout<<"Czas rozwiazania: "<<this->solutionTime<<" s"<<endl;
   cout<<"Temperatura finalna "<<this->temperature<<endl;
}
