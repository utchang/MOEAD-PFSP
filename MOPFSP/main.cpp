#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#include "instance.h"
#include "individual.h"
#include "evaluator.h"

void loadInstance(CInstance& instance, const string& fname)
{
    ifstream ifile;
    ifile.open(fname, std::ifstream::in);
    if(instance.load(ifile))
        ifile.close();
    else
        exit(1);
}

void loadAllInstance(vector<CInstance>& instances)
{
    string jobs[3] = {"20", "50", "100"};
    string machines[3] = {"5", "10", "20"};
    string ids[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    for(const string& j : jobs)
    {
        for(const string& m : machines)
        {
            for(const string& i : ids)
            {
                string fileName = "TaillardInstance/";
                fileName += "tai" + j + "_" + m + "_" + i + ".txt";
                CInstance ins;
                loadInstance(ins, fileName);
                instances.push_back(ins);
            }
        }
    }
}

int main()
{
    vector<CInstance> instances;
    loadAllInstance(instances);

    CIndividual indv(instances[0].numJobs());
    //Evaluate(indv, instances[0]);
    Evaluate.detail(indv, instances[0]);
    cout << indv << endl;
    return 0;
}
