#include <iostream>
#include "branchbound.h"
#include "bruteforce.h"
#include "dynamicprogramming.h"

using namespace std;

BranchBound BB;
BruteForce BF;
DynamicProgramming DP;

int main()
{
    string loc;
    cout << "Witam w projekcie PEA 1"<<endl;
    cout << "Wprowadz nazwe pliku"<<endl;
    cin>>loc;
    bool isReaded = DP.ReadFromFile(loc);

    if(isReaded) {
      //BB.PrintGraph();
      //BB.SolveTSP();
      //BB.PrintSolution();
      DP.PrintGraph();
      DP.InitializePathArray();
      DP.PrintSolution();
    }

    return 0;
}
