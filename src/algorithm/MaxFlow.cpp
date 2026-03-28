//
// Created by ricar on 3/14/2026.
//

#include "MaxFlow.h"
#include <climits>

MaxFlow::MaxFlow(Graph<int> *graph, Vertex<int> *s, Vertex<int> *t)
                : g(graph), s(s), t(t) {}

void MaxFlow::testAndVisit(std::queue<Vertex<int>*> &q, Edge<int> *e, Vertex<int> *w, int residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

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

int MaxFlow::findMinResidualAlongPath() {
    int f = INT_MAX;
    auto v = t;
    while (v != s) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        } else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

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
}