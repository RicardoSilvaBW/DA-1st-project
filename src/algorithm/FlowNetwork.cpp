//
// Created by ricar on 3/20/2026.
//

/**
 * @file FlowNetwork.cpp
 * @brief Implementation of the FlowNetwork class.
 */

#include "FlowNetwork.h"

/**
 * @brief Constructor for FlowNetwork.
 * @param reviewers Vector of reviewers to include in the network.
 * @param submissions Vector of submissions to include in the network.
 * @param parameters Configuration parameters (min/max reviews).
 * @param controlSettings Settings for assignment generation.
 */
FlowNetwork::FlowNetwork(const std::vector<Reviewer>& reviewers,
                         const std::vector<Submission>& submissions,
                         const Parameters& parameters,
                         const ControlSettings& controlSettings)
    : reviewers(reviewers), submissions(submissions),
      parameters(parameters), controlSettings(controlSettings),
      g(new Graph<int>()), source(nullptr), sink(nullptr),
      totalFlow(0), numOfRev(reviewers.size()), numOfSub(submissions.size()) {}

/**
 * @brief Destructor for FlowNetwork. Cleans up the graph.
 */
FlowNetwork::~FlowNetwork() {
    delete g;
}

/**
 * @brief Adds vertices to the flow network (source, sink, reviewers, submissions).
 * @complexity O(R + S) where R is the number of reviewers and S is the number of submissions.
 */
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

/**
 * @brief Adds edges with capacities from source to reviewers and submissions to sink.
 * @complexity O(R + S) where R is the number of reviewers and S is the number of submissions.
 */
void FlowNetwork::addCapacityEdges() {
    for (int i = 0 ; i < numOfRev ; i++) {
        g->addEdge(0, i + 1, parameters.maxReviewsPerReviewer);
    }
    for (int i = 0 ; i < numOfSub ; i++) {
        g->addEdge(numOfRev + i + 1, numOfRev + numOfSub + 1, parameters.minReviewsPerSubmission);
    }
}

/**
 * @brief Determines if a reviewer is compatible with a submission based on the control settings.
 * @param reviewer The reviewer to check.
 * @param submission The submission to check.
 * @return true if they are compatible, false otherwise.
 * @complexity O(1)
 */
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

/**
 * @brief Adds edges between compatible reviewers and submissions.
 * @complexity O(R * S) where R is the number of reviewers and S is the number of submissions.
 */
void FlowNetwork::addMatchingEdges() {
    for (int i = 0 ; i < numOfRev ; i++) {
        for (int j = 0 ; j < numOfSub ; j++) {
            if (topicsMatch(reviewers[i], submissions[j]))
                g->addEdge(i + 1, numOfRev + j + 1, 1);
        }
    }
}

/**
 * @brief Builds the flow network by adding vertices and edges.
 * @complexity O(R * S) where R is the number of reviewers and S is the number of submissions.
 */
void FlowNetwork::build() {
    addVertices();
    addCapacityEdges();
    addMatchingEdges();
}

/**
 * @brief Executes the Edmonds-Karp algorithm to find the maximum flow.
 * @return Total flow assigned.
 * @complexity O(V * E^2) where V = R+S+2 and E = R*S + R + S.
 */
int FlowNetwork::run() {
    if (source == nullptr || sink == nullptr) return 0;
    MaxFlow maxFlow(g, source, sink);
    totalFlow = maxFlow.edmondsKarp();
    return totalFlow;
}

/**
 * @brief Extracts the review assignments from the flow network after running the algorithm.
 * @return Vector of ReviewAssignment objects.
 * @complexity O(V + E)
 */
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
                
                int matchedSubDomain = 0;
                int matchedRevDomain = 0;
                
                
                bool pMatch = (r.getPrimaryExpertise() == s.getPrimaryTopic());
                bool sMatchSub = (r.getPrimaryExpertise() == s.getSecondaryTopic() && s.getSecondaryTopic() != 0);
                bool sMatchRev = (r.getSecondaryExpertise() == s.getPrimaryTopic() && r.getSecondaryExpertise() != 0);
                bool bothSecondary = (r.getSecondaryExpertise() != 0 && s.getSecondaryTopic() != 0 && r.getSecondaryExpertise() == s.getSecondaryTopic());

                if (pMatch) {
                    matchedSubDomain = s.getPrimaryTopic();
                    matchedRevDomain = r.getPrimaryExpertise();
                } else if (sMatchSub) {
                    matchedSubDomain = s.getSecondaryTopic();
                    matchedRevDomain = r.getPrimaryExpertise();
                } else if (sMatchRev) {
                    matchedSubDomain = s.getPrimaryTopic();
                    matchedRevDomain = r.getSecondaryExpertise();
                } else if (bothSecondary) {
                    matchedSubDomain = s.getSecondaryTopic();
                    matchedRevDomain = r.getSecondaryExpertise();
                }

                assignments.emplace_back(s.getId(), r.getId(), matchedSubDomain, matchedRevDomain);
            }
        }
    }
    return assignments;
}

/**
 * @brief Identifies submissions that did not receive the minimum required reviews.
 * @return Vector of MissingReview objects.
 * @complexity O(V + E)
 */
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