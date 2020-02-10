//
// Created by yuvalshechter on 28/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H

#include <string>
#include "math.h"
using  namespace std;
class State{
private:
    State *fatherVertex;
    double cost;
    string indexes;
    int i;
    int j;

public:
    State(string indexes1, double cost1);
    ~State();
    double h(State *goal);
    State *get_father();
    string get_vertex_index();
    double getCostVertex();
    void set_father(State *fatherVertex);
    void setcurrentState(string currentState);
    void setCost(double cost);
    void setIndex(string indexes);
    int getI();
    int getJ();
    int getCost();
};

#endif //EX4_STATE_H
