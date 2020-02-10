//
// Created by yuvalshechter on 05/02/2020.
//


#include "AStar.h"
/***
 *
 * @param This function get as input searchable
 * @return possible way from the source vertex (sourceVertex) to the target vertex (targetVertex).
 */
string AStar::search(Searchable *searchable) {
    State *targetVertex = searchable->getGoalState();
    State *sourceVertex = searchable->getInitialState();
    State *tempAdjacent;
    State *currentVertex;
    if (sourceVertex->get_vertex_index() == targetVertex->get_vertex_index()) {
        return "{}\r\n";
    }
    unordered_map<string, State *> *vertex_map = searchable->getVertexMap(); // get matrix map
    map<string, double> f_map = build_f_map(vertex_map); // build f value map
    map<string, double> g_map = build_g_map(vertex_map); // build g value map
    map<string, vector<State *>> adjacent_map = HelpfulFunctionsForMatrix::makingNeighborMap(vertex_map, searchable->getN());
    map<string, double> h_map = build_h_map(vertex_map, targetVertex); // build h value map
    vector<State *> close_vec;
    vector<State *> open_vec;
    vector<State *> currentAdjacent;
    open_vec.push_back(sourceVertex);
    f_map[sourceVertex->get_vertex_index()] = h_map[sourceVertex->get_vertex_index()] ;
    g_map[sourceVertex->get_vertex_index()] = 0;
    this->evaluatedNodes = 1 ;
    vector<State *>::iterator begin_it;
    vector<State *>::iterator low_cost_it;
    string adjIndex;
    double adjGValue;
    double adjDistanceValue;

    while (open_vec.empty() == false) {
        low_cost_it = find_lowest_cost(&open_vec, &f_map);
        currentVertex = *low_cost_it;
        open_vec.erase(low_cost_it);
        close_vec.push_back(currentVertex);

        currentAdjacent = adjacent_map.at(currentVertex->get_vertex_index());
        for (int i = 0; i < currentAdjacent.size(); i++) {
            begin_it = open_vec.begin();
            tempAdjacent = currentAdjacent[i];
            if(tempAdjacent == targetVertex) {
                tempAdjacent->set_father(currentVertex) ;
                return HelpfulFunctionsForMatrix::createSolutionPath(searchable) ;
            }
            adjIndex = tempAdjacent->get_vertex_index();
            adjDistanceValue = tempAdjacent->getCost() + g_map[currentVertex->get_vertex_index()] ;
            adjGValue = g_map[adjIndex];
            if (find_in_vec(&close_vec, tempAdjacent) < 0) {
                // if the adjacent is in the open_vec and it's distance value from entry throw the current vertex is
                // less than it's g value, erase it from open_vec
                if ((find_in_vec(&open_vec, tempAdjacent) > -1) && (adjDistanceValue < adjGValue)) {
                    open_vec.erase(begin_it + find_in_vec(&open_vec, tempAdjacent));
                }
                    // if the adjacent is in the close_vec and it's distance value from entry throw the current vertex is
                    // less than it's g value, erase it from close_vec
                else if ((find_in_vec(&close_vec, tempAdjacent) > -1) && (adjDistanceValue < adjGValue)) {
                    close_vec.erase(begin_it + find_in_vec(&close_vec, tempAdjacent));
                }
                    // if the adjacent is not in the open_vec and not in the close_vec, update it's data
                else if ((find_in_vec(&open_vec, tempAdjacent) < 0) && (find_in_vec(&close_vec, tempAdjacent) < 0)) {
                    tempAdjacent->set_father(currentVertex); // set current vertex to be it's father
                    open_vec.push_back(tempAdjacent); // push it into open_vec
                    g_map[adjIndex] = adjDistanceValue; // update it's g value
                    f_map[adjIndex] = adjDistanceValue + h_map[adjIndex] ; // update it's f value
                    this->evaluatedNodes++ ;
                }
            }
        }
    }
    cout << endl << "expandedNodesNum: " << this->evaluatedNodes;
    return "-1\r\n" ;
}

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
// Initialize the h_map value for all each vertex in the matrix to be it's cost
map<string, double> AStar::build_h_map(unordered_map<string, State *> *vertex_map, State* goal) {
    map<string, double> h_map ;
    State* goal_state = goal ;
    unordered_map<string, State *>::iterator it;
    for (it = vertex_map->begin(); it != vertex_map->end(); ++it) {
        h_map.insert(pair<string, double>(it->first, it->second->h(goal_state)));
    }
    return h_map ;
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

int AStar::NumOfNodesEvaluated() {
    return this->evaluatedNodes ;
}

AStar:: ~AStar(){};