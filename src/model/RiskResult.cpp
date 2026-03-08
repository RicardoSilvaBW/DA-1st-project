//
// Created by ricar on 3/7/2026.
//

#include "RiskResult.h"

RiskResult::RiskResult(int riskLevel, std::vector<int> riskyReviewerIds) :
    : riskLevel(riskLevel), riskyReviewerIds(riskyReviewerIds) {}

int RiskResult::getRiskLevel() const {
    return riskLevel;
}

const std::vector<int>& RiskResult::getRiskyReviewerIds() const {
    return riskyReviewerIds;
}