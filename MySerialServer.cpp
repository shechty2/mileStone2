//
// Created by yuvalshechter on 19/01/2020.
//
#include "MySerialServer.h"
using namespace std;

//Creating a socket
void MySerialServer :: open(int port, ClientHandler *c) {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
    }
    //binding socket to IP address
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(client_socket, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
    }
    //making socket listen to the port
    if (listen(client_socket, 5) == -1) {
        std::cerr<<"Error during listening command"<<std::endl;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }
    //closing the listening socket


    //thread
    //thread thread1([=] {acceptClients(c, client_socket, address); });
    //thread1.join();
    //stop(client_socket);
    acceptClients(c, client_socket, address);
    //return client_socket;
}

//accepting and waiting for the clients
void MySerialServer::acceptClients(ClientHandler *c, int client_socket, sockaddr_in address){
// define timout for client connecting
    timeval timeOut;
    timeOut.tv_sec = 120;
    timeOut.tv_usec = 0;
    setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeOut, sizeof(timeOut));
    // accepting a client
    client_socket = accept(client_socket, (struct sockaddr*)&address,(socklen_t*)&address);
    if (client_socket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
    } else {
        cout<<"Client accepted"<<endl;
        c->handleClient(client_socket);
    }
    stop(client_socket);
}


//closing the socket
void MySerialServer::stop(int client_socket){
    close(client_socket);
}