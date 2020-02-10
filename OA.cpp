//
// Created by adam on 30/01/2020.
//
#include "OA.h"
#include "Matrix.h"
#include "Searcher.h"
#include "BestFS.h"
#include "DFS.h"
#include "BFS.h"
#include "AStar.h"

string OA::solve(vector<string> problem) {
  Matrix* matrix = new Matrix(problem);
  AStar* searcher = new AStar();
  string sol = searcher->search(matrix);
  cout << sol;
  return sol;
}