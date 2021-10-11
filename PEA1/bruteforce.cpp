#include "bruteforce.h"

BruteForce::BruteForce()
{
   //ctor
}

BruteForce::~BruteForce()
{
   delete[] this->tmpPermutation;
   delete[] this->finalPermutation;

   for(int i=0;i<this->node_num ;i++)
        delete[] this->macierz[i];
       delete[] this->macierz;
}

void BruteForce::SetValueForMatrix(int i, int j ,int value)
{
   this->macierz[i][j] = value;
}

bool BruteForce::ReadFromFile(string filename)
{
   ifstream file(filename);
   if(file.is_open())
   {
      int distance;
      file>>this->node_num;                           /* inicjalizacja liczby wierzcholkow */

      this->finalPermutation = new int*[this->node_num];   /* inicjalizacja miejsca dla koncowej permutacji */
      this->tmpPermutation = new int*[this->node_num];   /* inicjalizacja miejsca dla chwilowej permutacji */

      if(file.fail())
      {
         cout<<"Blad podczas odczytywania poczatkowych wartosci"<<endl;
         return false;
      }

      this->macierz = new int*[this->node_num];    /* alokacja macierzy sasiedztwa */

      for(int i = 0;i<this->node_num;i++)           /* uzupelnianie macierzy sasiedztwa */
      {
         this->macierz[i] = new int[this->node_num];
         for(int j = 0;j<this->node_num;j++)
         {
            file >> distance;
            SetValueForMatrix(i,j, distance);
         }
      }
      return true;

   }
   else
   {
      cout<<"Blad podczas otwierania pliku"<<endl;
      return false;
   }
}

void BruteForce::PrintGraph()
{
   for(int i=0;i<node_num;i++) {
        for(int j = 0;j<node_num;j++)
            cout<<this->macierz[i][j]<<'\t';
        cout<<endl;
   }
}

void BruteForce::PrintSolution()
{

}

void BruteForce::Start()
{
   for(int i=0;i<this->node_num;i++)
   {
      this->tmpPermutation[i] = i;                 /* inicjalizacja startowej permutacji */
   }
   StartBrute(1);
}

void BruteForce::StartBrute(int nodeNumber)
{

}
