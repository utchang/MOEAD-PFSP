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
        bool local_replacement(const CIndividual&, std::size_t);
        bool global_replacement(const CIndividual&);
        bool distance_replacement(const CIndividual&);
        double weighted_sum(const CIndividual::TObjVec&, const CSubproblem::TWeiObj&, const std::vector<int>&, const std::vector<int>&) const;
        double tchebycheff(const CIndividual::TObjVec&, const CSubproblem::TWeiObj&, const std::vector<int>&, const std::vector<int>&) const;
};

#endif // MOEAD_H
