//
// Created by andresantos on 24/03/26.
//

/**
 * @file RiskAnalyzer.cpp
 * @brief Implementation of the RiskAnalyzer class.
 */

#include "RiskAnalyzer.h"
#include <queue>
#include <algorithm>
#include <set>
#include "FlowNetwork.h"

using namespace std;

/**
 * @brief Constructor for RiskAnalyzer.
 * @param submissions Vector of submissions.
 * @param reviewers Vector of reviewers.
 * @param parameters Configuration parameters.
 * @param controlSettings Control settings.
 */
RiskAnalyzer::RiskAnalyzer(const vector<Submission>& submissions,
                           const vector<Reviewer>& reviewers,
                           const Parameters& parameters,
                           const ControlSettings& controlSettings)
    : submissions(submissions), reviewers(reviewers), parameters(parameters), controlSettings(controlSettings) {}

/**
 * @brief Determines if a reviewer is compatible with a submission based on topics.
 * @param reviewer The reviewer.
 * @param submission The submission.
 * @return true if compatible, false otherwise.
 * @complexity O(1)
 */
bool RiskAnalyzer::isReviewerCompatibleWithSubmission(const Reviewer& reviewer, const Submission& submission) const {
    
    int rp = reviewer.getPrimaryExpertise();
    int rs = reviewer.getSecondaryExpertise();
    int sp = submission.getPrimaryTopic();
    int ss = submission.getSecondaryTopic();

    if (rp == sp || rp == ss) return true;
    if (rs == sp || rs == ss) return true;

    return false;
}

/**
 * @brief Checks if an assignment is feasible without a group of reviewers.
 * @param removedIndices Indices of reviewers to exclude.
 * @return true if feasible, false otherwise.
 * @complexity O(V * E^2) where V and E are from the flow network.
 */
bool RiskAnalyzer::isFeasibleWithoutReviewers(const vector<size_t>& removedIndices) const {
    if (submissions.empty()) {
        return true;
    }

    vector<Reviewer> availableReviewers;
    set<size_t> removedSet(removedIndices.begin(), removedIndices.end());
    
    for (size_t i = 0; i < reviewers.size(); i++) {
        if (removedSet.find(i) == removedSet.end()) {
            availableReviewers.push_back(reviewers[i]);
        }
    }

    
    
    FlowNetwork network(availableReviewers, submissions, parameters, controlSettings);
    network.build();
    int flow = network.run();

    
    int requiredFlow = static_cast<int>(submissions.size()) * parameters.minReviewsPerSubmission;
    return flow >= requiredFlow;
}

/**
 * @brief Checks if an assignment is feasible without a specific reviewer.
 * @param removedReviewerIndex Index of the reviewer to exclude.
 * @return true if feasible, false otherwise.
 * @complexity O(V * E^2)
 */
bool RiskAnalyzer::isFeasibleWithoutReviewer(size_t removedReviewerIndex) const {
    return isFeasibleWithoutReviewers({removedReviewerIndex});
}

/**
 * @brief Recursive helper to find all combinations of K reviewers that are risky.
 * @param start Starting index for combination generation.
 * @param k Number of reviewers to remove.
 * @param currentCombination Current combination being built.
 * @param riskyIds Set of IDs of reviewers that were part of at least one risky combination.
 * @complexity O(R^K * V * E^2) where R is the number of reviewers.
 */
void RiskAnalyzer::findRiskyCombinations(size_t start, int k, vector<size_t>& currentCombination, set<int>& riskyIds) const {
    if (static_cast<int>(currentCombination.size()) == k) {
        if (!isFeasibleWithoutReviewers(currentCombination)) {
            for (size_t idx : currentCombination) {
                riskyIds.insert(reviewers[idx].getId());
            }
        }
        return;
    }

    
    
    
    
    
    
    for (size_t i = start; i < reviewers.size(); i++) {
        currentCombination.push_back(i);
        findRiskyCombinations(i + 1, k, currentCombination, riskyIds);
        currentCombination.pop_back();
    }
}

/**
 * @brief Performs the requested Risk Analysis (K=1 or K>1).
 * @return RiskResult containing the list of reviewers that are part of a risky group.
 * @complexity O(R^K * V * E^2)
 */
RiskResult RiskAnalyzer::analyze() const {
    int k = controlSettings.riskAnalysis;
    if (k <= 0) {
        return RiskResult(0, {});
    }

    set<int> uniqueRiskyIds;

    if (k == 1) {
        for (size_t i = 0; i < reviewers.size(); i++) {
            if (!isFeasibleWithoutReviewer(i)) {
                uniqueRiskyIds.insert(reviewers[i].getId());
            }
        }
    } else {
        vector<size_t> currentCombination;
        findRiskyCombinations(0, k, currentCombination, uniqueRiskyIds);
    }

    vector<int> riskyReviewerIds(uniqueRiskyIds.begin(), uniqueRiskyIds.end());
    sort(riskyReviewerIds.begin(), riskyReviewerIds.end());
    
    return RiskResult(static_cast<int>(riskyReviewerIds.size()), riskyReviewerIds);
}