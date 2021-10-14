#include "branchbound.h"

BranchBound::BranchBound() {}

BranchBound::~BranchBound()
{
       delete[] this->checked;
       delete[] this->minimumTab;

       for(int i=0;i<this->node_num ;i++)
        delete[] this->macierz[i];
       delete[] this->macierz;
}

bool BranchBound::ReadFromFile(string filename)
{
   ifstream file(filename);
   if(file.is_open())
   {
      int distance;
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


   string values;
   while(!this->finalPath.empty())
   {
      values += to_string(finalPath.top());  /* pobieramy wierzcholek */
      values += ' ';
      finalPath.pop();              /* usuwamy */
   }

   reverse(values.begin(), values.end());

   cout<<values<<" 0 "<<endl;
}

void BranchBound::SolveTSP()
{
   int ograniczenieStartowe = 0;
   /* Ustawienie ograniczenia startowego */
   int minimum = INT_MAX;
   for(int i=0;i<this->node_num;i++)
   {
      checked[i] = false;                    /* inicjalizacja wartosci tablicy odwiedzonych */
      for(int j=0;j<this->node_num;j++)
      {
         if(this->macierz[i][j] < minimum && this->macierz[i][j] != 9999)
         {
            minimum = this->macierz[i][j];
         }
      }
      this->minimumTab[i] = minimum;
      ograniczenieStartowe += minimum;     /* ograniczenie startowe ustawiam jako minimalne wartosci drog kazdego z wierzcholkow */
      minimum = INT_MAX;
   }

   Node startNode;      /* wierzcholek poczatkowy */
   startNode.value = 0;
   startNode.ograniczenie = ograniczenieStartowe; /*wpisujemy mu ograniczenie startowe wyliczone powyzej */
   Start(startNode);

}

int BranchBound::LowLimit(Node node, int next)
{
   int value = node.ograniczenie;                  /* wynik = gr.dolne + odlegl. pomiedzy wierzch. - min.wartosc wierzcholka */
   value -= this->minimumTab[node.value];
   value += this->macierz[node.value][next];
   return value;
}

void BranchBound::HighLimit(Node node)
{
   int value = LowLimit(node, 0);         /* obliczamy sciezke od liscia do korzenia */
   if(value < this->ograniczenieGorne)    /* jezeli granica jest lepsza to aktualizaujemy sciezke i granice */
   {
      this->finalPath = this->actualPath;
      this->ograniczenieGorne = value;
   }
}

bool operator<(const Node& a, const Node& b)
{
      return a.ograniczenie > b.ograniczenie;
}


void BranchBound::Start(Node startNode)
{
      actualPath.push(startNode.value);     /* wrzucamy na stos */
      checked[startNode.value] = true;    /* ustawiamy na odwiedzony */

      Node tmp;
      priority_queue<Node> kolejka;

      for(int i=0;i<this->node_num;i++)
      {
         if(checked[i] == false)
         {
            tmp.value = i;
            tmp.ograniczenie = LowLimit(startNode, i);      /* obliczamy dla kazdego wierzcholka dolne ograniczenie */
            kolejka.push(tmp);
         }
      }

      if(kolejka.empty())
      {
         HighLimit(startNode);      /* Tu trafimy jezeli wszystkie wierzcholki beda zwiedzone -> trafilismy do liscia wiec ustawiamy gorne ograniczenie */
      }
      else
      {
         while(!kolejka.empty())
         {
            tmp = kolejka.top();  /* pobieramy wierzcholek z najmniejsza granica i od razu go usuwamy z kolejki */
            kolejka.pop();

            if(tmp.ograniczenie <= this->ograniczenieGorne)
            {
               Start(tmp);  /* znaczy ta sciezka ma sens i musimy ja sprawdzic */
            }
            else
            {
               break;      /* sciezka nie ma sensu wiec odrzucamy (ograniczenie wieksze niz obecne) */
            }
         }
      }
      actualPath.pop();
      checked[startNode.value] = false;
}





