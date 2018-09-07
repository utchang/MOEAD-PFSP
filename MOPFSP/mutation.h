#ifndef CINSERTMUTATION_H
#define CINSERTMUTATION_H

#include "parameter.h"

class CIndividual;

class CInsertMutation
{
    public:
        CInsertMutation(double mr = MUTATION_RATE):_mr(mr) {}
        bool operator()(CIndividual&) const;
    private:
        double _mr;
};

class CSwapMutation
{
    public:
        CSwapMutation(double mr = MUTATION_RATE):_mr(mr) {}
        bool operator()(CIndividual&) const;
    private:
        double _mr;
};

extern CInsertMutation InsertMutation;
extern CSwapMutation SwapMutation;

#endif // CINSERTMUTATION_H
