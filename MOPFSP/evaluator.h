#ifndef CEVALUATOR_H
#define CEVALUATOR_H

#include "individual.h"
#include "instance.h"
#include <fstream>

class CEvaluator
{
    public:
        void operator()(CIndividual&, const CInstance&) const;
};

extern CEvaluator Evaluate;

#endif // CEVALUATOR_H
