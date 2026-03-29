//
// Created by ricar on 3/14/2026.
//

/**
 * @file MaxFlow.cpp
 * @brief Implementation of the MaxFlow class (Edmonds-Karp algorithm).
 */

#include "MaxFlow.h"
#include <climits>

/**
 * @brief Constructor for MaxFlow.
 * @param graph Pointer to the graph.
 * @param s Pointer to the source vertex.
 * @param t Pointer to the sink vertex.
 */
MaxFlow::MaxFlow(Graph<int> *graph, Vertex<int> *s, Vertex<int> *t)
                : g(graph), s(s), t(t) {}

/**
 * @brief Helper for findAugmentingPath in BFS. Tests if a vertex can be visited.
 * @param q Queue of vertices to visit.
 * @param e Edge being traversed.
 * @param w Destination vertex.
 * @param residual Residual capacity of the edge.
 * @complexity O(1)
 */
void MaxFlow::testAndVisit(std::queue<Vertex<int>*> &q, Edge<int> *e, Vertex<int> *w, int residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

/**
 * @brief Searches for an augmenting path using Breadth-First Search (BFS).
 * @return true if an augmenting path was found, false otherwise.
 * @complexity O(V + E)
 */
bool MaxFlow::findAugmentingPath() {
    for (auto v: g->getVertexSet()) {
        v->setVisited(false);
    }
    s->setVisited(true);
    std::queue<Vertex<int>*> q;
    q.push(s);
    while (!q.empty() && !t->isVisited()) {
        auto v = q.front();
        q.pop();
        for (auto e: v->getAdj())
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        for (auto e: v->getIncoming())
            testAndVisit(q, e, e->getOrig(), e->getFlow());
    }
    return t->isVisited();
}

/**
 * @brief Finds the minimum residual capacity along the augmenting path.
 * @return The bottleneck capacity.
 * @complexity O(V)
 */
int MaxFlow::findMinResidualAlongPath() {
    int f = INT_MAX;
    auto v = t;
    while (v != s) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, static_cast<int>(e->getWeight() - e->getFlow()));
            v = e->getOrig();
        } else {
            f = std::min(f, static_cast<int>(e->getFlow()));
            v = e->getDest();
        }
    }
    return f;
}

/**
 * @brief Updates the flow along the augmenting path.
 * @param f The flow value to augment.
 * @complexity O(V)
 */
void MaxFlow::augmentFlowAlongPath(int f) {
    auto v = t;
    while (v != s) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            e->setFlow(e->getFlow() + f);
            v = e->getOrig();
        } else {
            e->setFlow(e->getFlow() - f);
            v = e->getDest();
        }
    }
}

/**
 * @brief Executes the Edmonds-Karp algorithm to find the maximum flow.
 * @return The total maximum flow.
 * @complexity O(V * E^2)
 */
int MaxFlow::edmondsKarp() {
    for (auto v: g->getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    while (findAugmentingPath()) {
        int f = findMinResidualAlongPath();
        augmentFlowAlongPath(f);
    }
    int totalFlow = 0;
    for (auto e : s->getAdj()) {
        totalFlow += static_cast<int>(e->getFlow());
    }
    return totalFlow;
}