#ifndef CINSTANCE_H
#define CINSTANCE_H

#include <vector>
#include <fstream>

class CInstance
{
    public:
        CInstance() {}
        bool load(std::ifstream&);

        int processingTimes(int machineId, int jobId) const { return _processingTimes[machineId][jobId]; }
        int numJobs() const { return _numJobs; }
        int numMachines() const { return _numMachines; }
        int Id() const { return _id; }
    private:
        std::vector<std::vector<int>> _processingTimes;
        int _numJobs = 0;
        int _numMachines = 0;
        int _id = 0;
};

#endif // CINSTANCE_H
