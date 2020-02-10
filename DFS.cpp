//
// Created by yuvalshechter on 05/02/2020.
//

#include "DFS.h"
/**
 *
 * @param This function get as input searchable
 * @return possible way from the source vertex (initialState) to the target vertex (goalState).
 */
string DFS::search(Searchable* searchable) {
    State* currentVertex;
    State* currentAdjacent;
    stack<State*> st;
    unordered_map<string, State *> *vertexMap = searchable->getVertexMap();
    map<string, vector<State *>> mapOfAdjacentVertexes = HelpfulFunctionsForMatrix::makingNeighborMap(vertexMap,
                                                                                                      searchable->getN());
    map<string, bool> mapOfVisitedVertexes= HelpfulFunctionsForMatrix::makingVisitedMap(vertexMap);
    if(searchable->getGoalState() == searchable->getInitialState())
    {
        return "{}";
    }
    st.push(searchable->getInitialState());
    while(!st.empty())
    {
        currentVertex = st.top();
        st.pop();
        if(!mapOfVisitedVertexes[currentVertex->get_vertex_index()])
        {
            mapOfVisitedVertexes[currentVertex->get_vertex_index()] = true;
            this->evaluatedNodes++;
        }
        vector<State*> temp_adjacent = mapOfAdjacentVertexes[currentVertex->get_vertex_index()] ;
        for (int i = 0; i < temp_adjacent.size() ; i++)
        {
            currentAdjacent = temp_adjacent[i];
            //if the state have not visited yet
            if (mapOfVisitedVertexes[currentAdjacent->get_vertex_index()] == false)
            {
                //set the current vertex to be his father
                currentAdjacent->set_father(currentVertex);
                if (currentAdjacent != searchable->getGoalState()) {
                    st.push(currentAdjacent);
                } else
                {
                    cout << endl << "Number of evaluated nodes is: " << this->evaluatedNodes << endl;
                    return HelpfulFunctionsForMatrix::createSolutionPath(searchable);
                }
            }
        }
    }
    return "-1";
}
int DFS:: NumOfNodesEvaluated()
{
    return this->evaluatedNodes;
}

DFS::~DFS(){};