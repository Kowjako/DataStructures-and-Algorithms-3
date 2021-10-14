#include "dynamicprogramming.h"

DynamicProgramming::DynamicProgramming()
{
   //ctor
}

DynamicProgramming::~DynamicProgramming()
{
   //dtor
}

bool DynamicProgramming::ReadFromFile()
{
   ifstream file(filename);
   if(file.is_open())
   {
      int distance;
      file>>this->node_num;                           /* inicjalizacja liczby wierzcholkow */

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
	  
	  InitializePathArray();
	  
      return true;

   }
   else
   {
      cout<<"Blad podczas otwierania pliku"<<endl;
      return false;
   }
}

void DynamicProgramming::InitializePathArray()
{
	this->d.resize((1<<this->node_num), vector<int>(this->node_num, INT_MAX));	/* inicjalizacja 2^n*n macierzy */
	this->d[0][0] = 0;
	Start();
}

void DynamicProgramming::PrintGraph() 
{
	for(int i=0;i<node_num;i++) {
        for(int j = 0;j<node_num;j++)
            cout<<this->macierz[i][j]<<'\t';
        cout<<endl;
   }
}

void DynamicProgramming::Start()
{
	for(int mask = 0; mask < (1<<n); mask++)	/*sprawdzenie wszystkich masek od 0 do 2^n */
	{
		for(int i =0;i<this->node_num;i++)	/* sprawdzenie miast od 0 do n */
		{
			if(d[mask][i] == INT_MAX) continue;		
			for(int j = 0;j<this->node_num;j++)	/* miasto docelowe */
			{
				if(!(mask & (1<<j)))	/* dane miasto nie jest zawarte w aktualnej masce */
					d[mask ^ (1<<j)][j] = min(d[mask ^ (1<<j)][j],d[mask][i] + a[i][j]); /* wybranie najlepszej sciezki */
			} 
		}
	}
	//d[mask][i]  -min droga jezeli odwiedzil mask miast i jest obecnie w i-tym miescie
}