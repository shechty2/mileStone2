//
// Created by yuvalshechter on 05/02/2020.
//

#include "BFS.h"
#include "HelpfulFunctionsForMatrix.h"

int BFS:: getExpended() {
    return expandedNodesNum;
}


string BFS::search(Searchable* searchable) {
    unordered_map<string, State*>* v_map = searchable->getVertexMap() ;
    queue<State*> qe;
    State* curAdj ;
    State* curV ;
    map<string, vector<State*>> neighborsMap = HelpfulFunctionsForMatrix::makingNeighborMap(v_map, searchable->getN());
    map<string, bool> beenMap = HelpfulFunctionsForMatrix::makingVisitedMap(v_map) ;
    if(searchable->getInitialState() == searchable->getGoalState()) {
        return "{ }";
    }
    HelpfulFunctionsForMatrix::setVisitedMap(searchable->getInitialState()->get_vertex_index(), &beenMap);
    qe.push(searchable->getInitialState());
    beenMap[qe.front()->get_vertex_index()] = true;
    this->expandedNodesNum = expandedNodesNum + 1;
    while(qe.empty() == false) {
        curV = qe.front();
        qe.pop();
        vector<State*> temp_adjacent = neighborsMap[curV->get_vertex_index()];
        int i;
        for (i = 0;i < temp_adjacent.size();++i) {
            curAdj = temp_adjacent[i];
            if(!beenMap[curAdj->get_vertex_index()]) {
                curAdj->set_father(curV);
                if(curAdj != searchable->getGoalState()) {
                    beenMap[curAdj->get_vertex_index()] = true;
                    qe.push(curAdj);
                    this->expandedNodesNum = expandedNodesNum + 1;
                } else {
                    //cout<<this->expandedNodesNum<<"\n"<<endl;
                    //cout << endl << "expandedNodesNum: " << this->expandedNodesNum << endl;
                    return HelpfulFunctionsForMatrix::createSolutionPath(searchable);
                }
            }
        }
    }
    return "-1\r\n";
}