#include "lox.h"
#include "aux_math.h"

CLinearOrderCrossover LinearOrderCrossover;

static std::vector<int> cut_point;
static std::vector<std::vector<int>> mark;

bool CLinearOrderCrossover::operator()(std::vector<CIndividual>& offspring,
                                       const std::vector<CIndividual>& parents) const
{
    if(MathAux::uniform(0, 1) > _cr) return false;

    // length of individual
    const int length = int(parents[0].size());

    // resize and reset to zero
    offspring.resize(2);
    mark.resize(2, std::vector<int>(length));
    for(std::vector<int>& v : mark)
        std::fill(v.begin(), v.end(), 0);
    std::fill(cut_point.begin(), cut_point.end(), 0);

    // (m, n) is the cut points of parents, m < n
    MathAux::rand_seq(cut_point, 0, length-1, 2);
    int m = MathAux::min(cut_point);
    int n = MathAux::max(cut_point);

    // stage 1
    for(std::size_t i = 0; i < offspring.size(); i += 1)
    {
        offspring[i].vars().resize(length);
        offspring[i].objs().resize(NUM_OBJECTIVES);
        for(int j = m; j <= n; j += 1)
        {
            CIndividual::TGene gene = parents[i][j];
            offspring[i][j] = gene;
            mark[i][gene] = 1;
        }
    }

    // stage 2
    for(std::size_t i = 0; i < offspring.size(); i += 1)
    {
        int j = 0;
        for(int k = 0; k < length; k += 1)
        {
            if(k < m || k > n)
            {
                // find a gene haven't placed
                while(mark[i][parents[!i][j]]) j += 1;
                offspring[i][k] = parents[!i][j];
                mark[i][parents[!i][j]] = 1;
            }
        }
    }

    return true;
}
