//
// Created by andresantos on 24/03/26.
//

#include "RiskAnalyzer.h"
#include <queue>

using namespace std;

RiskAnalyzer::RiskAnalyzer(const vector<Submission>& submissions,
                           const vector<Reviewer>& reviewers,
                           const Parameters& parameters)
    : submissions(submissions), reviewers(reviewers), parameters(parameters) {}

bool RiskAnalyzer::isReviewerCompatibleWithSubmission(const Reviewer& reviewer, const Submission& submission) const {
    // Basic compatibility rule:
    // A reviewer is considered compatible if their primary or secondary expertise
    // matches the submission's primary or secondary topic.
    int rp = reviewer.getPrimaryExpertise();
    int rs = reviewer.getSecondaryExpertise();
    int sp = submission.getPrimaryTopic();
    int ss = submission.getSecondaryTopic();

    if (rp == sp || rp == ss) return true;
    if (rs == sp || rs == ss) return true;

    return false;
}

bool RiskAnalyzer::isFeasibleWithoutReviewer(size_t removedReviewerIndex) const {
    if (submissions.empty()) {
        return true;
    }

    vector<int> reviewerCapacity;
    reviewerCapacity.reserve(reviewers.size());

    for (size_t i = 0; i < reviewers.size(); i++) {
        if (i == removedReviewerIndex) continue;
        reviewerCapacity.push_back(parameters.maxReviewsPerReviewer);
    }

    // Quick rejection: total available capacity must cover total required reviews
    long long totalRequiredReviews = 0;
    for (const auto& s : submissions) {
        totalRequiredReviews += parameters.minReviewsPerSubmission;
    }

    long long totalAvailableCapacity = 0;
    for (size_t i = 0; i < reviewers.size(); i++) {
        if (i == removedReviewerIndex) continue;
        totalAvailableCapacity += parameters.maxReviewsPerReviewer;
    }

    if (totalAvailableCapacity < totalRequiredReviews) {
        return false;
    }

    // Greedy feasibility test:
    // for each submission, count compatible available reviewers
    // and ensure there are at least minReviewsPerSubmission of them.
    //
    // This is not the full max-flow solution yet, but it is a useful first
    // risk-analysis approximation and compiles cleanly now.
    for (const auto& submission : submissions) {
        int compatibleReviewers = 0;

        for (size_t i = 0; i < reviewers.size(); i++) {
            if (i == removedReviewerIndex) continue;

            const auto& reviewer = reviewers[i];
            if (isReviewerCompatibleWithSubmission(reviewer, submission)) {
                compatibleReviewers++;
            }
        }

        if (compatibleReviewers < parameters.minReviewsPerSubmission) {
            return false;
        }
    }

    return true;
}

RiskResult RiskAnalyzer::analyze() const {
    vector<int> riskyReviewerIds;
    int riskLevel = 0;

    for (size_t i = 0; i < reviewers.size(); i++) {
        if (!isFeasibleWithoutReviewer(i)) {
            riskyReviewerIds.push_back(reviewers[i].getId());
        }
    }

    riskLevel = static_cast<int>(riskyReviewerIds.size());
    return RiskResult(riskLevel, riskyReviewerIds);
}