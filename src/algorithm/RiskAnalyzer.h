//
// Created by andresantos on 24/03/26.
//

#ifndef DA_1ST_PROJECT_RISKANALYZER_H
#define DA_1ST_PROJECT_RISKANALYZER_H

#include <vector>
#include <set>
#include "../model/Submission.h"
#include "../model/Reviewer.h"
#include "../model/Parameters.h"
#include "../model/ControlSettings.h"
#include "../model/RiskResult.h"

class RiskAnalyzer {
public:
    RiskAnalyzer(const std::vector<Submission>& submissions,
                 const std::vector<Reviewer>& reviewers,
                 const Parameters& parameters,
                 const ControlSettings& controlSettings);

    RiskResult analyze() const;

private:
    const std::vector<Submission>& submissions;
    const std::vector<Reviewer>& reviewers;
    const Parameters& parameters;
    const ControlSettings& controlSettings;

    bool isReviewerCompatibleWithSubmission(const Reviewer& reviewer, const Submission& submission) const;
    bool isFeasibleWithoutReviewer(size_t removedReviewerIndex) const;
    bool isFeasibleWithoutReviewers(const std::vector<size_t>& removedIndices) const;
    void findRiskyCombinations(size_t start, int k, std::vector<size_t>& currentCombination, std::set<int>& riskyIds) const;
};

#endif //DA_1ST_PROJECT_RISKANALYZER_H