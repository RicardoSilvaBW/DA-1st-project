//
// Created by ricar on 3/14/2026.
//

#ifndef DA_1ST_PROJECT_MAXFLOW_H
#define DA_1ST_PROJECT_MAXFLOW_H

#include "../graph/Graph.h"

class MaxFlow {
private:
    Graph<int>* g;
    Vertex<int>* s;
    Vertex<int>* t;

	void testAndVisit(std::queue<Vertex<int>*>& q, Edge<int>* e, Vertex<int>* w, int residual);
	bool findAugmentingPath();
	int findMinResidualAlongPath();
	void augmentFlowAlongPath(int f);

public:
    MaxFlow(Graph<int>* g, Vertex<int>* s, Vertex<int>* t);
	int edmondsKarp();
};

#endif //DA_1ST_PROJECT_MAXFLOW_H