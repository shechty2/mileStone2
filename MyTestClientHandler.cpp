//
// Created by yuvalshechter on 19/01/2020.
//

#include <unistd.h>
#include <iostream>
#include "MyTestClientHandler.h"
#include "CacheManager.h"

MyTestClientHandler::MyTestClientHandler(CacheManager<string,string>* cm1, Solver<string,string>*solver1){
   this-> cm = cm1;
    this-> solver = solver;
}

void MyTestClientHandler::handleClient(int socketClient){
    char buffer[1024] = {0};
    string str = "";
    while(true){
        int valRead= read(socketClient, buffer, 1048);
        str = "";
        for(char c:buffer){
            if(c == '\n'){
                break;
            }
            str = str +c;
        }
        if (str == "end"){
            break;
        }
        //need the class FileCacheManger from targil 2 to continue!!!!!
        }
    }


}




MyTestClientHandler::~MyTestClientHandler(){}