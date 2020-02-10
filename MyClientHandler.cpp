//
// Created by yuvalshechter on 04/02/2020.
//

#include "MyClientHandler.h"

#include <unistd.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include "MyTestClientHandler.h"
#include "FileCacheManager.h"


MyClientHandler::MyClientHandler(Solver<vector<string>,string>* solver1){
    this-> cm = new FileCacheManager<string, string>();
    this-> solver = solver1;
}

void MyClientHandler::handleClient(int socketClient){
    char buffer[1024] = {0};
    int bufferlength = 1024;
    vector<string> matrix_vec;
    string newBuffer = "";
    string line = "";
    string temp_buffer;
    string strBuffer = "";
    //while (true) {
    memset(buffer, 0, bufferlength);
    int i = 0;
    read(socketClient, buffer, bufferlength);
    while (buffer[i] != '\0' && i < bufferlength) {
        line += buffer[i];
        i++;
    }
    while (!isEnd(buffer)) {
        int i = 0;
        memset(buffer, 0, bufferlength);
        read(socketClient, buffer, 1024);
        while (buffer[i] != '\0' && i < bufferlength) {
            line += buffer[i];
            i++;
        }
    }
    string temp_line = "";
    for (int i = 0; i<line.length(); i++) {
        if (line[i] != '\n' && line[i] != '\r') {
          temp_line += line[i];
        } else {
            if (temp_line.length() > 0) {
                matrix_vec.push_back(temp_line);
                temp_line = "";
            }
        }
    }
    matrix_vec.erase(matrix_vec.end()-1);
    //if (this->cm->isSolutionExist(line)) {
        //string solution = cm->getSolution(line);
        //connectAndSend(solution, socketClient);
    //} else {
    string solution;
    solution = solver->solve(matrix_vec);
   // cm->saveSolution(line, solution);
    connectAndSend(solution, socketClient);
    //}
}



int MyClientHandler:: connectAndSend(string msg, int clientSocket){
//create socket
    int is_sent = send(clientSocket,(char*)msg.c_str() , strlen((char*)msg.c_str()) , 0);
    if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    }
    close(clientSocket);
}


MyClientHandler::~MyClientHandler(){}

bool MyClientHandler::isEnd(string buffer) {
    int x = buffer.find("end");
    if (x < 0)
        return false;
    if (x >= 0) {
        buffer.erase(buffer.find("end"), 3);
        return true;
    }
}