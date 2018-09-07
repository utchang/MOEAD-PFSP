#ifndef ARCHIVE_H
#define ARCHIVE_H

#include "individual.h"
#include <ostream>

class CArchive : public CPopulation
{
    public:
        bool update(const CIndividual& indv);
};

#endif // ARCHIVE_H
