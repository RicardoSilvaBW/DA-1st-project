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
    // TODO: add super-source vertex (ID 0)
    // TODO: add reviewer vertices (IDs 1 to N) and populate reviewerMap
    // TODO: add submission vertices (IDs N+1 to N+M) and populate submissionMap
    // TODO: add super-sink vertex (ID N+M+1)
    // TODO: set source and sink pointers
}

void FlowNetwork::addCapacityEdges() {
    // TODO: add edges from super-source to each reviewer (cap = MaxReviewsPerReviewer)
    // TODO: add edges from each submission to super-sink (cap = MinReviewsPerSubmission)
}

void FlowNetwork::addMatchingEdges() {
    // TODO: for each reviewer-submission pair, call topicsMatch()
    // TODO: if match found, add edge with capacity 1
}

bool FlowNetwork::topicsMatch(const Reviewer& reviewer, const Submission& submission) {
    // TODO: check domains based on controlSettings.generateAssignments mode
    // mode 1: primary reviewer expertise == primary submission topic
    // mode 2: also consider secondary domains
    // mode 3: all domain combinations
    return false;
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