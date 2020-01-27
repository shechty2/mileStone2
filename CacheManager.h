//
// Created by yuvalshechter on 20/01/2020.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

#include <unordered_map>
using  namespace std;
template <class p, class s>

/**
 * This class is a interface.
 * @tparam p is a string name "problem" and we need to keep it in
 * map when ever we will see the same string so we already have the solution and used it.
 * @tparam s is a string name "solution". s is the reversed string of p string.
 */

class CacheManager {
    unordered_map <p,s> cache;
public:
    virtual bool isSolutionExist (p input) = 0;
    virtual string getSolution (p input) = 0;
    virtual void saveSolution (p input, s output) = 0;
};


#endif //EX4_CACHEMANAGER_H
