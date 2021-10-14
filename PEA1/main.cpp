#include <iostream>
#include "branchbound.h"
#include "bruteforce.h"

using namespace std;

BranchBound BB;
BruteForce BF;

int main()
{
    string loc;
    cout << "Witam w projekcie PEA 1"<<endl;
    cout << "Wprowadz nazwe pliku"<<endl;
    cin>>loc;
    bool isReaded = BF.ReadFromFile(loc);

    if(isReaded) {
      //BB.PrintGraph();
      //BB.SolveTSP();
      //BB.PrintSolution();
      BF.PrintGraph();
      BF.Start();
      BF.PrintSolution();
    }

    return 0;
}
