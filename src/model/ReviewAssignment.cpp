//
// Created by ricar on 3/7/2026.
//

#include "ReviewAssignment.h"

ReviewAssignment::ReviewAssignment(int submissionId, int reviewerId, int submissionDomain, int reviewerDomain)
                                    : submissionId(submissionId), reviewerId(reviewerId), submissionDomain(submissionDomain), reviewerDomain(reviewerDomain) {}

int ReviewAssignment::getSubmissionId() const {
    return submissionId;
}

int ReviewAssignment::getReviewerId() const {
    return reviewerId;
}

int ReviewAssignment::getSubmissionDomain() const {
    return submissionDomain;
}

int ReviewAssignment::getReviewerDomain() const {
    return reviewerDomain;
}