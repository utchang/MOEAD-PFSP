#ifndef CLINEARORDERCROSSOVER_H
#define CLINEARORDERCROSSOVER_H

#include "individual.h"
#include "parameter.h"

class CLinearOrderCrossover
{
    public:
        explicit CLinearOrderCrossover(double cr = CROSSOVER_RATE):_cr(cr) {}
        bool operator()(std::vector<CIndividual>&, const std::vector<CIndividual>&) const;
    private:
        double _cr;
};

#endif // CLINEARORDERCROSSOVER_H
