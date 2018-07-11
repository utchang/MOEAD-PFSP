#include "instance.h"

/*
20 5 1
54 83 15 71 77 36 53 38 27 87 76 91 14 29 12 77 32 87 68 94
79 3 11 99 56 70 99 60 5 56 3 61 73 75 47 14 21 86 5 77
16 89 49 15 89 45 60 23 57 64 7 1 63 41 63 47 26 75 77 40
66 58 31 68 78 91 13 59 49 85 85 9 39 41 56 40 54 77 51 31
58 56 20 85 53 35 53 41 69 13 86 72 8 49 47 87 58 18 68 28
*/

bool CInstance::load(std::ifstream& ifile)
{
    if(!ifile.is_open()) return false;

    ifile >> _numJobs >> _numMachines >> _id;

    _processingTimes.resize(_numMachines, std::vector<int>(_numJobs));
    for(std::vector<int>& row : _processingTimes)
        for(int& time : row)
            ifile >> time;

    return true;
}
