//
// Created by adam on 29/01/2020.
//

#include "BestFS.h"
#include "SearchableUtility.h"
#include <algorithm>
#define  ONE 1
/*
 *This function get a searchable add return the shortest way
 * from the initialState to the goalState
 */
string BestFS::search(Searchable* searchable) {
    State* initialState = searchable->getInitialState();
    State* goalState = searchable->getGoalState();
    double cost_current = 0.0;
    double cost_current_adjacent = 0.0;
    //create vertex map
    unordered_map<string, State*>* vertex_map = searchable->get_vertex_map();
    //create adjacent map
    map<string, vector<State*>> adjacent_map = SearchableUtility::build_adjacent_map(vertex_map , searchable->get_n());
    //create visited map
    map<string, bool> visited_map = SearchableUtility::create_visited_map(vertex_map);
    //create cost map
    map<string, double> cost_map = build_f_map(vertex_map);
    vector<pair<double ,State*>> vec;
    vector<pair<double ,State*>>::iterator current;
    State* current_adjacent ;
    State* current_vertex;
    //push the initial state to the vector
    if(searchable->getInitialState() == searchable->getGoalState())
    {
        return "{}";
    }
    vec.push_back(pair<double ,State*>(initialState->get_cost(),initialState));
    visited_map[searchable->getInitialState()->get_vertex_index()] = true;
    while(!vec.empty())
    {
        //find the state with the lowest cost
        current = find_lowest_cost(&vec);
        current_vertex = current->second;
        cost_current = current->first;
        //erase the this state from the vector
        vec.erase(current);
        this->evaluated_nodes++;
        //if the state is the goal restore the solution
        if((current_vertex->get_vertex_index()) == searchable->getGoalState()->get_vertex_index())
        {
            this->evaluated_nodes++;
            return SearchableUtility::restore_solution(searchable);
        }
        else
        {
            //move on all the adjacent of the state
            vector<State*> temp_adjacent = adjacent_map[(current_vertex)->get_vertex_index()] ;
            for (int i = 0 ; i < temp_adjacent.size() ; i++) {
                current_adjacent = temp_adjacent[i];
                //if the state have not visited yet
                if(!visited_map[current_adjacent->get_vertex_index()]) {
                    //set the state father
                    current_adjacent->set_father(current_vertex);
                    //mark him as visited
                    visited_map[current_adjacent->get_vertex_index()] = true;
                    //check if he is the state gol
                    if(current_adjacent->get_vertex_index() == searchable->getGoalState()->get_vertex_index())
                    {
                        return SearchableUtility::restore_solution(searchable);
                    }
                    cost_current_adjacent = cost_map[current_adjacent->get_vertex_index()];
                    //push the state to vector
                    vec.push_back(pair<double,State*>(cost_current_adjacent+cost_current,current_adjacent ));
                }
            }
        }
    }
    return "-1\r\n";
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

/*
 *This function get vertex map
 * move on the map and create map of cost
 */
map<string, double> BestFS::build_f_map(unordered_map<string, State *> *vertex_map) {
    map<string, double> c_map;
    unordered_map<string, State *>::iterator it;
    //move on the map and set the cost of every vertex in another map
    for (it = vertex_map->begin(); it != vertex_map->end(); ++it) {
        c_map.insert(pair<string, double >(it->first, it->second->get_cost()));
    }
    return c_map;
}

int BestFS::getNumberOfNodesEvaluated()
{
    return this->evaluated_nodes;
}
BestFS::~BestFS(){};