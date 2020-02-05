//
// Created by yuvalshechter on 05/02/2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H


#include "Searcher.h"
#include "Searchable.h"
#include "map"
#include "vector"
#include <iostream>
using namespace std;
// this class is an implementation for the A* algorithm

class AStar: public Searcher {

    int evaluated_nodes ;

public:
    virtual string search(Searchable* searchable) ;
    virtual int getNumberOfNodesEvaluated() ;
    virtual ~AStar();

private:
    map<string, double> build_g_map(unordered_map<string, State*>* vertex_map) ;
    map<string, double> build_h_map(unordered_map<string, State *> *vertex_map, State* goal) ;
    map<string, double> build_f_map(unordered_map<string, State*>* vertex_map) ;
    int find_in_vec(vector<State*>* vec, State* current) ;
    vector<State*>::iterator find_lowest_cost(vector<State*>* vec, map<string,double>* cost_to_vertex_map) ;

};


#endif //EX4_ASTAR_H
