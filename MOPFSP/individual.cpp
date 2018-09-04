#include "individual.h"
#include <ostream>
#include <iomanip>

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
