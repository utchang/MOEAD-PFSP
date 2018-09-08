#include "moead.h"
#include "parameter.h"
#include "instance.h"
#include "evaluator.h"
#include "aux_math.h"
#include "comparator.h"
#include "mutation.h"
#include "lox.h"
#include <climits>

#include <iostream>
using namespace std;
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

    static std::vector<int> parents_id(2);
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
            mating(parents_id, j);
            const std::vector<CIndividual>& parents = { _subproblems[parents_id[0]].sol(),
                                                        _subproblems[parents_id[1]].sol()};
            LinearOrderCrossover(offspring, parents);
            for(std::size_t k = 0; k < offspring.size(); k += 1)
            {
                InsertMutation(offspring[k]);
                Evaluate(offspring[k], instance);
                _solutions.update(offspring[k]);
                update_ideal(offspring[k]);
                local_replacement(offspring[k], j);

                // other replacement:
                //global_replacement(offspring[k]);
                //distance_replacement(offspring[k]);
            }
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

void CMOEAD::mating(std::vector<int>& parents_id, std::size_t p_id) const
{
    std::size_t range = (MathAux::uniform(0, 1) < MATING_RATE)?MATING_NEIGHBOR_SIZE:POPULATION_SIZE;
    MathAux::rand_seq(parents_id, 0, range-1, 2);
    if(range == MATING_NEIGHBOR_SIZE)
    {
        for(std::size_t i = 0; i < parents_id.size(); i += 1)
        {
            parents_id[i] = _subproblems[p_id].m_nei()[parents_id[i]];
        }
    }
}

bool CMOEAD::local_replacement(const CIndividual& indv, std::size_t p_id)
{
    static std::vector<int> max_objs;
    max_objs = _nadir;
    for(std::size_t i = 0; i < max_objs.size(); i += 1)
    {
        max_objs[i] = std::max(max_objs[i], indv.objs()[i]);
    }

    std::random_shuffle(_subproblems[p_id].r_nei().begin(), _subproblems[p_id].r_nei().end());

    for(std::size_t i = 0; i < REPLACE_NEIGHBOR_SIZE; i += 1)
    {
        std::size_t k = _subproblems[p_id].r_nei()[i];
        double new_fit = tchebycheff(indv.objs(), _subproblems[k].w(), _ideal, max_objs);
        double old_fit = tchebycheff(_subproblems[k].sol().objs(), _subproblems[k].w(), _ideal, max_objs);
        if(new_fit < old_fit || (new_fit == old_fit && !ParetoDominate(_subproblems[p_id].sol(), indv)))
        {
            _subproblems[k].sol() = indv;
            return true;
        }
    }
    return false;
}

bool CMOEAD::global_replacement(const CIndividual& indv)
{
    static std::vector<int> max_objs;
    max_objs = _nadir;
    for(std::size_t i = 0; i < max_objs.size(); i += 1)
    {
        max_objs[i] = std::max(max_objs[i], indv.objs()[i]);
    }

    double best_fit = std::numeric_limits<double>::max();
    std::size_t id = 0;
    for(std::size_t i = 0; i < POPULATION_SIZE; i += 1)
    {
        // in the GR method, the WS scalar function can't be use
        double f = tchebycheff(indv.objs(), _subproblems[i].w(), _ideal, max_objs);
        if(f < best_fit)
        {
            best_fit = f;
            id = i;
        }
    }

    std::random_shuffle(_subproblems[id].r_nei().begin(), _subproblems[id].r_nei().end());
    for(std::size_t i = 0; i < REPLACE_NEIGHBOR_SIZE; i += 1)
    {
        std::size_t k = _subproblems[id].r_nei()[i];
        double new_fit = tchebycheff(indv.objs(), _subproblems[k].w(), _ideal, max_objs);
        double old_fit = tchebycheff(_subproblems[k].sol().objs(), _subproblems[k].w(), _ideal, max_objs);
        if(new_fit < old_fit || (new_fit == old_fit && !ParetoDominate(_subproblems[id].sol(), indv)))
        {
            _subproblems[k].sol() = indv;
            return true;
        }
    }
    return false;
}

bool CMOEAD::distance_replacement(const CIndividual& indv)
{
    static std::vector<int> max_objs;
    max_objs = _nadir;
    for(std::size_t i = 0; i < max_objs.size(); i += 1)
    {
        max_objs[i] = std::max(max_objs[i], indv.objs()[i]);
    }

    static std::vector<double> point(NUM_OBJECTIVES);
    MathAux::normalize(point, indv.objs(), _ideal, max_objs);

    static std::vector< std::pair<double, std::size_t> > rank(POPULATION_SIZE);
    static std::vector<double> d(POPULATION_SIZE);
    static CSubproblem::TWeiObj w(NUM_OBJECTIVES);
    for(std::size_t i = 0; i < d.size(); i += 1)
    {
        w = _subproblems[i].w();
        // if using WS as scalar function
        // std::swap(w[0], w[1]);

        d[i] = MathAux::perpendicular_distance(w, point);
        rank[i] = std::make_pair(d[i], i);
    }

    std::sort(rank.begin(), rank.end());

    for(std::size_t i = 0; i < REPLACE_NEIGHBOR_SIZE; i += 1)
    {
        std::size_t id = rank[i].second;

        double new_fit = tchebycheff(indv.objs(), _subproblems[id].w(), _ideal, max_objs);
        double old_fit = tchebycheff(_subproblems[id].sol().objs(), _subproblems[id].w(), _ideal, max_objs);
        if(new_fit < old_fit || (new_fit == old_fit && !ParetoDominate(_subproblems[id].sol(), indv)))
        {
            _subproblems[id].sol() = indv;
            return true;
        }
    }

    return false;
}

double CMOEAD::weighted_sum(const CIndividual::TObjVec& objs,
                            const CSubproblem::TWeiObj& weight,
                            const std::vector<int>& min,
                            const std::vector<int>& max) const
{
    static std::vector<double> val(NUM_OBJECTIVES);
    MathAux::normalize(val, objs, min, max);

    double fitness = 0.;
    for(std::size_t i = 0; i < NUM_GENERATIONS; i += 1)
    {
        fitness += val[i] * weight[i];
    }
    return fitness;
}

double CMOEAD::tchebycheff(const CIndividual::TObjVec& objs,
                           const CSubproblem::TWeiObj& weight,
                           const std::vector<int>& min,
                           const std::vector<int>& max) const
{
    static std::vector<double> val(NUM_OBJECTIVES);
    MathAux::normalize(val, objs, min, max);

    double fitness = 0.;
    for(std::size_t i = 0; i < NUM_OBJECTIVES; i += 1)
    {
        double f = val[i]*weight[i];
        fitness = std::max(fitness, f);
    }
    return fitness;
}
