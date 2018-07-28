#include "individual.h"
#include <ostream>
#include <iomanip>

std::ostream & operator << (std::ostream &os, const CIndividual& indv)
{
    if(indv.schedule.size() > 0)
    {
        os << "--- completion time for each stage ---" << std::endl;
        for(const std::vector<int>& row : indv.schedule)
        {
            for(int time : row)
                os << std::setw(5) << time;
            os << std::endl;
        }
        os << std::endl;
    }

	for(std::size_t i = 0; i < indv.vars().size(); i += 1)
	{
		os << indv.vars()[i] << ' ';
	}

	os << " => ";

	for(std::size_t f = 0; f < indv.objs().size(); f += 1)
	{
		os << indv.objs()[f] << ' ';
	}

	return os;
}
