#include "branchbound.h"

BranchBound::BranchBound() {}

BranchBound::~BranchBound()
{
       delete[] this->checked;
       delete[] this->minimumTab;
}

bool BranchBound::ReadFromFile(string filename)
{
   ifstream file(filename);
   if(file.is_open())
   {
      int nodenum, distance;
      file>>this->node_num;                             /* inicjalizacja liczby wierzcholkow */

      this->checked = new bool[this->node_num];       /* inicjalizacja odwiedzonych wierzcholkow */
      this->minimumTab = new int[this->node_num];     /* inicjalizacja tablicy min. wartosci */

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

void BranchBound::SetValueForMatrix(int i, int j, int value)
{
   this->macierz[i][j] = value;
}

void BranchBound::PrintGraph()
{
   for(int i=0;i<node_num;i++) {
        for(int j = 0;j<node_num;j++)
            cout<<this->macierz[i][j]<<'\t';
        cout<<endl;
   }
}

void BranchBound::PrintSolution()
{
   cout<<"Minimalna dlugosc wynosi : "<<this->ograniczenieGorne<<endl;
   cout<<"Sciezka : ";
   cout<<"0 ";
   while(!this->finalPath.empty())
   {
      int value = finalPath.top();  /* pobieramy wierzcholek */
      cout<<value<<" ";             /* wyswietlamy */
      finalPath.pop();              /* usuwamy */
   }
}


void BranchBound::SolveTSP()
{
   int ograniczenieStartowe = 0;
   /* Ustawienie ograniczenia dolnego */
   int minimum = INT_MAX;
   for(int i=0;i<this->node_num;i++)
   {
      checked[i] = false;
      for(int j=0;j<this->node_num;j++)
      {
         if(this->macierz[i][j] < minimum && this->macierz[i][j] != 9999)
         {
            minimum = this->macierz[i][j];
         }
      }
      this->minimumTab[i] = minimum;
      ograniczenieStartowe += minimum;     /* ograniczenie dolne ustawiam jako minimalne wartosci drog kazdego z wierzcholkow */
      minimum = INT_MAX;
   }

   Node startNode;      /* wierzcholek poczatkowy */
   startNode.value = 0;
   startNode.ograniczenie = ograniczenieStartowe; /*wpisujemy mu ograniczenie dolne na wyliczone powyzej */
   Start(startNode);

}

/* Ograniczenie dolne */
int BranchBound::LowLimit(Node node, int next)
{
   int value = node.ograniczenie;                  /* wynik = aktualne ogr.dolne + odlegl. pomiedzy wierzch. - min.wartosc wierzcholka */
   value -= this->minimumTab[node.value];
   value += this->macierz[node.value][next];
   return value;
}

void BranchBound::HighLimit(Node node)
{
   int value = LowLimit(node, 0);
   if(value < this->ograniczenieGorne)
   {
      this->finalPath = this->actualPath;
      this->ograniczenieGorne = value;
   }
}

void BranchBound::Start(Node startNode)
{
      actualPath.push(startNode.value);     /* wrzucamy na stos */
      checked[startNode.value] = true;    /* ustawiamy na odwiedzony */

      Node tmp;
      queue<Node> kolejka;

      for(int i=0;i<this->node_num;i++)
      {
         if(checked[i] == false)
         {
            tmp.value = i;
            tmp.ograniczenie = LowLimit(startNode, i);      /* obliczamy dolne ograniczenie */
            kolejka.push(tmp);
         }
      }

      if(kolejka.empty())
      {
         HighLimit(startNode);      /* Tu trafimy jezeli wszystkie wierzcholki beda zwiedzone */
      }
      else
      {
         while(!kolejka.empty())
         {
            tmp = kolejka.front();  /* pobieramy pierwszy z kolejki i od razu go usuwamy z kolejki */
            kolejka.pop();

            if(tmp.ograniczenie < this->ograniczenieGorne)
            {
               Start(tmp); /* znaczy ta sciezka ma sens i musimy ja sprawdzic */
            }
            else
            {
               break;
            }
         }
      }
      actualPath.pop();
      checked[startNode.value] = false;
}





