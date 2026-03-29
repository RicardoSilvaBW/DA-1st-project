//
// Created by ricar on 3/20/2026.
//

/**
 * @file FlowNetwork.h
 * @brief Header for the FlowNetwork class.
 */

#ifndef DA_1ST_PROJECT_FLOWNETWORK_H
#define DA_1ST_PROJECT_FLOWNETWORK_H

#include <vector>
#include <unordered_map>
#include "../graph/Graph.h"
#include "../model/Reviewer.h"
#include "../model/Parameters.h"
#include "../model/ControlSettings.h"
#include "../model/ReviewAssignment.h"
#include "../model/Submission.h"
#include "../model/MissingReview.h"
#include "MaxFlow.h"

/**
 * @brief Class that handles the construction of the flow network for assignment.
 * 
 * Part of Task 2.1: Formulation of the Review Assignment Problem as a Max-Flow problem.
 */
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
    std::unordered_map<int, Submission> submissionMap;

    int totalFlow;
    int numOfRev;
    int numOfSub;

    /**
     * @brief Adds source, sink, reviewer and submission vertices to the graph.
     * @complexity O(R + S) where R is number of reviewers and S number of submissions.
     */
    void addVertices();

    /**
     * @brief Adds edges from Source to Reviewers and Submissions to Sink with their respective capacities.
     * @complexity O(R + S)
     */
    void addCapacityEdges();

    /**
     * @brief Checks if a reviewer is compatible with a submission based on ControlSettings.
     * @complexity O(1)
     */
    bool topicsMatch(const Reviewer& reviewer, const Submission& submission);

    /**
     * @brief Adds edges between compatible reviewers and submissions.
     * @complexity O(R * S)
     */
    void addMatchingEdges();

public:

    /**
     * @brief Constructor for FlowNetwork.
     */
    FlowNetwork(const std::vector<Reviewer>& reviewers,
                const std::vector<Submission>& submissions,
                const Parameters& parameters,
                const ControlSettings& controlSettings);
    
    /**
     * @brief Destructor to clean up the graph.
     */
    ~FlowNetwork();

    /**
     * @brief Builds the flow network.
     * @complexity O(R * S)
     */
    void build();

    /**
     * @brief Runs the Max-Flow algorithm on the network.
     * @return Total flow assigned.
     * @complexity O(V * E^2) where V = R+S+2 and E = R*S + R + S.
     */
    int run();

    /**
     * @brief Extracts assignments from the flow network after run().
     * @return Vector of ReviewAssignment.
     * @complexity O(V + E)
     */
    std::vector<ReviewAssignment> getReviewAssignments();

    /**
     * @brief Identifies submissions with missing reviews.
     * @return Vector of MissingReview.
     * @complexity O(V + E)
     */
    std::vector<MissingReview> getMissingReviews();
};

#endif //DA_1ST_PROJECT_FLOWNETWORK_H