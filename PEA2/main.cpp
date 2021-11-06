#include <iostream>
#include "graphreader.h"
#include "tabusearch.h"

using namespace std;

GraphReader reader;
TabuSearch ts;

int main()
{
    string loc;
    cout<<"Wprowadz lokalizacje pliku"<<endl;
    cin>>loc;

    if(reader.ReadFromFile(loc))
    {
       cout<<"Pomyslnie wczytano"<<endl;
       reader.PrintGraph();
       ts.SetMatrix(reader.getMacierz(), reader.getNodeNum());
    }



    return 0;
}
