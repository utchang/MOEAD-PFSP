#include "evaluator.h"
#include <vector>
#include <string>

CEvaluator Evaluate;

void CEvaluator::operator()(CIndividual& indv, const CInstance& instance) const
{
    // completion time (span) for each machines
    // declare to static variables due to avoid reallocating space every time
    static std::vector<int> span;
    // clean up
    span.resize(instance.numMachines());
    for(int& time : span) time = 0;

    // accumulate completion time for each jobs
    int totalFlowTime = 0;
    for(std::size_t jobId = 0; jobId < indv.size(); jobId += 1)
    {
        span[0] += instance.processingTimes(0, indv[jobId]);

        for(std::size_t machineId = 1; machineId < instance.numMachines(); machineId += 1)
        {
            span[machineId] = std::max(span[machineId], span[machineId-1])
                              + instance.processingTimes(machineId, indv[jobId]);
        }
        totalFlowTime += span.back();
    }

    // update objectives
    indv.objs()[0] = span.back();
    indv.objs()[1] = totalFlowTime;
}

void CEvaluator::detail(CIndividual& indv, const CInstance& instance) const
{
    // use 2d array to store information of schedule
    indv.schedule.resize(instance.numMachines(), std::vector<int>(instance.numJobs()));

    for(std::size_t machineId = 0; machineId < instance.numMachines(); machineId += 1)
    {
        indv.schedule[machineId][0] = instance.processingTimes(machineId, indv[0]);
        if(machineId > 0) indv.schedule[machineId][0] += indv.schedule[machineId-1][0];
    }

    int totalFlowTime = indv.schedule[instance.numMachines()-1][0];
    for(std::size_t jobId = 1; jobId < instance.numJobs(); jobId += 1)
    {
        indv.schedule[0][jobId] = indv.schedule[0][jobId-1] + instance.processingTimes(0, indv[jobId]);

        for(std::size_t machineId = 1; machineId < instance.numMachines(); machineId += 1)
        {
            indv.schedule[machineId][jobId] = std::max(indv.schedule[machineId-1][jobId], indv.schedule[machineId][jobId-1])
                                              + instance.processingTimes(machineId, indv[jobId]);
        }

        totalFlowTime += indv.schedule[instance.numMachines()-1][jobId];
    }

    indv.objs()[0] = indv.schedule[instance.numMachines()-1].back();
    indv.objs()[1] = totalFlowTime;
}

bool CEvaluator::genttable(std::ofstream& ofile, const CIndividual& indv, const CInstance& instance)
{
    if(indv.schedule.size() > 0)
    {
        if(!ofile.is_open()) return false;

        for(std::size_t i = 0; i < indv.schedule.size(); i += 1)
        {
            std::string mid = "M" + std::to_string(i+1);
            for(std::size_t j = 0; j < indv.schedule[i].size(); j += 1)
            {
                std::string jid = "J" + std::to_string(j+1);
                std::string task = mid + ",";
                task += std::to_string(indv.schedule[i][j] - instance.processingTimes(i, j));
                task = task + "," + std::to_string(indv.schedule[i][j]) + "," + jid + "\n";
                ofile << task;
            }
        }

        return true;
    }
    return false;
}
