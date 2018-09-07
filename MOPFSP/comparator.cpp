#include "comparator.h"
#include "individual.h"

CParetoDominate ParetoDominate;

bool CParetoDominate::operator()(const CIndividual& l, const CIndividual& r) const
{
	bool better = false;
	for (std::size_t f=0; f<l.objs().size(); f+=1)
	{
		if (l.objs()[f] > r.objs()[f])
			return false;
		else if (l.objs()[f] < r.objs()[f])
			better = true;
	}

	return better;
}
