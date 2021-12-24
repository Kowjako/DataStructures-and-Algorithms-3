#include <iostream>
#include "graphreader.h"
#include "GeneticAlgorithm.h"

using namespace std;

GraphReader reader;
GeneticAlgorithm GA;

int main()
{
    cout << "Hello world!" << endl;
    vector<int> test {1,2,3,4,5,6,7,8,9};
    vector<int> test2 {5, 3, 6,7,8,1,2,9,4};

    GA.CrossoverPMX(test, test2);

    for(auto i =0;i<9;i++)
        cout<<test[i]<<" ";

        cout<<endl;

    for(auto i =0;i<9;i++)
        cout<<test2[i]<<" ";

    return 0;
}
