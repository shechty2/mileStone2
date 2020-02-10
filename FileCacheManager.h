//
// Created by yuvalshechter on 20/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

#include "CacheManager.h"
//#include "filesystem"
#include <fstream>
template <class P, class S>
class FileCacheManager: public CacheManager<P,S> {
public:
  virtual bool isSolutionExist (P problem) {
    hash<string> h;
    int hash_name = h(problem);
    ifstream problemFile(to_string(hash_name));
    return problemFile.good();
  };

  virtual string getSolution (P problem) {
    hash<string> h;
    int hash_name = h(problem);
    ifstream readFile(to_string(hash_name));
    string solution((istreambuf_iterator<char>(readFile)),
                    (istreambuf_iterator<char>()));
    return solution;
  };

  virtual void saveSolution (P problem, S solution) {
    hash<string> h;
    int hash_name = h(problem);
    ofstream solutionFile(to_string(hash_name));
    //outFile.open(to_string(hash_name));
    if (solutionFile.is_open()) {
      solutionFile << solution;
      solutionFile.close();
    } else {throw "error in opening file";}
  };
};


#endif //EX4_FILECACHEMANAGER_H
