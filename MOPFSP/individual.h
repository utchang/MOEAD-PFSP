#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H

#include <vector>

class CIndividual
{
    public:
        typedef int TGene;
        typedef std::vector<TGene> TDecVec;
        typedef std::vector<int> TObjVec;

        CIndividual() {}
        explicit CIndividual(size_t size):_permutation(size){
            for(size_t i = 0; i < size; i += 1) { _permutation[i] = i; } }

        size_t size() const { return _permutation.size(); }
        const TDecVec& vars() const { return _permutation; }
        TDecVec& vars() { return _permutation; }
        const TObjVec& objs() const { return _objectives; }
        TObjVec& objs() { return _objectives; }
        const TGene& operator[](size_t i) const { return _permutation[i]; }
        TGene& operator[](size_t i) { return _permutation[i]; }

    private:
        TDecVec _permutation;
        TObjVec _objectives;
};

#endif // CINDIVIDUAL_H
