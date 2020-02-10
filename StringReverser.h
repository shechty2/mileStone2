//
// Created by yuvalshechter on 21/01/2020.
//

#ifndef EX4_STRINGREVERSER_H
#define EX4_STRINGREVERSER_H

#include "Solver.h"
#include <string>
#include <vector>

using namespace std;
 /***
  * This class getting string from the client ("problem") and need to return the reversed string ("solution").
  */
class StringReverser : public Solver<string,string> {
public:
    string solve(string problem);
    vector<string> parseLine(string buffer);
};


#endif //EX4_STRINGREVERSER_H
