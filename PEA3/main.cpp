#include <iostream>
#include "graphreader.h"
#include "GeneticAlgorithm.h"

using namespace std;

GraphReader reader;
GeneticAlgorithm GA;

int main()
{
    cout << "Hello world!" << endl;
    vector<vector<int>> SA;
    vector<int> test {10,9,8,7,6,5,4,3,2,1};
    SA.push_back(test);

    cout<<"START"<<endl;
    GA.MutationInversion(SA);

    cout<<"OK"<<endl;
    for(auto i =0;i<SA.size();i++)
        for(auto j=0;j<SA.at(i).size();j++)
            cout<<SA.at(i)[j]<<" ";

    return 0;
}
