//
// Created by yuvalshechter on 19/01/2020.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

#include "Server.h"
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>

using namespace std;

class MySerialServer: public server_side::Server{
public:
    void open(int port, ClientHandler *c);
    void stop(int client_socket);
    void acceptClients(ClientHandler *c, int client_socket, sockaddr_in address);

};


#endif //EX4_MYSERIALSERVER_H
