#ifndef CLINEARORDERCROSSOVER_H
#define CLINEARORDERCROSSOVER_H

#include "parameter.h"
#include <vector>

class CIndividual;

class CLinearOrderCrossover
{
    public:
        explicit CLinearOrderCrossover(double cr = CROSSOVER_RATE):_cr(cr) {}
        bool operator()(std::vector<CIndividual>&, const std::vector<CIndividual>&) const;
    private:
        double _cr;
};

extern CLinearOrderCrossover LinearOrderCrossover;

#endif // CLINEARORDERCROSSOVER_H
