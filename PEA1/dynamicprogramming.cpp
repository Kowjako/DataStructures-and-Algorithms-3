#include "dynamicprogramming.h"

DynamicProgramming::DynamicProgramming()
{
   //ctor
}

DynamicProgramming::~DynamicProgramming()
{

   for(int i=0;i<this->node_num ;i++)
        delete[] this->macierz[i];
       delete[] this->macierz;
}

void DynamicProgramming::ClearValues()
{
   cout<<"Czyszczenie poprzednich wartosci ... "<<endl;

   for(int i=0;i<this->node_num ;i++)
      delete[] this->macierz[i];
   delete[] this->macierz;

   this->d.clear();
   this->track.clear();
}

bool DynamicProgramming::ReadFromFile(string filename)
{
   if(this->node_num != 0)
   {
      ClearValues();
   }

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
            SetMatrixValue(i,j, distance);
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

void DynamicProgramming::InitializePathArray()
{
	this->d.resize((1<<this->node_num), vector<int>(this->node_num, 9999));	/* inicjalizacja 2^n*n macierzy */
	this->track.resize((1<<this->node_num), vector<int>(this->node_num, 9999999));

	for(int i=1;i<this->node_num;i++)
   {
      this->track[(1<<i) | 1][i] = 0;
   }

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

void DynamicProgramming::SetMatrixValue(int i, int j, int value)
{
   this->macierz[i][j] = value;
}

void DynamicProgramming::PrintSolution()
{
	cout<<"Najkrotsza sciezka : ";
	cout<<d[(1<<this->node_num) - 1][0] << endl;

	cout<<"Sciezka : ";
   string values;

	int prev, actual = this->lastNode, mask = (1<<this->node_num) - 1;

	cout<<"0 - ";

   for(int i = this->node_num - 2;i>0;i--)
   {
      prev = this->track[mask][actual];
      values.insert(0, to_string(prev) + " - ");
      mask = mask ^ (1<<actual);
      actual = prev;
   }
   cout<<values<<this->lastNode<<" - 0"<<endl;
}



void DynamicProgramming::Start()
{
   int prevValue = 0;
	for(int mask = 0; mask < (1<<this->node_num); mask++)	/* iterowanie wszystkich masek od 0 do 2^n */
	{
		for(int i = 0;i<this->node_num;i++)	/* sprawdzenie miast od 0 do n */
		{
			if(d[mask][i] == 9999) continue;
			for(int j = 0;j<this->node_num;j++)	/* miasto docelowe */
			{
				if(!(mask & (1<<j)))  /* dane miasto nie jest zawarte w aktualnej masce */
            {
               prevValue = d[mask ^ (1<<j)][j]; /* poprzednia wartosc podejrzanej komorki */
               d[mask ^ (1<<j)][j] = min(d[mask ^ (1<<j)][j],d[mask][i] + this->macierz[i][j]); /* wybranie najlepszej sciezki */

               /** Nastapila zmiana wartosci **/
               if(prevValue != d[mask ^ (1<<j)][j])
               {
                  /** Jezeli strzal do finalnej komorki **/
                  if(mask ^ (1<<j) == (1<<this->node_num) - 1 && j == 0)
                  {
                     this->lastNode = i;  /* ustawiamy ostatni wierzcholek z ktorego osiagnieto 0 */
                  }

                  if(prevValue > d[mask][i] + this->macierz[i][j])
                  {
                     this->track[mask | (1<<j)][j] = i;  /* aktualizacja wierzcholka gdy sciezka jest lepsza */
                  }

               }
               if(prevValue == d[mask][i] + this->macierz[i][j])
               {
                  if(this->track[mask | (1<<j)][j] == 0)
                     this->track[mask | (1<<j)][j] = i;
               }
            }
			}
		}
	}
}
