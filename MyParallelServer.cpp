//
// Created by yuvalshechter on 06/02/2020.
//

#include "MyParallelServer.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include "ClientHandler.h"
#include "MyClientHandler.h"
#include "Server.h"
#include "OA.h"
#include <unistd.h>
#include <thread>


void MyParallelServer::open(int port, ClientHandler *ch) {
    int newsockfd, sock;
    struct sockaddr_in serv_addr{}, client_addr{};
    //Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cout << "Error at opening socket!";
        cout << endl << strerror(errno);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Error binding to address" << endl;
        cout << strerror(errno);
        this->stop(sock);
    }
    if (listen(sock, SOMAXCONN) == -1) {
        cerr<<"Error during listening command"<< endl;
    } else {
        cout<<"Server is now listening ..."<< endl;
    }
    struct sockaddr_in cli_addr;
    int clilen = sizeof(cli_addr);
    struct timeval tv;
    tv.tv_sec = 120;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
    while (true) {
        newsockfd = accept(sock, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
        if (newsockfd < 0) {
            if (errno == EWOULDBLOCK) {
                cout << "the time was given to connecting is over (120 seconds)" << endl;
                break;
            } else {
                cerr << "Cannot accept connection";
                cout << endl << strerror(errno);
                break;
            }
        }
        threadsVec.push_back(thread(OAFunction, ch, newsockfd));
    }
    this->stop(sock);
    if (newsockfd != -1) {
        this->stop(newsockfd);
    }
}


void MyParallelServer::stop(int socket) {
    close(socket);
}


//the function for creating the adaptor and handeling the client
void MyParallelServer::OAFunction(ClientHandler *ch, int socket) {
    OA* searcher = new OA();
    ch = new MyClientHandler(searcher);
    ch->handleClient(socket);
}