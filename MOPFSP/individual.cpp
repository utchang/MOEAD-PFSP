#include "individual.h"
#include <ostream>
#include <iomanip>

bool operator < (const CIndividual& l, const CIndividual& r)
{
    if(l.objs()[0] < r.objs()[0]) return true;
    else if(l.objs()[0] == r.objs()[0])
    {
        return l.objs()[1] > r.objs()[1];
    }
    else return false;
}

std::ostream & operator << (std::ostream &os, const std::vector<int>& vec)
{
    for(int v : vec)
        os << v << ' ';
    return os;
}

std::ostream & operator << (std::ostream &os, const CIndividual& indv)
{
	os << indv.vars() << " => " << indv.objs();
	return os;
}
