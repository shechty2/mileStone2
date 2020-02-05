//
// Created by yuvalshechter on 05/02/2020.
//

#include <stack>
#include "DFS.h"
#include "SearchableUtility.h"

string DFS::search(Searchable* searchable) {
    stack<State*> s;
    State* current;
    State* current_adjacent;
    //create vertex map
    unordered_map<string, State *> *vertex_map = searchable->get_vertex_map();
    //create adjacent map
    map<string, vector<State *>> adjacent_map = SearchableUtility::build_adjacent_map(vertex_map, searchable->get_n());
    //create visited map
    map<string, bool> visited_map = SearchableUtility::create_visited_map(vertex_map);
    if(searchable->getGoalState() == searchable->getInitialState())
    {
        return "{}";
    }
    s.push(searchable->getInitialState());
    while(!s.empty())
    {
        current = s.top();
        s.pop();
        if(!visited_map[current->get_vertex_index()])
        {
            visited_map[current->get_vertex_index()] = true;
            this->evaluated_nodes++;
        }
        vector<State*> temp_adjacent = adjacent_map[current->get_vertex_index()] ;
        for (int i = 0; i < temp_adjacent.size() ; i++)
        {
            current_adjacent = temp_adjacent[i];
            //if the state have not visited yet
            if (visited_map[current_adjacent->get_vertex_index()] == false)
            {
                //set the current vertex to be his father
                current_adjacent->set_father(current);
                if (current_adjacent != searchable->getGoalState()) {
                    s.push(current_adjacent);
                } else
                {
                    return SearchableUtility::restore_solution(searchable);
                }
            }
        }
    }
    return "-1";
}
int DFS:: getNumberOfNodesEvaluated()
{
    return this->evaluated_nodes;
}

DFS::~DFS(){};
