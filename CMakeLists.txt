cmake_minimum_required(VERSION 3.15)
project(ex4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(ex4 main.cpp Server.h ClientHandler.h MySerialServer.cpp MySerialServer.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.cpp Solver.h CacheManager.h FileCacheManager.h StringReverser.cpp StringReverser.h Boot.h Searchable.h State.h Searcher.h Matrix.cpp Matrix.h BestFS.cpp BestFS.h State.cpp OA.cpp OA.h HelpfulFunctionsForMatrix.cpp HelpfulFunctionsForMatrix.h MyClientHandler.cpp MyClientHandler.h DFS.cpp DFS.h BFS.cpp BFS.h AStar.cpp AStar.h MyParallelServer.cpp MyParallelServer.h)
