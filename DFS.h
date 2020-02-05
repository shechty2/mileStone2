//
// Created by yuvalshechter on 05/02/2020.
//

#ifndef EX4_DFS_H
#define EX4_DFS_H


#include <map>
#include <string>
#include <vector>
#include "Searcher.h"
#include "Searchable.h"


using namespace std;

class DFS : public  Searcher
{
private:
    int evaluated_nodes;
    void searchDFS(string* answer, Searchable* searchable, map<string, vector<State*>> adjacent_map,map<string,bool> visited_map, State* current, State* goalState);
public:
    virtual string search(Searchable* searchable) ;
    virtual ~DFS();
    virtual int getNumberOfNodesEvaluated();
};



#endif //EX4_DFS_H
