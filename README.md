# mileStone2
by Vadim Litvinov & Yuval Shechter

## Description:
This project represents a server that accepts a problem from client and finds the solution by 
implements four search algorithms to return the short possible way from the initial vertex to the goal vertex.
The four algoritms are:

1.DFS

2.BFS

3.BestFS

4.A*

The program handles several clients by using parallel server and able to save 
previous solutions and pull solution for a problem that has already been solved by using cache manager and saving solutions into files.

# Run Insturctions:

1.Open terminal in project directory and type:

sudo g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread

 After compilation, type:
 
 ./a.out 'port_no'
 
 2.After the program is running, connect as a client.
 
 # More:
 link for the git: https://github.com/shechty2/mileStone2
