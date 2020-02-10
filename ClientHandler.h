//
// Created by yuvalshechter on 19/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H

using namespace std;

class ClientHandler {
public:
    virtual void handleClient(int clientSocket) = 0;
    virtual ~ClientHandler(){};
};


#endif //EX4_CLIENTHANDLER_H
