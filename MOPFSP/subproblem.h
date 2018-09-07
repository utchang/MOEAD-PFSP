#ifndef SUBPROBLEM_H
#define SUBPROBLEM_H

#include <vector>
#include "individual.h"

class CSubproblem
{
    public:
        typedef std::vector<double> TWeiObj;
        typedef std::vector<std::size_t> TNeiObj;

        CSubproblem():_weight(NUM_OBJECTIVES) {}

        const CIndividual& sol() const { return _solution; }
        CIndividual& sol() { return _solution; }
        const TWeiObj& w() const { return _weight; }
        TWeiObj& w() { return _weight; }
        const TNeiObj& m_nei() const { return _mating_neighbors; }
        TNeiObj& m_nei() { return _mating_neighbors; }
        const TNeiObj& r_nei() const { return _replace_neighbors; }
        TNeiObj& r_nei() { return _replace_neighbors; }
    private:
        CIndividual _solution;
        TWeiObj _weight;
        TNeiObj _mating_neighbors;
        TNeiObj _replace_neighbors;
};

typedef std::vector<CSubproblem> TProblemSet;

#endif // SUBPROBLEM_H
