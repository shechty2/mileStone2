//
// Created by adam on 29/01/2020.
//

#include "BestFS.h"
#include "HelpfulFunctionsForMatrix.h"
#include <algorithm>
#include <iostream>
#define  ONE 1
/***
 *
 * @param This function get as input searchable
 * @return possible short way from the source vertex to the target vertex.
 */
string BestFS::search(Searchable* searchable) {
    State* targetState = searchable->getGoalState();
    State* sourceState = searchable->getInitialState();
    double costCurrentAdjacent = 0.0;
    double costCurrent = 0.0;
    unordered_map<string, State*>* vertex_map = searchable->getVertexMap();
    map<string, vector<State*>> adjacent_map = HelpfulFunctionsForMatrix::makingNeighborMap(vertex_map, searchable->getN());
    map<string, bool> visited_map = HelpfulFunctionsForMatrix::makingVisitedMap(vertex_map);
    map<string, double> cost_map = build_f_map(vertex_map);
    vector<pair<double ,State*>>::iterator current;
    vector<pair<double ,State*>> vec;
    State* currentAdjacent ;
    State* currentVertex;
    if(searchable->getInitialState() == searchable->getGoalState())
    {
        return "{}";
    }
    vec.push_back(pair<double ,State*>(sourceState->getCost(), sourceState));
    visited_map[searchable->getInitialState()->get_vertex_index()] = true;
    while(!vec.empty())
    {
        current = find_lowest_cost(&vec);
        currentVertex = current->second;
        costCurrent = current->first;
        vec.erase(current);
        this->evaluatedNodes++;
        if((currentVertex->get_vertex_index()) == searchable->getGoalState()->get_vertex_index())
        {
            this->evaluatedNodes++;
            return HelpfulFunctionsForMatrix::createSolutionPath(searchable);
        }
        else
        {
            vector<State*> temp_adjacent = adjacent_map[(currentVertex)->get_vertex_index()] ;
            for (int i = 0 ; i < temp_adjacent.size() ; i++) {
                currentAdjacent = temp_adjacent[i];
                if(!visited_map[currentAdjacent->get_vertex_index()]) {
                    currentAdjacent->set_father(currentVertex);
                    visited_map[currentAdjacent->get_vertex_index()] = true;
                    if(currentAdjacent->get_vertex_index() == searchable->getGoalState()->get_vertex_index())
                    {
                        return HelpfulFunctionsForMatrix::createSolutionPath(searchable);
                    }
                    costCurrentAdjacent = cost_map[currentAdjacent->get_vertex_index()];
                    vec.push_back(pair<double,State*>(costCurrentAdjacent+costCurrent,currentAdjacent ));
                }
            }
        }
    }
    return "-1\r\n";
}
/*
 *This function get vertex map
 * move on the map and create map of cost
 */
map<string, double> BestFS::build_f_map(unordered_map<string, State *> *vertex_map) {
    map<string, double> c_map;
    unordered_map<string, State *>::iterator it;
    //move on the map and set the cost of every vertex in another map
    for (it = vertex_map->begin(); it != vertex_map->end(); ++it) {
        c_map.insert(pair<string, double >(it->first, it->second->getCost()));
    }
    return c_map;
}
/*
 *This function get vector and map of costs
 * move on the vector and find the lowst cost
 */
vector<pair<double ,State*>>::iterator BestFS::find_lowest_cost(vector<pair<double ,State*>> *vec) {
    //it is iterator to the first organ in the vector
    vector<pair<double ,State*>>::iterator it = vec->begin();
    vector<pair<double ,State*>>::iterator min_cost_it;
    //min cost is one more than the first organ in order to get in to the if in the loop
    double min_cost = (*it).first + ONE;
    double temp_cost;
    //move on the organs in the vector
    for (it = vec->begin(); it != vec->end(); it++) {
        temp_cost = (*it).first;
        //if there is organ that have lower cost then the min cost save his value in min_cost
        if (temp_cost < min_cost) {
            min_cost = temp_cost;
            min_cost_it = it;
        }
    }
    return min_cost_it;
}

int BestFS::NumOfNodesEvaluated()
{
    return this->evaluatedNodes;
}
BestFS::~BestFS(){};