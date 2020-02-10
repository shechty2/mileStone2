//
// Created by yuvalshechter on 06/02/2020.
//

#ifndef EX4_MYPARALLELSERVER_H
#define EX4_MYPARALLELSERVER_H


#include <thread>
#include "Server.h"
#include "vector"
#include "MyClientHandler.h"

using namespace std;
class MyParallelServer: public server_side::Server{
private:
    vector<std::thread> threadsVec;

public:
    static void OAFunction(ClientHandler* ch, int socket);
    MyParallelServer() {};
    virtual ~MyParallelServer() {
        int i;
        for (i = 0; i < threadsVec.size(); ++i) {
            threadsVec.at(i).detach();
        }
    };
    virtual void stop(int socket);
    virtual void open(int port, ClientHandler* ch);
};


#endif //EX4_MYPARALLELSERVER_H