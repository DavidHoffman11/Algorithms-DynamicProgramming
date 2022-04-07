#ifndef LAB_2_DYNAMIC_PROGRAMMING_DAVIDHOFFMAN11_RUNTSP_H
#define LAB_2_DYNAMIC_PROGRAMMING_DAVIDHOFFMAN11_RUNTSP_H
#include "Node.h"
#include "Algorithm.h"
#include "NaiveBruteForce.h"
#include "DynamicProgramming.h"
#include <iostream>
#include <map>
#include <chrono>
#include <vector>

using namespace std;

class RunTSP: public Algorithm {
public:
    RunTSP();
    ~RunTSP();
    void load();
    void execute();
    void display();
    void stats();
    void select(int);
private:
    map<int, Node> graph;
    chrono::duration<double> runTime;
    NaiveBruteForce* naiveBF;
    DynamicProgramming* dynamicProg;
    vector<int> bestPath;
    int algoExecute;
    int numIterations;
    float lowestDistance;
    Node src, dest;
};

#endif //LAB_2_DYNAMIC_PROGRAMMING_DAVIDHOFFMAN11_RUNTSP_H
