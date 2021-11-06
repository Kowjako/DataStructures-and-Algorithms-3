#include "graphreader.h"

GraphReader::GraphReader()
{
   //ctor
}

GraphReader::~GraphReader()
{
   for(int i=0;i<this->nodeNum ;i++)
        delete[] this->macierz[i];
       delete[] this->macierz;
}

int GraphReader::getNodeNum()
{
   return this->nodeNum;
}

int** GraphReader::getMacierz()
{
   return this->macierz;
}

bool GraphReader::ReadFromFile(string filename)
{
   if(this->nodeNum != 0)
   {
       ClearValues();
   }

   ifstream file(filename);
   if(file.is_open())
   {
      int distance;
      file>>this->nodeNum;                             /* inicjalizacja liczby wierzcholkow */

      if(file.fail())
      {
         cout<<"Blad podczas odczytywania poczatkowych wartosci"<<endl;
         return false;
      }

      this->macierz = new int*[this->nodeNum];    /* alokacja macierzy sasiedztwa */

      for(int i = 0;i<this->nodeNum;i++)           /* uzupelnianie macierzy sasiedztwa */
      {
         this->macierz[i] = new int[this->nodeNum];
         for(int j = 0;j<this->nodeNum;j++)
         {
            file >> distance;
            this->macierz[i][j] = distance;
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

void GraphReader::ClearValues()
{
   cout<<"Czyszczenie poprzednich wartosci ... "<<endl;

   for(int i=0;i<this->nodeNum ;i++)
      delete[] this->macierz[i];
   delete[] this->macierz;
}

void GraphReader::PrintGraph()
{
   for(auto i =0;i<this->nodeNum;i++)
   {
      for(auto j = 0;j<this->nodeNum;j++)
         cout<<this->macierz[i][j]<<" ";
      cout<<endl;
   }
}

