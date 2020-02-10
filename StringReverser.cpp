//
// Created by yuvalshechter on 21/01/2020.
//

#include "StringReverser.h"
#include <vector>
//
string StringReverser::solve(string problem) {
    //len is the size of the input string
    int len = problem.length();
    //creat a new string name as solution to be the reversed problem string
    string solution = "";
    for(int i = len-1; i>=0; i--){
        solution += problem.at(i);
    }
    return solution;
}