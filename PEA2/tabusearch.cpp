#include "tabusearch.h"

TabuSearch::TabuSearch()
{
   //ctor
}

TabuSearch::~TabuSearch()
{
   //dtor
}

void TabuSearch::SetMatrix(int** copyMatrix, int nodenum)
{
   this->macierz = copyMatrix;
   this->nodeNum = nodenum;
}

void TabuSearch::PrintMatrix()
{
   for(auto i =0;i<this->nodeNum;i++)
   {
      for(auto j = 0;j<this->nodeNum;j++)
         cout<<this->macierz[i][j]<<" ";
      cout<<endl;
   }
}

void TabuSearch::SetStopTime(double time)
{
   this->stopTime = time;
}

vector<int> TabuSearch::CreateRandomPermutation(int permSize)
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

int TabuSearch::CountPathLength(vector<int> path)
{
   auto length = 0;
   for(auto i = 0;i<path.size() - 1;i++)
   {
      length += this->macierz[path[i]][path[i + 1]]; /*obliczanie drogi pomiedzy kolejnymi wierzcholkami w sciezce */
   }
   length += this->macierz[path[this->nodeNum - 1]][0]; /* dodanie odleglosci do poczatkowego */
   return length;
}

vector<int> TabuSearch::CreateStartPath()
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

vector<int> TabuSearch::FindNextMove(vector<int> path, int pathLength)
{
   int bestLength = pathLength;  /* najlepsze obecne rozwiazanie */
   vector<int> minPath = path;
   int minLength = INT_MAX;       /* minimalna sciezka */

   for(auto i = 0;i<this->nodeNum - 1;i++)
      for(auto j = i+1;j<this->nodeNum;j++)
      {
         bool isBanned = false;
         vector<int> actualPath;
         for(auto a = 0;a<this->BannedMoves.size();a++)
         {
            if(i==this->BannedMoves[a].startNode && j==this->BannedMoves[a].finishNode)   /* kryterium aspiracji -
            sprawdzenie ruchu zakazanego czy nie da lepsze rozwiazanie */
            {
               actualPath = path;
               swap(actualPath[i],actualPath[j]);
               int actualPathLength = CountPathLength(actualPath);
               if(actualPathLength < bestLength && actualPathLength < minLength)
               {
                  minPath = actualPath;
                  minLength = actualPathLength;
                  bestLength = actualPathLength;
               }
               isBanned = true;
               break;
            }
         }
         if(!isBanned)  /* jezeli ruch jest dozwolony */
         {
            actualPath = path;
            swap(actualPath[i], actualPath[j]);
            int actualPathLength = CountPathLength(actualPath);
            if(actualPathLength < minLength) /* jezeli koszt sciezki jest lepszy */
            {
               minLength = actualPathLength;
               minPath = actualPath;
               this->startNode = i; /* wierzcholek poczatku ruchu */
               this->finishNode = j; /* wierzcholek konca ruchu */
            }
         }
      }

   return minPath;
}

void TabuSearch::StartAlgorithm()
{
   vector<int> bestPath =  CreateStartPath();
   vector<int> actualPath(bestPath);

   double time = 0;
   double usedTime  = 0;
   this->frequency = this->nodeNum;
   clock_t start = clock();

   int i =0;
   while(time <= this->stopTime)
   {
      actualPath = FindNextMove(actualPath, CountPathLength(bestPath));

      if(CountPathLength(actualPath) - CountPathLength(bestPath) < 0)   /* f-ja oceny ruchu */
      {
         cout<<"GO " <<i<<endl;
         bestPath = actualPath;
         usedTime = (clock() - start) / (double)CLOCKS_PER_SEC;   /* ustawienie czasu algorytmu (uzyteczny czas a nie calkowity) */
         i++;
      }

      Move tmp;
      tmp.frequency = this->frequency + rand() % this->frequency;
      tmp.startNode = (finishNode < startNode) ? finishNode : startNode;   /* Ustawiamy mniejszy indeks jako poczatek */
      tmp.finishNode = (finishNode < startNode) ? startNode : finishNode;
      this->BannedMoves.push_back(tmp);


      for(auto offset = 0;offset< this->BannedMoves.size();offset++)  /* sprawdzenie ruchow zakazanych */
      {
         if(this->BannedMoves[offset].reduceFrequency()) /* zmniejszamy czestotliwosc wystepowania ruchu */
         {
            this->BannedMoves.erase(this->BannedMoves.begin() + offset);   /* jezeli czestotliwosc jest 0 znaczy mozna juz odblokowac ten ruch */
         }
      }

      time = (clock() - start) / (double)CLOCKS_PER_SEC;   /* aktualizacja czasu jaki juz minal */
   }

   this->finalPath = bestPath;
   this->finalPathLength = CountPathLength(this->finalPath);
   this->finalTime = usedTime;

}

void TabuSearch::PrintSolution()
{
   cout<<"Sciezka: "<<endl;
   for(auto i =0;i<this->nodeNum;i++)
   {
      if(i == this->nodeNum - 1)
      {
         cout<<this->finalPath[i];
      }
      else
      {
         cout<<this->finalPath[i]<<" - ";
      }
   }
   cout<<endl;
   cout<<"Dlugosc: "<<this->finalPathLength<<endl;
   cout<<"Czas rozwiazania: "<<this->finalTime<<endl;
}
