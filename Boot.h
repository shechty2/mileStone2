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
#include "OA.h"
#include "MyClientHandler.h"
#include "MyParallelServer.h"

namespace  Boot {
class Main{
public:
  Main(){};
  ~Main(){};
  void main(int args){
    MyParallelServer mps;
    //FileCacheManager<string, string> cm;
    OA sr;
    MyClientHandler *mch = new MyClientHandler(&sr);
    mps.open(args, mch);
    //cout<< "I finished Main.main()";
    //return 0;
  };
};
};

#endif //EX4_BOOT_H