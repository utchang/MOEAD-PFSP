#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <ostream>
#include "individual.h"

class CArchive : public TPopulation
{
    public:
        bool update(const CIndividual& indv);
};

#endif // ARCHIVE_H
