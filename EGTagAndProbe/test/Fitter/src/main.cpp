#include <iostream>
#include <vector>

#include "TurnonManager.h"

using namespace std;


int main(int argc, char** argv)
{
    if(argc!=2)
    {
        cout<<"Usage: fit.exe configFile\n";
        return 1;
    }
    string config(argv[1]);

    TurnonManager turnons;
    bool status = turnons.readConfig(config);
    if(!status) return 1;
    turnons.fit();

    return 0;
}
