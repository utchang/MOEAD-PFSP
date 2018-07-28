#ifndef CINSTANCE_H
#define CINSTANCE_H

#include <vector>
#include <fstream>

const int MAX_MACHINE = 20;
const int MAX_JOB = 100;

class CInstance
{
    public:
        CInstance() {}
        bool load(std::ifstream&);

        int processingTimes(int machineId, int jobId) const { return _processingTimes[machineId][jobId]; }
        std::size_t numJobs() const { return _numJobs; }
        std::size_t numMachines() const { return _numMachines; }
        int Id() const { return _id; }
    private:
        std::vector<std::vector<int>> _processingTimes;
        std::size_t _numJobs = 0;
        std::size_t _numMachines = 0;
        int _id = 0;
};

#endif // CINSTANCE_H
