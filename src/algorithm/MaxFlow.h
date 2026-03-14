//
// Created by ricar on 3/14/2026.
//

#ifndef DA_1ST_PROJECT_MAXFLOW_H
#define DA_1ST_PROJECT_MAXFLOW_H

#include "../graph/Graph.h"
#include <limits>

class MaxFlow {
private:
    Graph<int>* g;
    Vertex<int>* s;
    Vertex<int>* t;

public:
    MaxFlow(Graph<int>* g, Vertex<int>* s, Vertex<int>* t);
    void testAndVisit(std::queue<Vertex<int>*> &q, Edge<int>* e, Vertex<int>* v, int residual);
    bool findAugmentingPath(Graph<int> *g, Vertex<int> *s, Vertex<int> *t);
    int findMinResidualAlongPath(Vertex<int> *s, Vertex<int> *t);
    void augmentFlowAlongPath(Vertex<int> *s, Vertex<int> *t, double f);
    void edmondsKarp(Graph<int> *g, int s, int t);
};

#endif //DA_1ST_PROJECT_MAXFLOW_H