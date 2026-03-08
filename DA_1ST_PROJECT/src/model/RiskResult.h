//
// Created by ricar on 3/7/2026.
//

#ifndef DA_1ST_PROJECT_RISKRESULT_H
#define DA_1ST_PROJECT_RISKRESULT_H

#include <vector>

class RiskResult {
private:
    int riskLevel;
    std::vector<int> riskyReviewerIds;

public:

    RiskResult(int riskLevel, std::vector<int> riskyReviewerIds);

    int getRiskLevel() const;
    const std::vector<int>& getRiskyReviewerIds() const;
};


#endif //DA_1ST_PROJECT_RISKRESULT_H