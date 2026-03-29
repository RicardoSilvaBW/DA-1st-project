//
// Created by ricar on 3/7/2026.
//

/**
 * @file RiskResult.cpp
 * @brief Implementation of the RiskResult class.
 */

#include "RiskResult.h"

/**
 * @brief Constructor for RiskResult.
 * @param riskLevel Number of risky reviewers.
 * @param riskyReviewerIds Vector containing IDs of risky reviewers.
 */
RiskResult::RiskResult(int riskLevel, std::vector<int> riskyReviewerIds)
    : riskLevel(riskLevel), riskyReviewerIds(riskyReviewerIds) {}

/**
 * @brief Getter for Risk Level.
 * @return Number of risky reviewers.
 */
int RiskResult::getRiskLevel() const {
    return riskLevel;
}

/**
 * @brief Getter for Risky Reviewer IDs.
 * @return Vector of IDs.
 */
const std::vector<int>& RiskResult::getRiskyReviewerIds() const {
    return riskyReviewerIds;
}