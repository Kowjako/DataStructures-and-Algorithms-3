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
    bool isReaded = BB.ReadFromFile(loc);

    if(isReaded) {
      BB.PrintGraph();
      BB.SolveTSP();
      BB.PrintSolution();
    }

    return 0;
}
