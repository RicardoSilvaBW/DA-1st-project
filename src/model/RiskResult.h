//
// Created by ricar on 3/7/2026.
//

/**
 * @file RiskResult.h
 * @brief Header for the RiskResult class.
 */

#ifndef DA_1ST_PROJECT_RISKRESULT_H
#define DA_1ST_PROJECT_RISKRESULT_H

#include <vector>

/**
 * @class RiskResult
 * @brief Class representing the results of a risk analysis.
 */
class RiskResult {
private:
    int riskLevel;                  ///< Number of risky reviewers.
    std::vector<int> riskyReviewerIds; ///< IDs of risky reviewers.

public:
    /**
     * @brief Constructor for RiskResult.
     */
    RiskResult(int riskLevel, std::vector<int> riskyReviewerIds);

    /**
     * @brief Getter for Risk Level.
     */
    int getRiskLevel() const;

    /**
     * @brief Getter for Risky Reviewer IDs.
     */
    const std::vector<int>& getRiskyReviewerIds() const;
};


#endif //DA_1ST_PROJECT_RISKRESULT_H