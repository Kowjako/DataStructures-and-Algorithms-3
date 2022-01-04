#include <iostream>
#include "graphreader.h"
#include "GeneticAlgorithm.h"

using namespace std;

GraphReader reader;
GeneticAlgorithm GA;

int main()
{
    int operationNumber, population, crossType;
    double stopTime, crossP, mutationP;
    string loc;
    cout<<"Witam w projekcie PEA 3"<<endl;

    do
    {
        cout<<"1. Wczytaj plik"<<endl;
        cout<<"2. Wprowadz parametry"<<endl;
        cout<<"3. Algorytm genetyczny"<<endl;
        cout<<"4. Koniec programu"<<endl;
        cin >> operationNumber;
        switch(operationNumber)
        {
            case 1:
               cout<<"Wprowadz lokalizacje pliku"<<endl;
               cin>>loc;
               if(reader.ReadFromFile(loc))
               {
                  cout<<"Pomyslnie wczytano"<<endl;
                  GA.SetMatrix(reader.getMacierz(), reader.getNodeNum());
               }
               break;
            case 2:
               cout<<"Wprowadz czas stopu"<<endl;
               cin>>stopTime;
               cout<<"Wprowadz liczebnosc populacji (np. 5000)"<<endl;
               cin>>population;
               cout<<"Wprowadz wsp. krzyzowania (np. 0.9)"<<endl;
               cin>>crossP;
               cout<<"Wprowadz wsp. mutacji (np. 0.01)"<<endl;
               cin>>mutationP;
               cout<<"Wybierz krzyzowanie: 1 - OX, 2 - PMX"<<endl;
               cin>>crossType;
               GA.SetSpecificParameters(stopTime,mutationP,crossP,population,crossType);
               break;
            case 3:
               GA.StartAlgorithm();
               break;
            default:
               break;
        }
    }
    while(operationNumber!=4);
    return 0;
}
