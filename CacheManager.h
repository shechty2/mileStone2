//
// Created by yuvalshechter on 20/01/2020.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

#include <unordered_map>
using  namespace std;

/**
 * This class is a interface.
 * @tparam p is a string name "problem" and we need to keep it in
 * map when ever we will see the same string so we already have the solution and used it.
 * @tparam s is a string name "solution". s is the reversed string of p string.
 */
template <class P,class S>
class CacheManager {
    //unordered_map <p,s> cache;
public:
    //CacheManager();
    virtual bool isSolutionExist (P problem) = 0;
    virtual string getSolution (P problem) = 0;
    virtual void saveSolution (P problem, S solution) = 0;
};


#endif //EX4_CACHEMANAGER_H
