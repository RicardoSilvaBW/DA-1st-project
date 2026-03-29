//
// Created by ricar on 3/14/2026.
//

/**
 * @file MaxFlow.h
 * @brief Header for the MaxFlow class.
 */

#ifndef DA_1ST_PROJECT_MAXFLOW_H
#define DA_1ST_PROJECT_MAXFLOW_H

#include "../graph/Graph.h"

/**
 * @brief Class that implements the Max-Flow algorithm using Edmonds-Karp.
 * 
 * Task 2.1: Formulation of the Review Assignment Problem as a Max-Flow problem.
 */
class MaxFlow {
private:
    Graph<int>* g;
    Vertex<int>* s;
    Vertex<int>* t;

    /**
     * @brief Helper for findAugmentingPath in BFS.
     * @complexity O(1)
     */
	void testAndVisit(std::queue<Vertex<int>*>& q, Edge<int>* e, Vertex<int>* w, int residual);

    /**
     * @brief Searches for an augmenting path using BFS.
     * @return true if an augmenting path exists, false otherwise.
     * @complexity O(V + E)
     */
	bool findAugmentingPath();

    /**
     * @brief Finds the minimum residual capacity along the augmenting path.
     * @return Minimum residual capacity.
     * @complexity O(V)
     */
	int findMinResidualAlongPath();

    /**
     * @brief Updates the flow along the augmenting path.
     * @param f Flow to augment.
     * @complexity O(V)
     */
	void augmentFlowAlongPath(int f);

public:
    /**
     * @brief Constructor for MaxFlow.
     * @param g Pointer to the graph.
     * @param s Pointer to the source vertex.
     * @param t Pointer to the sink vertex.
     */
    MaxFlow(Graph<int>* g, Vertex<int>* s, Vertex<int>* t);

    /**
     * @brief Executes the Edmonds-Karp algorithm.
     * @return Total maximum flow.
     * @complexity O(V * E^2)
     */
	int edmondsKarp();
};

#endif //DA_1ST_PROJECT_MAXFLOW_H