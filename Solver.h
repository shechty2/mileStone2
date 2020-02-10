//
// Created by yuvalshechter on 20/01/2020.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

template <class P, class S>

class Solver {
public:
    virtual S solve(P problem)=0;

};


#endif //EX4_SOLVER_H
