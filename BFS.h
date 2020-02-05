//
// Created by yuvalshechter on 05/02/2020.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H


#include <map>
#include <string>
#include <vector>
#include "Searcher.h"
#include "Searchable.h"
#include <iostream>
#include "queue"
using namespace std;

class BFS: public Searcher{
private:
    int evaluated_nodes;

public:
    virtual string search(Searchable* searchable) ;
    virtual ~BFS();
    virtual int getNumberOfNodesEvaluated();

};



#endif //EX4_BFS_H
