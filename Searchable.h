//
// Created by adam on 28/01/2020.
//

#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H
#include "State.h"
#include "string.h"
#include <unordered_map>
using namespace std;
class Searchable {

public:
  virtual State* getGoalState() = 0;
  virtual State* getInitialState() = 0;
  virtual unordered_map <string, State*>* getVertexMap() = 0;
  virtual int getN() = 0;
};
#endif // EX4_SEARCHABLE_H
