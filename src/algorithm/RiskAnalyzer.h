//
// Created by andresantos on 24/03/26.
//

/**
 * @file RiskAnalyzer.h
 * @brief Header for the RiskAnalyzer class.
 */

#ifndef DA_1ST_PROJECT_RISKANALYZER_H
#define DA_1ST_PROJECT_RISKANALYZER_H

#include <vector>
#include <set>
#include "../model/Submission.h"
#include "../model/Reviewer.h"
#include "../model/Parameters.h"
#include "../model/ControlSettings.h"
#include "../model/RiskResult.h"

/**
 * @brief Class for analyzing conference reviewer risk.
 * 
 * Task 2.2 and 2.3: Basic Formulation with Risk Analysis = 1 and Risk Analysis = K.
 */
class RiskAnalyzer {
public:
    /**
     * @brief Constructor for RiskAnalyzer.
     */
    RiskAnalyzer(const std::vector<Submission>& submissions,
                 const std::vector<Reviewer>& reviewers,
                 const Parameters& parameters,
                 const ControlSettings& controlSettings);

    /**
     * @brief Performs the requested Risk Analysis (K=1 or K>1).
     * @return RiskResult containing the list of reviewers that are part of a risky group.
     * @complexity O(R^K * V * E^2) for K > 0.
     */
    RiskResult analyze() const;

private:
    const std::vector<Submission>& submissions;
    const std::vector<Reviewer>& reviewers;
    const Parameters& parameters;
    const ControlSettings& controlSettings;

    bool isReviewerCompatibleWithSubmission(const Reviewer& reviewer, const Submission& submission) const;

    /**
     * @brief Checks if an assignment is feasible without a specific reviewer.
     * @complexity O(V * E^2)
     */
    bool isFeasibleWithoutReviewer(size_t removedReviewerIndex) const;

    /**
     * @brief Checks if an assignment is feasible without a group of reviewers.
     * @complexity O(V * E^2)
     */
    bool isFeasibleWithoutReviewers(const std::vector<size_t>& removedIndices) const;

    /**
     * @brief Recursive helper to find all combinations of K reviewers that are risky.
     * @complexity O(R^K) combinations * MaxFlow check.
     */
    void findRiskyCombinations(size_t start, int k, std::vector<size_t>& currentCombination, std::set<int>& riskyIds) const;
};

#endif //DA_1ST_PROJECT_RISKANALYZER_H