//
// Created by ricar on 3/14/2026.
//

#include "MaxFlow.h"

MaxFlow::MaxFlow(Graph<int> *graph, Vertex<int> *s, Vertex<int> *t)
                : graph(graph), s(s), t(t) {}

void testAndVisit(std::queue<Vertex<int>*> &q, Edge<int> *e, Vertex<int> *w, int residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool findAugmentingPath(Graph<int> *g, Vertex<int> *s, Vertex<int> *t) {
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

int findMinResidualAlongPath(Vertex<int> *s, Vertex<int> *t) {
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

void augmentFlowAlongPath(Vertex<int> *s, Vertex<int> *t, double f) {
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

void edmondsKarp(Graph<int> *g, int s, int t) {
    Vertex<int> *source = g->findVertex(source);
    Vertex<int> *target = g->findVertex(target);
    for (auto v: g->getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    while (findAugmentingPath(g, source, target)) {
        double f = findMinResidualAlongPath(source, target);
        augmentFlowAlongPath(source, target, f);
    }
}