#include "archive.h"
#include "comparator.h"
#include <algorithm>

bool CArchive::update(const CIndividual& indv)
{
    std::vector<CIndividual>& solutions = (*this);

    bool accepted = true;
    for(std::size_t i = 0; i < solutions.size(); i += 1)
    {
        if(ParetoDominate(solutions[i], indv)
           || solutions[i].objs() == indv.objs())
        {
            accepted = false;
            break;
        }
    }

    if(accepted)
    {
        for(std::vector<CIndividual>::iterator i = solutions.begin(); i != solutions.end(); )
        {
            std::size_t id = std::distance(solutions.begin(), i);
            if(ParetoDominate(indv, solutions[id]))
            {
                i = solutions.erase(i);
            }
            else
            {
                ++i;
            }
        }
        solutions.push_back(indv);
    }
    return accepted;
}
