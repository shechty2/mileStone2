//
// Created by adam on 30/01/2020.
//

#ifndef EX4_OA_H
#define EX4_OA_H

#include "Solver.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class OA: public Solver<vector<string>, string> {
private:

  string solve(vector<string> problem);
};

#endif // EX4_OA_H
