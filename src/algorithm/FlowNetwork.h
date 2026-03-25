//
// Created by ricar on 3/20/2026.
//

#ifndef DA_1ST_PROJECT_FLOWNETWORK_H
#define DA_1ST_PROJECT_FLOWNETWORK_H

#include <vector>
#include <unordered_map>
#include "../graph/Graph.h"
#include "../model/Reviewer.h"
#include "../model/Parameters.h"
#include "../model/ControlSettings.h"
#include "../model/ReviewAssignments.h"
#include "../model/MissingReview.h"
#include "MaxFlow.h"

class FlowNetwork {
private:
    Graph<int>* g;
    Vertex<int>* source;
    Vertex<int>* sink;

    std::vector<Reviewer> reviewers;
    std::vector<Submission> submissions;
    Parameters parameters;
    ControlSettings controlSettings;

    std::unordered_map<int, Reviewer> reviewerMap;
    std::unordered_map<int, submission> submissionMap;

    int totalFlow;
    int numOfRev;
    int numOfSub;

    void addVertices();
    void addCapacityEdges();
    bool topicsMatch(const Reviewer& reviewer, const Submission& submission);
    void addMatchingEdges();

public:

    FlowNetwork(const std::vector<Reviewer>& reviewers,
                const std::vector<Submission>& submissions,
                const Parameters& parameters,
                const ControlSettings& controlSettings);
    ~FlowNetwork();

    void build();
    int run();
    std::vector<ReviewAssignment> getReviewAssignments();
    std::vector<MissingReview> getMissingReviews();
};

#endif //DA_1ST_PROJECT_FLOWNETWORK_H