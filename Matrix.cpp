//
// Created by yuvalshechter on 29/01/2020.
//

#include <iostream>
#include "Matrix.h"
using namespace std;

Matrix::Matrix(string buffer){

};

State* Matrix::getInitialState() {
    return this->initialState;
}

State* Matrix::getGoalState() {
    return this->goalState;
}

vector<string> Matrix::parsedLine(string buffer) {
    vector<string> vec;
    string delimiter = ",";
    size_t pos = 0;
    string vertexCost;
    while ((pos = buffer.find(delimiter)) != std::string::npos) {
        vertexCost = buffer.substr(0, pos);
        vec.push_back(vertexCost);
        //cout << vertexCost << std::endl;
        buffer.erase(0, pos + delimiter.length());
    }
    vec.push_back(buffer);
    //cout << buffer << std::endl;
    return vec;
}

bool Matrix::isGoalState(State st) {
    return true;
}




