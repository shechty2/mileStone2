//
// Created by yuvalshechter on 04/02/2020.
//

#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H


#include "ClientHandler.h"
#include "CacheManager.h"
#include "StringReverser.h"
#include "Solver.h"
#include <string>

using namespace std;

class MyClientHandler: public ClientHandler{
    Solver<vector<string>, string>* solver;
    CacheManager<string ,string>* cm;
public:
    MyClientHandler(Solver<vector<string>, string>*solver1);
    void handleClient(int clientSocket);
    int connectAndSend(string message, int socket);
    bool isEnd(string buffer);

        virtual ~MyClientHandler();

};


#endif //EX4_MYCLIENTHANDLER_H
