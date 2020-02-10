//
// Created by yuvalshechter on 05/02/2020.
//

#ifndef EX4_DFS_H
#define EX4_DFS_H


#include "Searcher.h"
#include "Searchable.h"
#include "HelpfulFunctionsForMatrix.h"
#include <iostream>
#include <stack>
#include <map>
#include <string>
#include <vector>
using namespace std;

/**
 * This class is DFS algorithm.
 */
class DFS : public  Searcher
{
private:
    int evaluatedNodes;
    void searchDFS(string* answer, Searchable* searchable, map<string, vector<State*>> adjacent_map,map<string,bool> visited_map, State* current, State* goalState);
public:
    virtual string search(Searchable* searchable) ;
    virtual ~DFS();
    virtual int NumOfNodesEvaluated();
};



#endif //EX4_DFS_H