#include "moead.h"
#include "parameter.h"
#include "instance.h"
#include "evaluator.h"
#include "aux_math.h"
#include <climits>

void CMOEAD::solve(const CInstance& instance)
{
    _subproblems.resize(POPULATION_SIZE);
    initial_solutions(instance);
    initial_weights();
    initial_neighbors();
    num_evaluations += POPULATION_SIZE;

    _ideal.resize(NUM_OBJECTIVES, INT_MAX);
    _nadir.resize(NUM_OBJECTIVES, 0);

    for(std::size_t i = 0; i < POPULATION_SIZE; i += 1)
    {
        update_ideal(_subproblems[i].sol());
        _solutions.update(_subproblems[i].sol());
    }

    static std::vector<int> parents(2);
    static std::vector<CIndividual> offspring(2);
    for(CIndividual& indv : offspring)
    {
        indv.objs().resize(NUM_OBJECTIVES);
        indv.vars().resize(instance.numJobs());
    }

    for(int i = 0; i < NUM_GENERATIONS; i += 1)
    {
        update_nadir();
        for(int j = 0; j < POPULATION_SIZE; j += 1)
        {
            //TODO
        }
        num_evaluations += POPULATION_SIZE;
    }
}

void CMOEAD::initial_weights()
{
    std::vector<double> weights(POPULATION_SIZE);
    for(std::size_t i = 0; i < weights.size(); i += 1)
    {
        weights[i] = 1. - i / (weights.size() - 1.);
    }
    weights.front() -= 1e6;
    weights.back() += 1e6;

    for(std::size_t i = 0; i < _subproblems.size(); i += 1)
    {
        _subproblems[i].w().resize(NUM_OBJECTIVES);
        _subproblems[i].w()[0] = weights[i];
        _subproblems[i].w()[1] = 1. - weights[i];
    }
}

void CMOEAD::initial_solutions(const CInstance& instance)
{
    for(CSubproblem& p : _subproblems)
    {
        CIndividual indv(instance.numJobs());
        indv.shuffle();
        Evaluate(indv, instance);
        p.sol() = indv;
    }
}

void CMOEAD::initial_neighbors()
{
    for(std::size_t i = 0; i < _subproblems.size(); i += 1)
    {
        _subproblems[i].m_nei().resize(MATING_NEIGHBOR_SIZE);
        _subproblems[i].r_nei().resize(REPLACE_NEIGHBOR_SIZE);

        std::vector< std::pair<double, std::size_t> > distance;
        distance.reserve(POPULATION_SIZE);
        for(std::size_t j = 0; j < POPULATION_SIZE; j += 1)
        {
            double dist = MathAux::euclidean_distance(_subproblems[i].w(),
                                                      _subproblems[j].w());
            distance.push_back(std::make_pair(dist, j));
        }
        std::sort(distance.begin(), distance.end());

        for(std::size_t j = 0; j < MATING_NEIGHBOR_SIZE; j += 1)
        {
            _subproblems[i].m_nei()[j] = distance[j].second;
        }

        for(std::size_t j = 0; j < REPLACE_NEIGHBOR_SIZE; j += 1)
        {
            _subproblems[i].r_nei()[j] = distance[j].second;
        }
    }
}

void CMOEAD::update_ideal(const CIndividual& indv)
{
    for(std::size_t i = 0; i < NUM_OBJECTIVES; i += 1)
    {
        _ideal[i] = std::min(_ideal[i], indv.objs()[i]);
    }
}

void CMOEAD::update_nadir()
{
    static std::vector<int> maximum(NUM_OBJECTIVES);
    std::fill(maximum.begin(), maximum.end(), 0);

    for(const CSubproblem& p : _subproblems)
    {
        for(std::size_t i = 0; i < NUM_OBJECTIVES; i += 1)
        {
            maximum[i] = std::max(maximum[i], p.sol().objs()[i]);
        }
    }
    _nadir = maximum;
}

