//
// Created by yuvalshechter on 29/01/2020.
//

#include "State.h"

State::State(string indexes1, double cost1){
  this->cost = cost1;
  this->fatherVertex = NULL;
  this->indexes = indexes1;
  this->i = int(indexes1[0]) - 48;
  this->j = int(indexes1[2]) - 48;
}
State * State::get_father() {
  return this->fatherVertex;
}

double State::getCostVertex() {
  return this->cost;
}

void State::set_father(State *fatherVertex1) {
  this->fatherVertex = fatherVertex1;
}

void State::setCost(double cost) {
  this->cost = cost;
}

//this is function the hold the indexes of the vertex in the vertexMap
void State::setIndex(string indexes) {
  this->indexes = indexes;
}


int State::getCost() {
    return this->cost;
}

string State::get_vertex_index() {
    return this->indexes;
}

int State::getI() {
    string index = this->get_vertex_index() ;
    return stoi(index.substr(0, index.find(',', 0))) ;
}

double State::h(State* goal) {
    return sqrt(pow((double)(this->getI() - goal->getI()), 2) + pow((double)(this->getJ() - goal->getJ()), 2)) ;
}

int State::getJ() {
    string index_vertex = this->get_vertex_index() ;
    int commaPlace = index_vertex.find(',', 0) ;
    return stoi(index_vertex.substr(commaPlace + 1, index_vertex.length() - commaPlace - 1)) ;
}

State::~State(){
    delete fatherVertex;
}
