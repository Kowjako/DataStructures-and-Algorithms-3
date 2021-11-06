#include <iostream>
#include "graphreader.h"

using namespace std;

GraphReader reader;

int main()
{
    string loc;
    cout<<"Wprowadz lokalizacje pliku"<<endl;
    cin>>loc;

    if(reader.ReadFromFile(loc))
    {
       cout<<"Pomyslnie wczytano"<<endl;
       reader.PrintGraph();
    }

    return 0;
}
