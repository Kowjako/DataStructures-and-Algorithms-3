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
    cout << "Witam w projekcie PEA 1"<<endl;
    string loc;
    int operationNumber;
    bool isReaded;
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

    do {
        cout<<"1. Branch & Bound"<<endl;
        cout<<"2. Bruteforce"<<endl;
        cout<<"3. Dynamic Programming"<<endl;
        cout<<"4. Koniec programu"<<endl;
        cin>>operationNumber;
        switch(operationNumber) {
            case 1:
                cout<<"Wprowadz lokalizacje pliku"<<endl;
                cin>>loc;
                isReaded = BB.ReadFromFile(loc);
                if(isReaded)
                {
                   start = read_QPC();
                   BB.SolveTSP();
                   elapsed = read_QPC() - start;
                   BB.PrintSolution();
                }
                break;
            case 2:
                cout<<"Wprowadz lokalizacje pliku"<<endl;
                cin>>loc;
                isReaded = BF.ReadFromFile(loc);
                if(isReaded)
                {
                   start = read_QPC();
                   BF.Start();
                   elapsed = read_QPC() - start;
                   BF.PrintSolution();
                }
                break;
            case 3:
                cout<<"Wprowadz lokalizacje pliku"<<endl;
                cin>>loc;
                isReaded = DP.ReadFromFile(loc);
                if(isReaded)
                {
                   start = read_QPC();
                   DP.InitializePathArray();
                   elapsed = read_QPC() - start;
                   DP.PrintSolution();
                }
                break;
            default:
                break;
        }

        cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;

    } while(operationNumber!=4);

    return 0;
}
