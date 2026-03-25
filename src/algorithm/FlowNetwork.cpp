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
      totalFlow(0), N(reviewers.size()), M(submissions.size()) {}

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
    if (g->addVertex(numOfRevs + numOfSub + 1))
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
    bool primaryMatch = reviewer.getPrimaryExpertise() == submission.getPrimaryTopic();

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
    // TODO: instantiate MaxFlow with g, source, sink
    // TODO: call edmondsKarp() and store result in totalFlow
    // TODO: return totalFlow
    return 0;
}

std::vector<ReviewAssignment> FlowNetwork::getAssignments() {
    // TODO: iterate over reviewer vertices (IDs 1 to N)
    // TODO: for each outgoing edge with flow == 1, look up reviewer and submission in maps
    // TODO: construct and collect ReviewAssignment objects
    return {};
}

std::vector<MissingReview> FlowNetwork::getMissingReviews() {
    // TODO: iterate over submission vertices (IDs N+1 to N+M)
    // TODO: compute total incoming flow for each submission vertex
    // TODO: if flow < MinReviewsPerSubmission, construct MissingReview with the difference
    return {};
}

#include "FlowNetwork.h"