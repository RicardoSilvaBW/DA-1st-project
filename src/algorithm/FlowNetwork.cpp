//
// Created by ricar on 3/20/2026.
//

#include "FlowNetwork.h"

FlowNetwork::FlowNetwork(const std::vector<Reviewer>& reviewers,
                         const std::vector<Submission>& submissions,
                         const Parameters& parameters,
                         const ControlSettings& controlSettings)
    : reviewers(reviewers), submissions(submissions),
      parameters(parameters), controlSettings(controlSettings),
      g(new Graph<int>()), source(nullptr), sink(nullptr),
      totalFlow(0), numOfRev(reviewers.size()), numOfSub(submissions.size()) {}

FlowNetwork::~FlowNetwork() {
    delete g;
}

void FlowNetwork::addVertices() {
    if (g->addVertex(0))
        source = g->findVertex(0);
    for (int i = 0 ; i < numOfRev ; i++) {
        g->addVertex(i + 1);
        reviewerMap.insert({i + 1, reviewers[i]});
    }
    for (int i = 0 ; i < numOfSub ; i++ ) {
        g->addVertex(numOfRev + i + 1);
        submissionMap.insert({numOfRev + i + 1, submissions[i]});
    }
    if (g->addVertex(numOfRev + numOfSub + 1))
        sink = g->findVertex(numOfRev + numOfSub + 1);
}

void FlowNetwork::addCapacityEdges() {
    for (int i = 0 ; i < numOfRev ; i++) {
        g->addEdge(0, i + 1, parameters.maxReviewsPerReviewer);
    }
    for (int i = 0 ; i < numOfSub ; i++) {
        g->addEdge(numOfRev + i + 1, numOfRev + numOfSub + 1, parameters.minReviewsPerSubmission);
    }
}

bool FlowNetwork::topicsMatch(const Reviewer& reviewer, const Submission& submission) {
    bool primaryMatch = (reviewer.getPrimaryExpertise() == submission.getPrimaryTopic());

    bool secondaryMatch = (reviewer.getPrimaryExpertise() == submission.getSecondaryTopic() && submission.getSecondaryTopic() != 0)
                       || (reviewer.getSecondaryExpertise() == submission.getPrimaryTopic() && reviewer.getSecondaryExpertise() != 0);

    bool allMatch = secondaryMatch
                 || (reviewer.getSecondaryExpertise() != 0 && submission.getSecondaryTopic() != 0
                     && reviewer.getSecondaryExpertise() == submission.getSecondaryTopic());

    switch (controlSettings.generateAssignments) {
        case 1: return primaryMatch;
        case 2: return primaryMatch || secondaryMatch;
        case 3: return primaryMatch || allMatch;
        default: return false;
    }
}

void FlowNetwork::addMatchingEdges() {
    for (int i = 0 ; i < numOfRev ; i++) {
        for (int j = 0 ; j < numOfSub ; j++) {
            if (topicsMatch(reviewers[i], submissions[j]))
                g->addEdge(i + 1, numOfRev + j + 1, 1);
        }
    }
}

void FlowNetwork::build() {
    addVertices();
    addCapacityEdges();
    addMatchingEdges();
}

int FlowNetwork::run() {
    if (source == nullptr || sink == nullptr) return 0;
    MaxFlow maxFlow(g, source, sink);
    totalFlow = maxFlow.edmondsKarp();
    return totalFlow;
}

std::vector<ReviewAssignment> FlowNetwork::getReviewAssignments() {
    std::vector<ReviewAssignment> assignments;
    for (int i = 0; i < numOfRev; i++) {
        auto v = g->findVertex(i + 1);
        if (!v) continue;
        for (auto e : v->getAdj()) {
            if (e->getFlow() > 0) {
                int subId = e->getDest()->getInfo();
                int revId = v->getInfo();
                const Reviewer& r = reviewerMap.at(revId);
                const Submission& s = submissionMap.at(subId);
                assignments.emplace_back(s.getId(), r.getId(), s.getPrimaryTopic(), r.getPrimaryExpertise());
            }
        }
    }
    return assignments;
}

std::vector<MissingReview> FlowNetwork::getMissingReviews() {
    std::vector<MissingReview> missing;
    for (int i = 0; i < numOfSub; i++) {
        auto v = g->findVertex(numOfRev + i + 1);
        if (!v) continue;
        int incomingFlow = 0;
        for (auto e : v->getIncoming()) {
            if (e->getOrig() != source && e->getOrig() != sink) {
                incomingFlow += e->getFlow();
            }
        }
        if (incomingFlow < parameters.minReviewsPerSubmission) {
            const Submission& s = submissionMap.at(v->getInfo());
            missing.emplace_back(s.getId(), s.getPrimaryTopic(), parameters.minReviewsPerSubmission - incomingFlow);
        }
    }
    return missing;
}