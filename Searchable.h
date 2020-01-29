//
// Created by yuvalshechter on 28/01/2020.
//

#ifndef EX4_SEARCHEABLE_H
#define EX4_SEARCHEABLE_H


#include "State.h"
#include <unordered_map>

using namespace std;

//searchable is when looking at all the matrix

class Searchable{
public:
    virtual State* getGoalState() = 0;
    virtual State* getInitionalState() = 0;
    virtual bool isGoalState(State st) = 0;
    virtual unordered_map<string, State*> *get_vertex_map(State st) = 0;

};

#endif //EX4_SEARCHEABLE_H
