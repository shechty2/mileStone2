//
// Created by yuvalshechter on 19/01/2020.
//

#include <unistd.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include "MyTestClientHandler.h"


MyTestClientHandler::MyTestClientHandler(CacheManager<string,string>* cm1, Solver<string,string>*solver1){
   this-> cm = cm1;
    this-> solver = solver1;
}

void MyTestClientHandler::handleClient(int socketClient){
        //char buffer[1048] = {0};
        string buffLine = "";
        string newBuffer = "";
        string strBuffer = "";
        while(true) {
            char buffer[1048] = {0};
            int valRead = read(socketClient, buffer, 1048);
            if (valRead < 0) {
                cout << "Error in reading from socket" << endl;
            }
            strBuffer = buffer;
            buffLine = "";
            for (char c: strBuffer) {
                if (c != '\r') {
                    if (c == '\n') {
                        buffLine = buffLine + ',' + c + ',';
                    } else {
                        buffLine += c;
                    }
                }
                //buffLine += c;
                if (c == '\n') {
                    if (buffLine != "end,\n,") {
                        newBuffer += buffLine;
                        buffLine = "";
                    } else {
                        break;
                    }
                }
            }
            if (buffLine == "end,\n,") {
                break;
            }
        }
            //if the buffLine is exists in the files
            /*if (this->cm->isSolutionExist(newBuffer)) {
                string solution = cm->getSolution(newBuffer);
                connectAndSend(solution);
            } else {*/
                string solution = solver->solve(newBuffer);
                //cm->saveSolution(newBuffer, solution);
                connectAndSend(solution);
            //}
        }

    /*char buffer[1024] = {0};
    string problem = "";
    while(true){
        int valRead = read(socketClient, buffer, 1048);
        problem = "";
        for(char c:buffer){
            if(c == '\n'){
                break;
            }
            if(c != '\r') {
                problem = problem + c;
            }
        }
        if (problem == "end"){
            break;
        }
        //if the problem is exits in the files, find the solution
        if(cm->isSolutionExist(problem)){
            string solution = cm->getSolution(problem);
            connectAndSend(solution);
        }
        //the problem is not exits, creat solution (reversed string)
        else{
            string solution = solver-> solve(problem);
            cm-> saveSolution(problem, solution);
            connectAndSend(solution);
        }
    }*/
//}

int MyTestClientHandler:: connectAndSend(string msg){
//create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
    address.sin_port = htons(5400);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.
    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        return -2;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }

    int is_sent = send(client_socket,(char*)msg.c_str() , strlen((char*)msg.c_str()) , 0);
    if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    } else {
        std::cout<< msg << "message sent to server"<<std::endl;
    }
    close(client_socket);
}


MyTestClientHandler::~MyTestClientHandler(){}