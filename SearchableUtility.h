//
// Created by yuvalshechter on 02/02/2020.
//

#ifndef EX4_SEARCHABLEUTILITY_H
#define EX4_SEARCHABLEUTILITY_H


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

class SearchableUtility {
private:
    static string check_direction(State* current);
public:
    static vector<State*> getAllPossibleStates(State* s, unordered_map<string, State*>* vertex_map, int n) ;
    static map<string, vector<State*>>build_adjacent_map(unordered_map<string, State*>* vertex_map, int n) ;
    static map<string, bool> create_visited_map(unordered_map<string, State*>* vertex_map) ;
    static void set_visited_map(string index, map<string, bool>* visited_map) ;
    static string create_index(int i, int j) ;
    static string restore_solution(Searchable* searchable);


};


#endif //FINAL_PROJECT_SECOND_SEARCHABLEUTILITY_H