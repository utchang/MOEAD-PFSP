#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#include "instance.h"
#include "individual.h"
#include "evaluator.h"
#include "lox.h"
#include "mutation.h"
#include "archive.h"

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
    srand(0);

    vector<CInstance> instances;
    loadAllInstance(instances);

    const CInstance& ins = instances[0];
    const int num_jobs = ins.numJobs();

    // random generate 2 individuals
    CIndividual a(num_jobs), b(num_jobs);
    a.shuffle();
    b.shuffle();
    Evaluate(a, ins);
    Evaluate(b, ins);
    cout << a << endl << b << endl;

    // lox testing
    vector<CIndividual> offspring;
    const vector<CIndividual>& parents = {a, b};
    LinearOrderCrossover(offspring, parents);
    Evaluate(offspring[0], ins);
    Evaluate(offspring[1], ins);
    cout << offspring[0] << endl << offspring[1] << endl;

    // mutation testing
    if(InsertMutation(offspring[0])) Evaluate(offspring[0], ins);
    if(SwapMutation(offspring[1])) Evaluate(offspring[1], ins);
    cout << offspring[0] << endl << offspring[1] << endl;

    cout << "==================================" << endl;
    // ParetoDominance testing
    CArchive solutions;
    for(int i = 0; i < 10; i += 1)
    {
        CIndividual s(num_jobs);
        s.shuffle();
        Evaluate(s, ins);
        cout << s << endl;
        solutions.update(s);
    }
    cout << "==================================" << endl;
    std::sort(solutions.begin(), solutions.end());
    for(const CIndividual& indv : solutions)
        cout << indv << endl;
    return 0;
}
