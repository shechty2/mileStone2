//
// Created by yuvalshechter on 29/01/2020.
//

#ifndef EX4_MATRIX_H
#define EX4_MATRIX_H


#include "Searchable.h"
#include <unordered_map>
#include <vector>
using namespace std;

/**
 * This is a class of Matrix.
 */
class Matrix : public Searchable{
private:
    unordered_map<string, State*> vertexMap;
    State *initialVertex;
    int n;
    State *goalVertex;
public:
    Matrix(vector<string> matrix_vec);
    virtual State* getGoalState() ;
    virtual unordered_map<string, State*>*getVertexMap();
    int getN();
    virtual State* getInitialState();
    bool mapBuilder(vector<string> line_vec, int i);
    vector<string> buildLine(string line);
    bool build_matrix(vector<string> matrix_vec);
    ~Matrix(){
        unordered_map<string, State *>::iterator it;
        for (it = this->vertexMap.begin(); it != this->vertexMap.end(); ++it) {
            delete this->vertexMap[it->first];
        }
    };
};


#endif //EX4_MATRIX_H