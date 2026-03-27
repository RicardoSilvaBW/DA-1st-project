//
// Created by andresantos on 24/03/26.
//

#ifndef DA_1ST_PROJECT_RISKANALYZER_H
#define DA_1ST_PROJECT_RISKANALYZER_H

#include <vector>
#include "../model/Submission.h"
#include "../model/Reviewer.h"
#include "../model/Parameters.h"
#include "../model/RiskResult.h"

class RiskAnalyzer {
public:
    RiskAnalyzer(const std::vector<Submission>& submissions,
                 const std::vector<Reviewer>& reviewers,
                 const Parameters& parameters);

    RiskResult analyze() const;

private:
    const std::vector<Submission>& submissions;
    const std::vector<Reviewer>& reviewers;
    const Parameters& parameters;

    bool isReviewerCompatibleWithSubmission(const Reviewer& reviewer, const Submission& submission) const;
    bool isFeasibleWithoutReviewer(size_t removedReviewerIndex) const;
};

#endif //DA_1ST_PROJECT_RISKANALYZER_H