#ifndef CEVALUATOR_H
#define CEVALUATOR_H

#include <fstream>

class CIndividual;
class CInstance;

class CEvaluator
{
    public:
        void operator()(CIndividual&, const CInstance&) const;
};

extern CEvaluator Evaluate;

#endif // CEVALUATOR_H
