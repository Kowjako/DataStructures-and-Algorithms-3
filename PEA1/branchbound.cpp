#include "branchbound.h"

BranchBound::BranchBound() {}

BranchBound::~BranchBound()
{
       //dtor
}

bool BranchBound::ReadFromFile(string filename)
{
   ifstream file(filename);
   if(file.is_open())
   {
      int nodenum, distance;
      file>>this->node_num;
      if(file.fail())
      {
         cout<<"Blad podczas odczytywania poczatkowych wartosci"<<endl;
         return false;
      }

      string str;
      getline(file,str);

      this->macierz = new int*[this->node_num];    /* alokacja macierzy sasiedztwa */

      for(int i = 0;i<this->node_num;i++)           /* uzupelnianie macierzy sasiedztwa */
      {
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

void BranchBound::SetValueForMatrix(int i, int j, int value)
{
   this->macierz[i][j] = value;
}

void BranchBound::Print()
{
   for(int i=0;i<node_num;i++) {
        for(int j = 0;j<node_num;j++)
            cout<<this->macierz[i][j]<<" ";
        cout<<endl;
   }
}
