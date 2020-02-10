//
// Created by yuval on 2/2/20.
//

#include "HelpfulFunctionsForMatrix.h"

vector<State*> HelpfulFunctionsForMatrix::getAllPossibleStates(State* state, unordered_map<string, State*>* vertex_map, int limit) {
    int cur_j = state->getJ();
    int cur_i = state->getI();
    vector<State*> legalStates;

    if(cur_i + 1 < limit && (vertex_map->at(makeIndex(cur_i + 1, cur_j))->getCost() > -1) ){
        legalStates.push_back(vertex_map->at(makeIndex(cur_i + 1, cur_j))) ;
    }
    if(cur_i - 1 >= 0 && (vertex_map->at(makeIndex(cur_i - 1, cur_j))->getCost() > -1)) {
        legalStates.push_back(vertex_map->at(makeIndex(cur_i - 1, cur_j))) ;
    }
    if(cur_j + 1 < limit && (vertex_map->at(makeIndex(cur_i, cur_j + 1))->getCost() > -1)) {
        legalStates.push_back(vertex_map->at(makeIndex(cur_i, cur_j + 1))) ;
    }
    if(cur_j - 1 >= 0 && (vertex_map->at(makeIndex(cur_i, cur_j - 1))->getCost() > -1)) {
        legalStates.push_back(vertex_map->at(makeIndex(cur_i, cur_j - 1))) ;
    }
    return legalStates;
}


map<string, vector<State*>>HelpfulFunctionsForMatrix::makingNeighborMap(unordered_map<string, State*>* vertex_map, int n) {
    map<string, vector<State*>> neighbors_map ;
    for(unordered_map<string, State*>::iterator it = vertex_map->begin() ; it != vertex_map->end() ; ++it) {
        neighbors_map[it->first] = getAllPossibleStates(it->second, vertex_map, n) ;
    }
    return neighbors_map ;
}

map<string, bool> HelpfulFunctionsForMatrix::makingVisitedMap(unordered_map<string, State*>* vertex_map) {
    map<string, bool> visitedMap;
    for(unordered_map<string, State*>::iterator it = vertex_map->begin() ; it != vertex_map->end() ; it++) {
        visitedMap.insert(pair<string, bool>(it->first, false)) ;
    }
    return visitedMap ;
}

void HelpfulFunctionsForMatrix::setVisitedMap(string index, map<string, bool>* visited_map) {
    visited_map->at(index) = true ;
}


string HelpfulFunctionsForMatrix::makeIndex(int i, int j) {
    string index = to_string(i)+","+to_string(j);
    return index;
}

string HelpfulFunctionsForMatrix::createSolutionPath(Searchable *searchable) {
    State *current = searchable->getGoalState();
    vector<string> directions;
    string ans = "{";
    int cost_counter = 0;
    //int fatherInitCost = 0;
    //int cost_counter = searchable->getGoalState()->getCost();
    while (current != searchable->getInitialState()) {
        cost_counter += current->get_father()->getCost();
        current = current->get_father();
    }
    cost_counter = cost_counter + searchable->getGoalState()->getCost();
    current = searchable->getGoalState();
    while (current != searchable->getInitialState()) {
        directions.push_back(check_direction(current) + "(" + to_string(cost_counter) + ")");
        cost_counter -= current->getCost();
        current = current->get_father();
    }
    for (int i = directions.size() - 1; i >= 0; i--) {
        ans += directions.at(i) + ", ";
    }
    ans.erase(ans.length() - 2, 2);
    ans += "}\r\n";
    return ans;
}

string HelpfulFunctionsForMatrix::check_direction(State *current) {
    int current_i = current->getI();
    int current_j = current->getJ();
    int father_i = current->get_father()->getI();
    int father_j = current->get_father()->getJ();
    if (current_j == father_j) {
        if (current_i > father_i) {
            return "DOWN";
        } else {
            return "UP";
        }
    }
    else if (current_i == father_i) {
        if (current_j > father_j) {
            return "RIGHT";
        } else {
            return "LEFT";
        }
    }
}