//
// Created by yuvalshechter on 27/01/2020.
//

#ifndef EX4_BOOT_H
#define EX4_BOOT_H

#include "Server.h"
#include "MySerialServer.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "CacheManager.h"
#include "MyTestClientHandler.h"

namespace  boot {
    class Main{
    public:
        Main(){};
        ~Main(){};
        void main(int args){
            MySerialServer mss;
            FileCacheManager<string, string> cm;
            StringReverser sr;
            MyTestClientHandler *mtch = new MyTestClientHandler(&cm, &sr);
            mss.open((args), mtch);
        };
    };
}

#endif //EX4_BOOT_H
