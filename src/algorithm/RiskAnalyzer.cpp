//
// Created by andresantos on 24/03/26.
//

#include "RiskAnalyzer.h"
#include <queue>
#include <algorithm>
#include <set>
#include "FlowNetwork.h"

using namespace std;

RiskAnalyzer::RiskAnalyzer(const vector<Submission>& submissions,
                           const vector<Reviewer>& reviewers,
                           const Parameters& parameters,
                           const ControlSettings& controlSettings)
    : submissions(submissions), reviewers(reviewers), parameters(parameters), controlSettings(controlSettings) {}

bool RiskAnalyzer::isReviewerCompatibleWithSubmission(const Reviewer& reviewer, const Submission& submission) const {
    // Basic compatibility rule used for initial verification
    int rp = reviewer.getPrimaryExpertise();
    int rs = reviewer.getSecondaryExpertise();
    int sp = submission.getPrimaryTopic();
    int ss = submission.getSecondaryTopic();

    if (rp == sp || rp == ss) return true;
    if (rs == sp || rs == ss) return true;

    return false;
}

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

    // Task 2.2: Formulate the Review Assignment Problem as a Max-Flow problem
    // We use Ricardo's FlowNetwork class (even if currently a stub)
    FlowNetwork network(availableReviewers, submissions, parameters, controlSettings);
    network.build();
    int flow = network.run();

    // The assignment is feasible if total flow covers all submissions' requirements
    int requiredFlow = static_cast<int>(submissions.size()) * parameters.minReviewsPerSubmission;
    return flow >= requiredFlow;
}

bool RiskAnalyzer::isFeasibleWithoutReviewer(size_t removedReviewerIndex) const {
    return isFeasibleWithoutReviewers({removedReviewerIndex});
}

void RiskAnalyzer::findRiskyCombinations(size_t start, int k, vector<size_t>& currentCombination, set<int>& riskyIds) const {
    if (static_cast<int>(currentCombination.size()) == k) {
        if (!isFeasibleWithoutReviewers(currentCombination)) {
            for (size_t idx : currentCombination) {
                riskyIds.insert(reviewers[idx].getId());
            }
        }
        return;
    }

    // Optimization: if we are looking for a combination of size K that is risky,
    // and we already found that a smaller subset is risky, 
    // any superset of that risky subset will also be risky.
    // However, the project asks to identify ALL reviewers that can be part of an "offending" group of size K.
    // If a smaller group is already risky, then any reviewer added to it will result in a risky group of size K.
    
    for (size_t i = start; i < reviewers.size(); i++) {
        currentCombination.push_back(i);
        findRiskyCombinations(i + 1, k, currentCombination, riskyIds);
        currentCombination.pop_back();
    }
}

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