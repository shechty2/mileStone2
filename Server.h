//
// Created by yuvalshechter on 19/01/2020.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H

#include "ClientHandler.h"

namespace server_side {

    class Server {
    public:
        virtual void open(int port, ClientHandler *c) = 0;
        virtual void stop(int client_socket) = 0;
    };

}

#endif //EX4_SERVER_H
