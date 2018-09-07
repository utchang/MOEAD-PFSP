#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <algorithm>
#include "archive.h"

class CInstance;

class BAlgorithm
{
    public:
        BAlgorithm(const std::string& name):_name(name) {}
        virtual ~BAlgorithm() {}
        virtual void solve(const CInstance& instance) = 0;

        std::string name() const { return _name; }
        int num_evaluations = 0;
        const CArchive& solutions() {
            std::sort(_solutions.begin(), _solutions.end());
            return _solutions; }
    protected:
        std::string _name;
        CArchive _solutions;
};

#endif // ALGORITHM_H
