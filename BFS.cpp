//
// Created by yuvalshechter on 05/02/2020.
//

#include "BFS.h"
#include "BFS.h"
#include "SearchableUtility.h"

/*
 * This function get searchable
 * and return possible way to goalState when the start is in initialState
 */
string BFS::search(Searchable* searchable) {
    queue<State*> q ;
    //create vertex map
    unordered_map<string, State*>* vertex_map = searchable->get_vertex_map() ;
    //create adjacent map
    map<string, vector<State*>> adjacent_map = SearchableUtility::build_adjacent_map(vertex_map , searchable->get_n()) ;
    //create visited map
    map<string, bool> visited_map = SearchableUtility::create_visited_map(vertex_map) ;
    if(searchable->getInitialState() == searchable->getGoalState())
    {
        return "{}";
    }
    //push the start state to the queue
    q.push(searchable->getInitialState()) ;
    SearchableUtility::set_visited_map(searchable->getInitialState()->get_vertex_index(), &visited_map) ;
    State* current_vertex ;
    State* current_adjacent ;
    visited_map[q.front()->get_vertex_index()] = true;
    this->evaluated_nodes++;
    //while the queue is not empty
    while(q.empty() == false) {
        //save the first organ in the queue and delete him from th queue
        current_vertex = q.front() ;
        q.pop() ;
        //get the vector of all the adjacent of the vertex
        vector<State*> temp_adjacent = adjacent_map[current_vertex->get_vertex_index()] ;
        //move on all the adjacent
        for (int i = 0 ; i < temp_adjacent.size() ; i++) {
            current_adjacent = temp_adjacent[i] ;
            //if the state have not visited yet
            if(visited_map[current_adjacent->get_vertex_index()] == false) {
                //set the current vertex to be his father
                current_adjacent->set_father(current_vertex) ;
                //if the adjacent is not the goalState
                if(current_adjacent != searchable->getGoalState()) {
                    //push the current adjacent to the queue and set him as visited
                    q.push(current_adjacent);
                    visited_map[current_adjacent->get_vertex_index()] = true;
                    this->evaluated_nodes++;
                }
                    //if the adjacent is the goalState restore the solution
                else {
                    cout<<this->evaluated_nodes<<"\n"<<endl;
                    return SearchableUtility::restore_solution(searchable) ;
                }
            }
        }
    }
    return "-1\r\n";
}
int BFS:: getNumberOfNodesEvaluated()
{
    return this->evaluated_nodes;
}

BFS::~BFS() {};