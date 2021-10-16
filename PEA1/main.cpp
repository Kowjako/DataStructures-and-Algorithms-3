#include <iostream>
#include "branchbound.h"
#include "bruteforce.h"
#include "dynamicprogramming.h"
#include <windows.h>
#include <iomanip>


using namespace std;

BranchBound BB;
BruteForce BF;
DynamicProgramming DP;

long long int read_QPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}

long long int frequency, start, elapsed;

int main()
{

   QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

    string loc;
    cout << "Witam w projekcie PEA 1"<<endl;
    cout << "Wprowadz nazwe pliku"<<endl;
    cin>>loc;
    bool isReaded = DP.ReadFromFile(loc);

    if(isReaded) {
      //BF.PrintGraph();
     // BF.Start();
     // BF.PrintSolution();
      //DP.PrintGraph();
      //start = read_QPC();
      DP.InitializePathArray();
      DP.PrintGraph();
      //elapsed = read_QPC() - start;
      DP.PrintSolution();
    }

    cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed /
frequency << endl;

    return 0;
}
