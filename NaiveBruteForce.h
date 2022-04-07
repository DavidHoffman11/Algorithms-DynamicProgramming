#ifndef LAB_3_DYNAMIC_PROGRAMMING_DAVIDHOFFMAN11_NAIVEBRUTEFORCE_H
#define LAB_3_DYNAMIC_PROGRAMMING_DAVIDHOFFMAN11_NAIVEBRUTEFORCE_H
#include "Node.h"
#include <vector>
#include <map>

class NaiveBruteForce {
public:
    static void NaiveAlgo(map<int, Node>&, Node);
    static float &returnCost();
    static int returnIterations();
    static vector<int> &returnPath();

private:
    static float getDistance(Node, Node, map<int, Node> &);
    static float cost;
    static int iterations;
    static vector<int> path;
};

#endif //LAB_3_DYNAMIC_PROGRAMMING_DAVIDHOFFMAN11_NAIVEBRUTEFORCE_H