#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>

class CInstance;
class CArchive;

class BAlgorithm
{
    public:
        BAlgorithm(const std::string& name):_name(name) {}
        virtual ~BAlgorithm() {}
        virtual void Solve(CArchive& solutions, const CInstance& instance) = 0;

        std::string name() const { return _name; }
        int num_evaluations = 0;
    protected:
        std::string _name;
};

#endif // ALGORITHM_H
