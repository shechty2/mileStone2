//
// Created by yuval on 2/2/20.
//

#include "SearchableUtility.h"

/* This function return a vector of all neighbor vertexes of a specifix vertex,
 * by checking the matrix bounds.
 */

vector<State*> SearchableUtility::getAllPossibleStates(State* s, unordered_map<string, State*>* vertex_map, int n) {
    vector<State*> possibleStates;
    int this_i = s->get_i() ;
    int this_j = s->get_j() ;
    if(this_i+1 < n  && (vertex_map->at(create_index(this_i+1, this_j))->get_cost() > -1) ){
        // if the vertex has an adjacent below
        possibleStates.push_back(vertex_map->at(create_index(this_i+1, this_j))) ;
    }
    if(this_i-1 >= 0 && (vertex_map->at(create_index(this_i-1, this_j))->get_cost() > -1)) {
        // if the vertex has an adjacent above
        possibleStates.push_back(vertex_map->at(create_index(this_i-1, this_j))) ;
    }
    if(this_j+1 < n && (vertex_map->at(create_index(this_i, this_j+1))->get_cost() > -1)) {
        // if the vertex has an adjacent in it's right
        possibleStates.push_back(vertex_map->at(create_index(this_i, this_j+1))) ;
    }
    if(this_j-1 >= 0 && (vertex_map->at(create_index(this_i, this_j-1))->get_cost() > -1)) {
        //if the vertex has an adjacent in it's left
        possibleStates.push_back(vertex_map->at(create_index(this_i, this_j-1))) ;
    }
    return possibleStates;
}

/* This function vuild a map which stores all the adjacents of all the vertexes in the graph.
 * The map's key is a vertex's index and the value is a vector of States (vertexes) of all
 * it's adjacents.
 */

map<string, vector<State*>>SearchableUtility::build_adjacent_map(unordered_map<string, State*>* vertex_map, int n) {
    map<string, vector<State*>> adjacent_map ;
    unordered_map<string, State*>::iterator it ;
    // run throw all the vertexes of the graph in the vertex_map using an iterator
    for(it = vertex_map->begin() ; it != vertex_map->end() ; it++) {
        // insert each vertex index to the map and activate the function getAllPossibleStates to
        // get a vector of all it's adjacents
        adjacent_map[it->first] = getAllPossibleStates(it->second, vertex_map, n) ;
    }
    return adjacent_map ;
}

// this function creates a visited map, when the key is the vretex's index and the value
// is a boolean that indicates that.

map<string, bool> SearchableUtility::create_visited_map(unordered_map<string, State*>* vertex_map) {
    unordered_map<string, State*>::iterator it ;
    map<string, bool> visited_map ;
    // run throw all the vertexes of the graph in the vertex_map using an iterator
    for(it = vertex_map->begin() ; it != vertex_map->end() ; it++) {
        // insert each vertex index to the map and initialize the value to false
        visited_map.insert(pair<string, bool>(it->first, false)) ;
    }
    return visited_map ;
}

void SearchableUtility::set_visited_map(string index, map<string, bool>* visited_map) {
    visited_map->at(index) = true ;
}

// this function receive a vertex's index in 2 ints and make them a string

string SearchableUtility::create_index(int i, int j) {
    return to_string(i)+","+to_string(j) ;
}

/* This function get's a searchable and loops throw each vertex's father, to check the
 * final path from the entry to the goal.
 * The function start the loop from the goal vertex.
 */

string SearchableUtility::restore_solution(Searchable *searchable) {
    State *current = searchable->getGoalState();
    vector<string> directions;
    string answer = "{";
    //int total_cost = 0;
    int cost_counter = 0;
    //int fatherInitCost = 0;
    //int cost_counter = searchable->getGoalState()->get_cost();
    // while the current vertex checked is not the entry vertex, continue loop
    while (current != searchable->getInitialState()) {
        // activate check_direction function to check the specific step in the path and push
        // the answer into a vector.
        cost_counter += current->get_father()->get_cost();

        //directions.push_back(check_direction(current) + "(" + to_string(cost_counter) + ")");
        // update the current vertex to be it's father vertex to continue the loop
        current = current->get_father();

    }
    cost_counter = cost_counter + searchable->getGoalState()->get_cost();
    //cost_counter += fatherInitCost;
    current = searchable->getGoalState();
    while (current != searchable->getInitialState()) {
        // activate check_direction function to check the specific step in the path and push
        // the answer into a vector.


        directions.push_back(check_direction(current) + "(" + to_string(cost_counter) + ")");
        cost_counter -= current->get_cost();
        // update the current vertex to be it's father vertex to continue the loop
        current = current->get_father();
    }

    // join all the directions into a string
    for (int i = directions.size() - 1; i >= 0; i--) {
        answer += directions.at(i) + ", ";
    }

    answer.erase(answer.length() - 2, 2);
    answer += "}\r\n";

    return answer;

}

// This function checks the direction from a vertex to it's father.

string SearchableUtility::check_direction(State *current) {
    int current_i = current->get_i();
    int current_j = current->get_j();
    int father_i = current->get_father()->get_i();
    int father_j = current->get_father()->get_j();

    // if the current vertex and it's father in the same column
    if (current_j == father_j) {
        if (current_i > father_i) {
            return "DOWN";
        } else {
            return "UP";
        }
    }

        // if the current vertex and it's father in the same line
    else if (current_i == father_i) {
        if (current_j > father_j) {
            return "RIGHT";
        } else {
            return "LEFT";
        }
    }
}