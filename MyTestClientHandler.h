//
// Created by yuvalshechter on 19/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "CacheManager.h"
#include "StringReverser.h"
#include "Solver.h"
#include <string>

using namespace std;

class MyTestClientHandler: public ClientHandler{
    Solver<string, string>* solver;
    CacheManager<string ,string>* cm;
public:
    MyTestClientHandler(CacheManager<string,string>* cm1, Solver<string,string>*solver1);
    virtual ~MyTestClientHandler();
    void handleClient(int clientSocket);

};


#endif //EX4_MYTESTCLIENTHANDLER_H
