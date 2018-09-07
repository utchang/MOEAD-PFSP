#include "evaluator.h"
#include "individual.h"
#include "instance.h"
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
