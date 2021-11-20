#include <iostream>
#include "graphreader.h"
#include "tabusearch.h"
#include "simulatedannealing.h"
#include <windows.h>
#include <iomanip>

using namespace std;

GraphReader reader;
TabuSearch ts;
SimulatedAnnealing sa;

long long int read_QPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}

long long int frequency, start, elapsed;

int main()
{
    int operationNumber;
    double stopTime;
    double freezingLevel;
    string loc;
    cout<<"Witam w projekcie PEA 2"<<endl;

    do
    {
        cout<<"1. Wczytaj plik"<<endl;
        cout<<"2. Wprowadz czas stopu"<<endl;
        cout<<"3. Tabu Search"<<endl;
        cout<<"4. Simulated Annealing"<<endl;
        cout<<"5. Koniec programu"<<endl;
        cin >> operationNumber;
        switch(operationNumber)
        {
            case 1:
               cout<<"Wprowadz lokalizacje pliku"<<endl;
               cin>>loc;
               if(reader.ReadFromFile(loc))
               {
                  cout<<"Pomyslnie wczytano"<<endl;
                  ts.SetMatrix(reader.getMacierz(), reader.getNodeNum());
                  sa.SetMatrix(reader.getMacierz(), reader.getNodeNum());
               }
               break;
            case 2:
               cout<<"Wprowadz czas stopu"<<endl;
               cin>>stopTime;
               break;
            case 3:
               srand(time(NULL));
               ts.SetStopTime(stopTime);
               ts.StartAlgorithm();
               ts.PrintSolution();
               break;
            case 4:
               sa.SetStopTime(stopTime);
               cout<<"Wprowadz wspolczynnik chlodzenia, np: 0.95"<<endl;
               cin>>freezingLevel;
               srand(time(NULL));
               sa.SetFreezingLevel(freezingLevel);
               sa.StartAlgorithm();
               sa.PrintSolution();
               break;
            default:
               break;
        }
    }
    while(operationNumber!=5);

    return 0;
}
