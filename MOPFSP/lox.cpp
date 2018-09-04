#include "lox.h"
#include "aux_math.h"

static std::vector<int> cut_point;
static std::vector<std::vector<int>> mark;

bool CLinearOrderCrossover::operator()(std::vector<CIndividual>& offspring,
                                       const std::vector<CIndividual>& parents) const
{
    if(MathAux::uniform(0, 1) < _cr) return false;

    // length of individual
    const int length = int(parents[0].size());

    // (m, n) is the cut points of parents, m < n
    MathAux::rand_seq(cut_point, 0, length, 2);
    int m = MathAux::min(cut_point);
    int n = MathAux::max(cut_point);

    // resize and clear
    offspring.resize(2);
    mark.resize(2, std::vector<int>(length));
    mark.clear();

    // stage 1
    for(std::size_t i = 0; i < offspring.size(); i += 1)
    {
        offspring[i].vars().resize(length);
        offspring[i].objs().resize(NUM_OBJECTIVES);
        for(int j = m; j <= n; j += 1)
        {
            int gene = parents[i][j];
            offspring[i][j] = gene;
            mark[i][gene] = 1;
        }
    }

    // stage 2
    for(std::size_t i = 0, j = 0; i < offspring.size(); i += 1)
    {
        // gene from another parents, start from the beginning
        int gene = parents[!i][j];

        for(int k = 0; k < length; k += 1)
        {
            if(k < m || k > n)
            {
                // find a gene haven't placed
                while(mark[i][gene]) j += 1;
                offspring[i][j] = gene;
                mark[i][gene] = 1;
            }
        }
    }

    return true;
}
