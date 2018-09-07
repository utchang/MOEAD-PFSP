#ifndef MOEAD_H
#define MOEAD_H

#include "algorithm.h"
#include "subproblem.h"

class CInstance;

class CMOEAD : public BAlgorithm
{
    public:
        CMOEAD(const std::string& name = "MOEAD"):BAlgorithm(name) {}
        ~CMOEAD(){}
        void solve(const CInstance&);
    private:
        std::vector<int> _ideal;
        std::vector<int> _nadir;
        TProblemSet _subproblems;

        void initial_weights();
        void initial_neighbors();
        void initial_solutions(const CInstance&);
        void update_ideal(const CIndividual&);
        void update_nadir();
        void mating(std::vector<int>&, std::size_t) const;
        void local_replacement(const CIndividual&, std::size_t);
        void global_replacement(const CIndividual&);
        void distance_replacement(const CIndividual&);
};

#endif // MOEAD_H
