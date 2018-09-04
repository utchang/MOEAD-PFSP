#include "mutation.h"
#include "aux_math.h"

CInsertMutation InsertMutation;
CSwapMutation SwapMutation;

bool CInsertMutation::operator()(CIndividual& indv) const
{
    CIndividual::TDecVec& permutation = indv.vars();

	bool mutated = false;
	for (size_t i = 0; i < indv.size(); i += 1)
	{
		if (MathAux::uniform(0, 1) < _mr)
		{
			size_t j;
			do {
				j = MathAux::random(0, indv.size() - 1);
			} while (i == j);
            size_t m = std::min(i, j), n = std::max(i, j);

            // forward or backward insertion
            if(MathAux::uniform(0, 1) < 0.5)
            {
                CIndividual::TGene job = indv[m];
                permutation.erase(permutation.begin()+m);
                permutation.insert(permutation.begin()+n, job);
            }
            else
            {
                CIndividual::TGene job = indv[n];
                permutation.erase(permutation.begin()+n);
                permutation.insert(permutation.begin()+m, job);
            }

			mutated = true;
		}
	}
	return mutated;
}

bool CSwapMutation::operator()(CIndividual& indv) const
{
    bool mutated = false;
	for (size_t i = 0; i < indv.size(); i += 1)
	{
		if (MathAux::uniform(0, 1) < _mr)
		{
			size_t j;
			do {
				j = MathAux::random(0, indv.size() - 1);
			} while (i == j);
            std::swap(indv[i], indv[j]);

			mutated = true;
		}
	}
	return mutated;
}
