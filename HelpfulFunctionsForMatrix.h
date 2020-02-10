//
// Created by yuvalshechter on 02/02/2020.
//

#ifndef EX4_HELPFULFUNCTIONSFORMATRIX_H
#define EX4_HELPFULFUNCTIONSFORMATRIX_H


#include <unordered_map>
#include <vector>
#include <map>
#include <string>
#include "State.h"
#include "Searchable.h"

using namespace std ;

/* This is a static class which implements some useful functions for all
 * the searchables objects, this way we avoid double code duplication
 */

class HelpfulFunctionsForMatrix {
private:
    static string check_direction(State* current);
public:
    static map<string, vector<State*>>makingNeighborMap(unordered_map<string, State*>* vertex_map, int n);
    static map<string, bool> makingVisitedMap(unordered_map<string, State*>* vertex_map);
    static vector<State*> getAllPossibleStates(State* state, unordered_map<string, State*>* vertex_map, int limit);
    static string createSolutionPath(Searchable* searchable);
    static void setVisitedMap(string index, map<string, bool>* visited_map);
    static string makeIndex(int i, int j);
};


#endif //FINAL_PROJECT_SECOND_SEARCHABLEUTILITY_H