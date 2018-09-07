#include "aux_math.h"
#include <cmath>
#include <climits>
#include <algorithm>

double MathAux::average(const std::vector<double>& nums)
{
    double total = 0.;
    for(double n : nums) total += n;
    return total/nums.size();
}

double MathAux::stddev(const std::vector<double>& nums)
{
    double avg = average(nums);
    double total = 0.;
    for(double n : nums) total += square(n - avg);
    return sqrt(total/(nums.size()-1));
}

int MathAux::min(const std::vector<int>& nums)
{
    int m = INT_MAX;
    for(int n : nums)
    {
        m = std::min(m, n);
    }
    return m;
}

int MathAux::max(const std::vector<int>& nums)
{
    int m = INT_MIN;
    for(int n : nums)
    {
        m = std::max(m, n);
    }
    return m;
}

void MathAux::rand_seq(std::vector<int>& seq, int lb, int ub, int size)
{
    static std::vector<int> numbers;
    numbers.resize(ub-lb+1);
    std::fill(numbers.begin(), numbers.end(), 0);

    for(int& n : numbers)
    {
        n = lb;
        lb += 1;
    }
    std::random_shuffle(numbers.begin(), numbers.end());

    seq.resize(size);
    for(std::size_t i = 0; i < seq.size(); i += 1)
    {
        seq[i] = numbers[i];
    }
}

double MathAux::euclidean_distance(const std::vector<double>& p,
                                   const std::vector<double>& q)
{
    double d = 0.;
    for(std::size_t i = 0; i < p.size(); i += 1)
    {
        double diff = (p[i] - q[i]);
        d += diff*diff;
    }
    return sqrt(d);
}
