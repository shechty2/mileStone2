
#include "Matrix.h"

/***
 *
 * @param matrix_vec is a vector that holds ths input of the matrix.
 */
Matrix::Matrix(vector<string> matrix_vec) {
    if (build_matrix(matrix_vec) == false) {
        n = -1;
    }
}


// this function bulds for each index a vertex in the vertexMap
bool Matrix::mapBuilder(vector<string> line_vec, int i) {
    int j;
    int vec_length = line_vec.size();
    if(vec_length == n) {
        State *temp_state;
        string vertex_index;
        for (j = 0; j < vec_length; ++j) {
            vertex_index = to_string(i) + "," + to_string(j);
            temp_state = new State(vertex_index, stod(line_vec.at(j)));
            vertexMap.insert(pair<string, State *>(vertex_index, temp_state));
        }
        return true;
    } else {
        return false;
    }
}

//the builder of the matrix, uses a friend functions
bool Matrix::build_matrix(vector<string> matrix_vec) {
    int i;
    int sizeOfVector = matrix_vec.size() - 2;
    vector<string> line;
    this->n = sizeOfVector;
    for (i = 0; i < sizeOfVector; i++) {
        line = buildLine(matrix_vec.at(i));
        if (mapBuilder(line, i) == false) {
            return false;
        }
    }
    line = buildLine(matrix_vec.at(sizeOfVector));
    initialVertex = vertexMap[line.at(0) + "," + line.at(1)];
    line = buildLine(matrix_vec.at(++sizeOfVector));
    goalVertex = vertexMap[line.at(0) + "," + line.at(1)];
    return true;
}

//this function gets a line and puts it into a vector of strings
vector<string> Matrix::buildLine(string line) {
    int endNum = 0;
    int start = 0;
    vector<string> line_vec;
    if (line[line.length() - 1] != ',') {
        line = line + ",";
    }
    while (true) {
        endNum = line.find(',', start);
        if (endNum != -1) {
            line_vec.push_back(line.substr(start, endNum-start));
            start = endNum + 1;
        } else {
            return line_vec;
        }
    }
}

int Matrix::getN() {
    return n;
}

unordered_map<string, State*>* Matrix::getVertexMap() {
    return &this->vertexMap;
}

State *Matrix::getInitialState() {
    return this->initialVertex;
}

State *Matrix::getGoalState() {
    return this->goalVertex;
}