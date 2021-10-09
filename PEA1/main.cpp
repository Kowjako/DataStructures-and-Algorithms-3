#include <iostream>
#include "branchbound.h"

using namespace std;

BranchBound BB;

int main()
{
    string loc;
    cout << "Witam w projekcie PEA 1"<<endl;
    cout << "Wprowadz nazwe pliku"<<endl;
    cin>>loc;
    BB.ReadFromFile(loc);
    BB.Print();
    return 0;
}
