#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H

#include <vector>

const int NUM_OBJECTIVES = 2;

class CIndividual
{
    public:
        typedef int TGene;
        typedef std::vector<TGene> TDecVec;
        typedef std::vector<int> TObjVec;

        CIndividual():_objectives(NUM_OBJECTIVES) {}
        explicit CIndividual(std::size_t s):_permutation(s), _objectives(NUM_OBJECTIVES) {
            for(std::size_t i = 0; i < s; i += 1) { _permutation[i] = i; } }

        std::size_t size() const { return _permutation.size(); }
        const TDecVec& vars() const { return _permutation; }
        TDecVec& vars() { return _permutation; }
        const TObjVec& objs() const { return _objectives; }
        TObjVec& objs() { return _objectives; }
        const TGene& operator[](std::size_t i) const { return _permutation[i]; }
        TGene& operator[](std::size_t i) { return _permutation[i]; }

    private:
        TDecVec _permutation;
        TObjVec _objectives;
};

typedef std::vector<CIndividual> CPopulation;

#endif // CINDIVIDUAL_H
