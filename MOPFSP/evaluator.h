#ifndef CEVALUATOR_H
#define CEVALUATOR_H

#include "individual.h"
#include "instance.h"
#include <fstream>

class CEvaluator
{
    public:
        void operator()(CIndividual&, const CInstance&) const;
        void detail(CIndividual&, const CInstance&) const;
        bool genttable(std::ofstream&, const CIndividual&, const CInstance&);
};

extern CEvaluator Evaluate;

#endif // CEVALUATOR_H
