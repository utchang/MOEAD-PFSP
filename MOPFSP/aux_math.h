#ifndef AUX_MATH
#define AUX_MATH

#include <vector>
#include <cstdlib>
#include "individual.h"

namespace MathAux
{
    inline double uniform(double lb, double ub)
        { return static_cast<double>(rand()) / RAND_MAX*(ub - lb) + lb; }
    inline int random(int lb, int ub)
        { return rand() % (ub-lb+1) + lb; }
    inline double square(double n) { return n*n; }
    double average(const std::vector<double>&);
    double stddev(const std::vector<double>&);
    int min(const std::vector<int>&);
    int max(const std::vector<int>&);

    void rand_seq(std::vector<int>& seq, int lb, int ub, int size);
    double euclidean_distance(const std::vector<double>&, const std::vector<double>&);
    double perpendicular_distance(const std::vector<double>&, const std::vector<double>&);
    void normalize(std::vector<double>& nv, const std::vector<int>& v, const std::vector<int>& min, const std::vector<int>& max);
}

#endif // AUX_MATH
