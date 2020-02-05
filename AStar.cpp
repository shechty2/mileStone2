//
// Created by yuvalshechter on 05/02/2020.
//

#include <limits>
#include "AStar.h"
#include "SearchableUtility.h"

string AStar::search(Searchable *searchable) {
    State *current_vertex;
    State *temp_adj;
    State *goal_vertex = searchable->getGoalState();
    State *start_vertex = searchable->getInitialState();

    if (goal_vertex->get_vertex_index() == start_vertex->get_vertex_index()) {
        return "{}\r\n" ;
    }

    unordered_map<string, State *> *vertex_map = searchable->get_vertex_map(); // get matrix map
    map<string, double> g_map = build_g_map(vertex_map); // build g value map
    map<string, double> f_map = build_f_map(vertex_map); // build f value map

    // build adjacents map
    map<string, vector<State *>> adjacent_map = SearchableUtility::build_adjacent_map(vertex_map, searchable->get_n());

    map<string, double> h_map = build_h_map(vertex_map, goal_vertex); // build h value map

    vector<State *> open_vec; // vector for unexplored vertexes
    vector<State *> close_vec; // vector for explored vertexes
    vector<State *> current_adjacents;
    open_vec.push_back(start_vertex);

    // initialize entry vertex

    g_map[start_vertex->get_vertex_index()] = 0;
    f_map[start_vertex->get_vertex_index()] = h_map[start_vertex->get_vertex_index()] ;
    this->evaluated_nodes = 1 ;

    vector<State *>::iterator low_cost_it;
    vector<State *>::iterator begin_it;

    string adj_index;
    double adj_distance_value;
    double adj_g_value;

    while (open_vec.empty() == false) {
        // find the lowest f value in the open_vec.
        // this line is equal to get the front value from a priority queue
        low_cost_it = find_lowest_cost(&open_vec, &f_map);
        current_vertex = *low_cost_it; // set the current_vertex
        open_vec.erase(low_cost_it); // erase it from open_vec
        close_vec.push_back(current_vertex); // push it into close_vec
        // get the adjacents vector of the current vector
        current_adjacents = adjacent_map.at(current_vertex->get_vertex_index());
        for (int i = 0; i < current_adjacents.size(); i++) { // run throw all the current's adjacents
            begin_it = open_vec.begin();
            temp_adj = current_adjacents[i];
            if(temp_adj == goal_vertex) { // if a certain adjacent is the goal vertex
                temp_adj->set_father(current_vertex) ;
                // activate function to restore the solution and return the shortest path
                cout << endl << "evaluated_nodes: " << this->evaluated_nodes << endl;
                return SearchableUtility::restore_solution(searchable) ;
            }
            adj_index = temp_adj->get_vertex_index();
            adj_distance_value = temp_adj->get_cost() + g_map[current_vertex->get_vertex_index()] ;
            adj_g_value = g_map[adj_index];
            if (find_in_vec(&close_vec, temp_adj) < 0) { // if adjacent is not in the close_vec

                // if the adjacent is in the open_vec and it's distance value from entry throw the current vertex is
                // less than it's g value, erase it from open_vec

                if ((find_in_vec(&open_vec, temp_adj) > -1) && (adj_distance_value < adj_g_value)) {
                    open_vec.erase(begin_it + find_in_vec(&open_vec, temp_adj));
                }

                    // if the adjacent is in the close_vec and it's distance value from entry throw the current vertex is
                    // less than it's g value, erase it from close_vec

                else if ((find_in_vec(&close_vec, temp_adj) > -1) && (adj_distance_value < adj_g_value)) {
                    close_vec.erase(begin_it + find_in_vec(&close_vec, temp_adj));

                }

                    // if the adjacent is not in the open_vec and not in the close_vec, update it's data

                else if ((find_in_vec(&open_vec, temp_adj) < 0) && (find_in_vec(&close_vec, temp_adj) < 0)) {
                    temp_adj->set_father(current_vertex); // set current vertex to be it's father
                    open_vec.push_back(temp_adj); // push it into open_vec
                    g_map[adj_index] = adj_distance_value; // update it's g value
                    f_map[adj_index] = adj_distance_value + h_map[adj_index] ; // update it's f value
                    this->evaluated_nodes++ ;
                }
            }
        }
    }
    cout << endl << "evaluated_nodes: " << this->evaluated_nodes;
    return "-1\r\n" ;
}

// Initialize the g_map value for all each vertex in the matrix to be 0

map<string, double> AStar::build_g_map(unordered_map<string, State *> *vertex_map) {
    map<string, double> g_map;
    unordered_map<string, State *>::iterator it;
    for (it = vertex_map->begin(); it != vertex_map->end(); ++it) {
        g_map.insert(pair<string, double>(it->first, 0));
    }
    return g_map;
}

// Initialize the h_map value for all each vertex in the matrix to be it's cost

map<string, double> AStar::build_h_map(unordered_map<string, State *> *vertex_map, State* goal) {
    map<string, double> h_map ;
    State* goal_state = goal ;
    unordered_map<string, State *>::iterator it;
    for (it = vertex_map->begin(); it != vertex_map->end(); ++it) {
        h_map.insert(pair<string, double>(it->first, it->second->calc_heuristic(goal_state)));
    }
    return h_map ;
}

// Initialize the f_map value for all each vertex in the matrix to be max int number

map<string, double> AStar::build_f_map(unordered_map<string, State *> *vertex_map) {
    double init_cost = numeric_limits<double>::max();
    map<string, double> f_map;
    unordered_map<string, State *>::iterator it;
    for (it = vertex_map->begin(); it != vertex_map->end(); ++it) {
        f_map.insert(pair<string, double>(it->first, init_cost));
    }
    return f_map;
}

/* This function receives a vector of states and a state, and checks if the state
 * is in the vector.
 * If it inside the vector, return it's index.
 * If not, return -1
 */

int AStar::find_in_vec(vector<State *> *vec, State *current) {
    string current_index = current->get_vertex_index();
    string temp_index;
    for (int i = 0; i < vec->size(); i++) { // run throw vector
        temp_index = (*vec)[i]->get_vertex_index();
        if (current_index == temp_index) { // for each state, check if it equal to the current state
            return i;
        }
    }
    return -1;
}

/* this function receives a vector and a map and return an iterator
 * to it's location in the vector.
 */

vector<State *>::iterator AStar::find_lowest_cost(vector<State *> *vec, map<string, double> *cost_to_vertex_map) {
    double min_cost = numeric_limits<double>::max(); // initialize max double number
    vector<State *>::iterator it; // iterator to run throw vector
    vector<State *>::iterator min_cost_it; // iterator to keep the lowest cost location
    double temp_cost;
    for (it = vec->begin(); it != vec->end(); it++) { // run throw vector
        temp_cost = (*cost_to_vertex_map)[(*it)->get_vertex_index()];
        if (temp_cost < min_cost) { // if the current state cost is lower than the minimum cost state
            min_cost = temp_cost;   // make it to be the minimum cost state
            min_cost_it = it;       // keep an iterator to it.
        }
    }
    return min_cost_it;
}

int AStar::getNumberOfNodesEvaluated() {
    return this->evaluated_nodes ;
}

AStar:: ~AStar(){};